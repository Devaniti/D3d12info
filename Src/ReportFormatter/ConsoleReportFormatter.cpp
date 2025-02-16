/*
This file is part of D3d12info project:
https://github.com/sawickiap/D3d12info

Copyright (c) 2018-2025 Adam Sawicki, https://asawicki.info
License: MIT

For more information, see files README.md, LICENSE.txt.
*/
#include "ConsoleReportFormatter.hpp"

#include "Printer.hpp"
#include "Enums.hpp"

ConsoleReportFormatter::ConsoleReportFormatter(Flags flags)
{
}

ConsoleReportFormatter::~ConsoleReportFormatter()
{
	assert(m_ScopeStack.empty());
	Printer::PrintNewLine();
}

void ConsoleReportFormatter::PushObject(std::wstring_view name)
{
	assert(!name.empty());

	// Need to skip new line when outputting first object
	if (!m_SkipNewLine)
	{
		Printer::PrintNewLine();
		Printer::PrintNewLine();
	}
	else
	{
		m_SkipNewLine = false;
	}

	PrintIndent();

	Printer::PrintString(name);

	PrintDivider(name.size());

	m_ScopeStack.push({ .Type = ScopeType::Object });
	++m_IndentLevel;
}

void ConsoleReportFormatter::PushArray(std::wstring_view name, ArraySuffix suffix /* = ArraySuffix::SquareBrackets */)
{
	assert(!name.empty());

	m_ScopeStack.push({ .ArrayName = std::wstring(name), .Type = ScopeType::Array, .Suffix = suffix });
}

void ConsoleReportFormatter::PushArrayItem()
{
	assert(!m_ScopeStack.empty());

	ScopeInfo& arrayScope = m_ScopeStack.top();

	assert(arrayScope.Type == ScopeType::Array);

	Printer::PrintNewLine();
	Printer::PrintNewLine();
	PrintIndent();

	std::wstring header; 
	switch (arrayScope.Suffix)
	{
	case ArraySuffix::SquareBrackets:
		header = std::format(L"{}[{}]", arrayScope.ArrayName, arrayScope.ElementCount++);
		break;
	default:
		assert(0);
		[[fallthrough]];
	case ArraySuffix::None:
		header = std::format(L"{} {}", arrayScope.ArrayName, arrayScope.ElementCount++);
		break;
	}

	Printer::PrintString(header);

	PrintDivider(header.size());

	m_ScopeStack.push({ .ElementCount = 0, .Type = ScopeType::Object });
	++m_IndentLevel;
}

void ConsoleReportFormatter::PopScope()
{
	assert(!m_ScopeStack.empty());
	ScopeInfo scope = m_ScopeStack.top();
	m_ScopeStack.pop();
	if (scope.Type != ScopeType::Array)
	{
		--m_IndentLevel;
	}
}

void ConsoleReportFormatter::AddFieldString(std::wstring_view name, std::wstring_view value)
{
	assert(!name.empty());
	assert(!value.empty());
	PushElement();
	Printer::PrintFormat(L"{} = {}", std::make_wformat_args(name, value));
}

void ConsoleReportFormatter::AddFieldBool(std::wstring_view name, bool value)
{
	assert(!name.empty());
	PushElement();
	Printer::PrintFormat(L"{} = {}", std::make_wformat_args(name, (value ? L"TRUE" : L"FALSE")));
}

void ConsoleReportFormatter::AddFieldUint32(std::wstring_view name, uint32_t value, std::wstring_view unit /*= {}*/)
{
	assert(!name.empty());
	PushElement();
	Printer::PrintFormat(L"{} = {}", std::make_wformat_args(name, value));
}

void ConsoleReportFormatter::AddFieldUint64(std::wstring_view name, uint64_t value, std::wstring_view unit /*= {}*/)
{
	assert(!name.empty());
	PushElement();
	if (unit.empty())
	{
		Printer::PrintFormat(L"{} = {}", std::make_wformat_args(name, value));
	}
	else
	{
		Printer::PrintFormat(L"{} = {} {}", std::make_wformat_args(name, value, unit));
	}
}

void ConsoleReportFormatter::AddFieldSize(std::wstring_view name, uint64_t value)
{
	assert(!name.empty());
	PushElement();

	const wchar_t* units[] = { L"B", L"KiB", L"MiB", L"GiB", L"TiB" };

	int selectedUnit = 0;
	uint64_t scale = 1;
	for (; selectedUnit < ARRAYSIZE(units) - 1; ++selectedUnit)
	{
		if (value / scale < 1024)
		{
			break;
		}
		scale = scale << 10;
	}

	if (selectedUnit == 0)
	{
		Printer::PrintFormat(L"{} = {} {}", std::make_wformat_args(name, value, units[selectedUnit]));
		return;
	}
	else
	{
		Printer::PrintFormat(L"{} = {:.2f} {} ({} B)", std::make_wformat_args(name, double(value) / scale, units[selectedUnit], value));
	}
}

void ConsoleReportFormatter::AddFieldSizeKilobytes(std::wstring_view name, uint64_t value)
{
	AddFieldSize(name, value * 1024);
}

void ConsoleReportFormatter::AddFieldHex32(std::wstring_view name, uint32_t value)
{
	assert(!name.empty());
	PushElement();
	Printer::PrintFormat(L"{} = 0x{:X}", std::make_wformat_args(name, value));
}

void ConsoleReportFormatter::AddFieldInt32(std::wstring_view name, int32_t value, std::wstring_view unit /*= {}*/)
{
	assert(!name.empty());
	PushElement();
	if (unit.empty())
	{
		Printer::PrintFormat(L"{} = {}", std::make_wformat_args(name, value));
	}
	else
	{
		Printer::PrintFormat(L"{} = {} {}", std::make_wformat_args(name, value, unit));
	}
}

void ConsoleReportFormatter::AddFieldFloat(std::wstring_view name, float value, std::wstring_view unit /*= {}*/)
{
	assert(!name.empty());
	PushElement();
	if (unit.empty())
	{
		Printer::PrintFormat(L"{} = {}", std::make_wformat_args(name, value));
	}
	else
	{
		Printer::PrintFormat(L"{} = {} {}", std::make_wformat_args(name, value, unit));
	}
}

void ConsoleReportFormatter::AddFieldEnum(std::wstring_view name, uint32_t value, const EnumItem* enumItems)
{
	assert(!name.empty());
	PushElement();
	const wchar_t* enumItemName = FindEnumItemName(value, enumItems);
	if (enumItemName == nullptr)
	{
		enumItemName = L"Unknown";
	}

	Printer::PrintFormat(L"{} = {} (0x{:X})", std::make_wformat_args(name, enumItemName, value));
}

void ConsoleReportFormatter::AddFieldEnumSigned(std::wstring_view name, int32_t value, const EnumItem* enumItems)
{
	assert(!name.empty());
	PushElement();
	const wchar_t* enumItemName = FindEnumItemName(value, enumItems);
	if (enumItemName == nullptr)
	{
		enumItemName = L"Unknown";
	}

	Printer::PrintFormat(L"{} = {} ({})", std::make_wformat_args(name, enumItemName, value));
}

void ConsoleReportFormatter::AddEnumArray(std::wstring_view name, const uint32_t* values, size_t count, const EnumItem* enumItems)
{
	assert(!name.empty());
	PushElement();
	Printer::PrintFormat(L"{}", std::make_wformat_args(name));
	++m_IndentLevel;
	for (size_t i = 0; i < count; ++i)
	{
		Printer::PrintNewLine();
		PrintIndent();
		const wchar_t* enumItemName = FindEnumItemName(values[i], enumItems);
		if (enumItemName == nullptr)
		{
			enumItemName = L"Unknown";
		}
		Printer::PrintFormat(L"[{}] = {} (0x{:X})", std::make_wformat_args(i, enumItemName, values[i]));
	}
	--m_IndentLevel;
}

void ConsoleReportFormatter::AddFieldFlags(std::wstring_view name, uint32_t value, const EnumItem* enumItems)
{
	assert(!name.empty());
	PushElement();
	Printer::PrintFormat(L"{} = 0x{:X}", std::make_wformat_args(name, value));

	++m_IndentLevel;
	size_t zeroFlagIndex = SIZE_MAX;
	for (size_t i = 0; enumItems[i].m_Name != nullptr; ++i)
	{
		if (enumItems[i].m_Value == 0)
		{
			zeroFlagIndex = i;
		}
		else
		{
			if ((value & enumItems[i].m_Value) != 0)
			{
				Printer::PrintNewLine();
				PrintIndent();
				Printer::PrintString(enumItems[i].m_Name);
			}
		}
	}
	if (value == 0 && zeroFlagIndex != SIZE_MAX)
	{
		Printer::PrintNewLine();
		PrintIndent();
		Printer::PrintString(enumItems[zeroFlagIndex].m_Name);
	}
	--m_IndentLevel;
}

void ConsoleReportFormatter::AddFieldHexBytes(std::wstring_view name, const void* data, size_t byteCount)
{
	std::wstring valStr;
	for (size_t i = 0; i < byteCount; ++i)
	{
		valStr += std::format(L"{:02X}", *((const uint8_t*)data + i));
	}
	AddFieldString(name, valStr);
}

void ConsoleReportFormatter::AddFieldVendorId(std::wstring_view name, uint32_t value)
{
	assert(!name.empty());

	auto ACPIIDOpt = DecodeACPIID(value);

	if (ACPIIDOpt.has_value())
	{
		PushElement();
		auto& ACPIID = ACPIIDOpt.value();
		const wchar_t* enumItemName = FindEnumItemName(value, Enum_VendorId);
		if (enumItemName == nullptr)
		{
			enumItemName = L"Unknown";
		}

		Printer::PrintFormat(L"{} = {} \"{}\" (0x{:X})", std::make_wformat_args(name, enumItemName, ACPIID, value));
	}
	else
	{
		AddFieldEnum(name, value, Enum_VendorId);
	}

}

void ConsoleReportFormatter::AddFieldSubsystemId(std::wstring_view name, uint32_t value)
{
	assert(!name.empty());
	PushElement();

	const wchar_t* enumItemName = FindEnumItemName(value & 0xFFFF, Enum_SubsystemVendorId);
	if (enumItemName == nullptr)
	{
		enumItemName = L"Unknown";
	}

	Printer::PrintFormat(L"{} = {} (0x{:X})", std::make_wformat_args(name, enumItemName, value));
}

void ConsoleReportFormatter::AddFieldMicrosoftVersion(std::wstring_view name, uint64_t value)
{
	assert(!name.empty());
	PushElement();
	Printer::PrintFormat(L"{} = {}.{}.{}.{}", std::make_wformat_args(name, value >> 48, (value >> 32) & 0xFFFF, (value >> 16) & 0xFFFF, value & 0xFFFF));
}

void ConsoleReportFormatter::AddFieldAMDVersion(std::wstring_view name, uint64_t value)
{
	assert(!name.empty());
	PushElement();
	Printer::PrintFormat(L"{} = {}.{}.{}", std::make_wformat_args(name, value >> 22, (value >> 12) & 0b11'1111'1111, value & 0b1111'1111'1111));
}

void ConsoleReportFormatter::AddFieldNvidiaImplementationID(std::wstring_view name, uint32_t architectureId, uint32_t implementationId, const EnumItem* architecturePlusImplementationIDEnum)
{
	// Prints only implementationId as the numerical value, but searches enum
	// using architectureId + implementationId.

	assert(!name.empty());
	PushElement();

	const wchar_t* enumItemName = FindEnumItemName(architectureId + implementationId,
		architecturePlusImplementationIDEnum);
	if (enumItemName == nullptr)
	{
		enumItemName = L"Unknown";
	}

	Printer::PrintFormat(L"{} = {} (0x{:X})", std::make_wformat_args(name, enumItemName, implementationId));
}

void ConsoleReportFormatter::PrintIndent() const
{
	Printer::PrintString(std::wstring(INDENT_SIZE * m_IndentLevel, INDENT_CHAR));
}

void ConsoleReportFormatter::PushElement()
{
	m_ScopeStack.top().ElementCount++;
	Printer::PrintNewLine();
	PrintIndent();
}

void ConsoleReportFormatter::PrintDivider(size_t size)
{
	Printer::PrintNewLine();
	PrintIndent();
	wchar_t dividerChar;

	switch (m_IndentLevel)
	{
	case 0:
		dividerChar = L'=';
		break;
	default:
		dividerChar = L'-';
		break;
	}

	Printer::PrintString(std::wstring(size, dividerChar));
}

std::optional<std::wstring> ConsoleReportFormatter::DecodeACPIID(uint32_t value)
{
	if (value <= 0xFFFF)
	{
		return std::nullopt;
	}

	std::wstring result;
	result.resize(4);

	for (uint32_t i = 0; i < 4; ++i)
	{
		const uint8_t charValue = (uint8_t)(value >> (i * 8));
		if (charValue < 32 || charValue > 126)
			return std::nullopt;
		result[i] = (wchar_t)charValue;
	}
	return result;
}
