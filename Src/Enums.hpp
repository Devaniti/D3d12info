/*
This file is part of D3d12info project:
https://github.com/sawickiap/D3d12info

Copyright (c) 2018-2024 Adam Sawicki, https://asawicki.info
License: MIT

For more information, see files README.md, LICENSE.txt.
*/
#pragma once

#include <unordered_map>

struct EnumItem
{
	const wchar_t* m_Name;
	uint32_t m_Value;
};

class EnumCollection
{
public:
	std::unordered_map<wstring, const EnumItem*> m_Enums;

	static EnumCollection& GetInstance()
	{
		static EnumCollection obj;
		return obj;
	}

	void Add(const wchar_t* enumName, const EnumItem* items)
	{
		m_Enums.insert({enumName, items});
	}
};

class EnumRegistration
{
public:
	EnumRegistration(const wchar_t* enumName, const EnumItem* items)
	{
		EnumCollection::GetInstance().Add(enumName, items);
	}
};

#define ENUM_BEGIN(name)   static const EnumItem Enum_ ## name[] = {
#define ENUM_END(name)   { NULL, UINT32_MAX } }; \
	static EnumRegistration g_Enum_ ## name ## _Registration(L"" #name, Enum_ ## name);
#define ENUM_ITEM(name)   { L"" #name, uint32_t(name) },

// If not found, returns null.
inline const wchar_t* FindEnumItemName(uint32_t value, const EnumItem* items)
{
	for(size_t i = 0; items[i].m_Name != nullptr; ++i)
	{
		if(items[i].m_Value == value)
			return items[i].m_Name;
	}
	return nullptr;
}

////////////////////////////////////////////////////////////////////////////////
// Other enums

static const EnumItem Enum_VendorId[] = {
	// PCI IDs
	{ L"AMD/ATI",   0x1002 },
	{ L"AMD",		0x1022 },
	{ L"NVIDIA",	0x10de },
	{ L"Microsoft", 0x1414 },
	{ L"Parallels",	0x1ab8 },
	{ L"Qualcomm",	0x5143 },
	{ L"Intel",		0x8086 },
	// ACPI IDs
	{ L"Parallels", 0x344C5250 }, // "PRL4"
	{ L"NVIDIA", 0x4144564E	},    // "NVDA"
	{ L"Intel", 0x43544E49 },     // "INTC"
	{ L"Intel", 0x4C544E49 },     // "INTL"
	{ L"AMD", 0x49444D41 },       // "AMDI"
	{ L"Intel", 0x49504341 },     // "ACPI"
	{ L"Qualcomm", 0x4D4F4351 },  // "QCOM"
	{ L"Microsoft", 0x5446534D }, // "MSFT"
	{ L"Microsoft", 0x5748534D }, // "MSHW"
	{ L"Microsoft", 0x5941534D }, // "MSAY"
	{ NULL, UINT32_MAX } };
static EnumRegistration g_Enum_VendorId_Registration(L"VendorId", Enum_VendorId);

static const EnumItem Enum_SubsystemVendorId[] = {
    { L"AMD/ATI",            0x1002 },
    { L"AMD",                0x1022 },
    { L"Acer",               0x1025 },
    { L"Dell",               0x1028 },
    { L"HP",                 0x103c },
    { L"ASUS",               0x1043 },
    { L"Sony",               0x104d },
    { L"Apple",              0x106b },
    { L"Gateway",            0x107b },
    { L"Diamond Multimedia", 0x106b },
    { L"NVIDIA",             0x10de },
    { L"Toshiba",            0x1179 },
    { L"Microsoft",          0x1414 },
    { L"Gigabyte",           0x1458 },
    { L"MSI",                0x1462 },
    { L"PowerColor",         0x148c },
    { L"VisionTek",          0x1545 },
    { L"Palit",              0x1569 },
    { L"XFX",                0x1682 },
    { L"Jetway",             0x16f3 },
    { L"Lenovo",             0x17aa },
    { L"HIS",                0x17af },
    { L"ASRock",             0x1849 },
    { L"GeCube",             0x18bc },
    { L"Club 3D",            0x196d },
    { L"PNY",                0x196e },
    { L"Razer",              0x1a58 },
    { L"Parallels",          0x1ab8 },
    { L"Sapphire",           0x1da2 },
    { L"Qualcomm",           0x5143 },
    { L"Intel",              0x8086 },
	{ NULL, UINT32_MAX } };
static EnumRegistration g_Enum_SubsystemVendorId_Registration(L"SubsystemVendorId", Enum_SubsystemVendorId);

////////////////////////////////////////////////////////////////////////////////
// WinAPI enums

ENUM_BEGIN(VER_SUITE)
	ENUM_ITEM(VER_SUITE_BACKOFFICE)
	ENUM_ITEM(VER_SUITE_BLADE)
	ENUM_ITEM(VER_SUITE_COMPUTE_SERVER)
	ENUM_ITEM(VER_SUITE_DATACENTER)
	ENUM_ITEM(VER_SUITE_ENTERPRISE)
	ENUM_ITEM(VER_SUITE_EMBEDDEDNT)
	ENUM_ITEM(VER_SUITE_PERSONAL)
	ENUM_ITEM(VER_SUITE_SINGLEUSERTS)
	ENUM_ITEM(VER_SUITE_SMALLBUSINESS)
	ENUM_ITEM(VER_SUITE_SMALLBUSINESS_RESTRICTED)
	ENUM_ITEM(VER_SUITE_STORAGE_SERVER)
	ENUM_ITEM(VER_SUITE_TERMINAL)
	ENUM_ITEM(VER_SUITE_WH_SERVER)
ENUM_END(VER_SUITE)

ENUM_BEGIN(VER_NT)
	ENUM_ITEM(VER_NT_WORKSTATION)
	ENUM_ITEM(VER_NT_DOMAIN_CONTROLLER)
	ENUM_ITEM(VER_NT_SERVER)
ENUM_END(VER_NT)

////////////////////////////////////////////////////////////////////////////////
// D3D12 enums

ENUM_BEGIN(DXGI_FORMAT)
	ENUM_ITEM(DXGI_FORMAT_UNKNOWN	                             )
	ENUM_ITEM(DXGI_FORMAT_R32G32B32A32_TYPELESS                  )
	ENUM_ITEM(DXGI_FORMAT_R32G32B32A32_FLOAT                     )
	ENUM_ITEM(DXGI_FORMAT_R32G32B32A32_UINT                      )
	ENUM_ITEM(DXGI_FORMAT_R32G32B32A32_SINT                      )
	ENUM_ITEM(DXGI_FORMAT_R32G32B32_TYPELESS                     )
	ENUM_ITEM(DXGI_FORMAT_R32G32B32_FLOAT                        )
	ENUM_ITEM(DXGI_FORMAT_R32G32B32_UINT                         )
	ENUM_ITEM(DXGI_FORMAT_R32G32B32_SINT                         )
	ENUM_ITEM(DXGI_FORMAT_R16G16B16A16_TYPELESS                  )
	ENUM_ITEM(DXGI_FORMAT_R16G16B16A16_FLOAT                     )
	ENUM_ITEM(DXGI_FORMAT_R16G16B16A16_UNORM                     )
	ENUM_ITEM(DXGI_FORMAT_R16G16B16A16_UINT                      )
	ENUM_ITEM(DXGI_FORMAT_R16G16B16A16_SNORM                     )
	ENUM_ITEM(DXGI_FORMAT_R16G16B16A16_SINT                      )
	ENUM_ITEM(DXGI_FORMAT_R32G32_TYPELESS                        )
	ENUM_ITEM(DXGI_FORMAT_R32G32_FLOAT                           )
	ENUM_ITEM(DXGI_FORMAT_R32G32_UINT                            )
	ENUM_ITEM(DXGI_FORMAT_R32G32_SINT                            )
	ENUM_ITEM(DXGI_FORMAT_R32G8X24_TYPELESS                      )
	ENUM_ITEM(DXGI_FORMAT_D32_FLOAT_S8X24_UINT                   )
	ENUM_ITEM(DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS               )
	ENUM_ITEM(DXGI_FORMAT_X32_TYPELESS_G8X24_UINT                )
	ENUM_ITEM(DXGI_FORMAT_R10G10B10A2_TYPELESS                   )
	ENUM_ITEM(DXGI_FORMAT_R10G10B10A2_UNORM                      )
	ENUM_ITEM(DXGI_FORMAT_R10G10B10A2_UINT                       )
	ENUM_ITEM(DXGI_FORMAT_R11G11B10_FLOAT                        )
	ENUM_ITEM(DXGI_FORMAT_R8G8B8A8_TYPELESS                      )
	ENUM_ITEM(DXGI_FORMAT_R8G8B8A8_UNORM                         )
	ENUM_ITEM(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB                    )
	ENUM_ITEM(DXGI_FORMAT_R8G8B8A8_UINT                          )
	ENUM_ITEM(DXGI_FORMAT_R8G8B8A8_SNORM                         )
	ENUM_ITEM(DXGI_FORMAT_R8G8B8A8_SINT                          )
	ENUM_ITEM(DXGI_FORMAT_R16G16_TYPELESS                        )
	ENUM_ITEM(DXGI_FORMAT_R16G16_FLOAT                           )
	ENUM_ITEM(DXGI_FORMAT_R16G16_UNORM                           )
	ENUM_ITEM(DXGI_FORMAT_R16G16_UINT                            )
	ENUM_ITEM(DXGI_FORMAT_R16G16_SNORM                           )
	ENUM_ITEM(DXGI_FORMAT_R16G16_SINT                            )
	ENUM_ITEM(DXGI_FORMAT_R32_TYPELESS                           )
	ENUM_ITEM(DXGI_FORMAT_D32_FLOAT                              )
	ENUM_ITEM(DXGI_FORMAT_R32_FLOAT                              )
	ENUM_ITEM(DXGI_FORMAT_R32_UINT                               )
	ENUM_ITEM(DXGI_FORMAT_R32_SINT                               )
	ENUM_ITEM(DXGI_FORMAT_R24G8_TYPELESS                         )
	ENUM_ITEM(DXGI_FORMAT_D24_UNORM_S8_UINT                      )
	ENUM_ITEM(DXGI_FORMAT_R24_UNORM_X8_TYPELESS                  )
	ENUM_ITEM(DXGI_FORMAT_X24_TYPELESS_G8_UINT                   )
	ENUM_ITEM(DXGI_FORMAT_R8G8_TYPELESS                          )
	ENUM_ITEM(DXGI_FORMAT_R8G8_UNORM                             )
	ENUM_ITEM(DXGI_FORMAT_R8G8_UINT                              )
	ENUM_ITEM(DXGI_FORMAT_R8G8_SNORM                             )
	ENUM_ITEM(DXGI_FORMAT_R8G8_SINT                              )
	ENUM_ITEM(DXGI_FORMAT_R16_TYPELESS                           )
	ENUM_ITEM(DXGI_FORMAT_R16_FLOAT                              )
	ENUM_ITEM(DXGI_FORMAT_D16_UNORM                              )
	ENUM_ITEM(DXGI_FORMAT_R16_UNORM                              )
	ENUM_ITEM(DXGI_FORMAT_R16_UINT                               )
	ENUM_ITEM(DXGI_FORMAT_R16_SNORM                              )
	ENUM_ITEM(DXGI_FORMAT_R16_SINT                               )
	ENUM_ITEM(DXGI_FORMAT_R8_TYPELESS                            )
	ENUM_ITEM(DXGI_FORMAT_R8_UNORM                               )
	ENUM_ITEM(DXGI_FORMAT_R8_UINT                                )
	ENUM_ITEM(DXGI_FORMAT_R8_SNORM                               )
	ENUM_ITEM(DXGI_FORMAT_R8_SINT                                )
	ENUM_ITEM(DXGI_FORMAT_A8_UNORM                               )
	ENUM_ITEM(DXGI_FORMAT_R1_UNORM                               )
	ENUM_ITEM(DXGI_FORMAT_R9G9B9E5_SHAREDEXP                     )
	ENUM_ITEM(DXGI_FORMAT_R8G8_B8G8_UNORM                        )
	ENUM_ITEM(DXGI_FORMAT_G8R8_G8B8_UNORM                        )
	ENUM_ITEM(DXGI_FORMAT_BC1_TYPELESS                           )
	ENUM_ITEM(DXGI_FORMAT_BC1_UNORM                              )
	ENUM_ITEM(DXGI_FORMAT_BC1_UNORM_SRGB                         )
	ENUM_ITEM(DXGI_FORMAT_BC2_TYPELESS                           )
	ENUM_ITEM(DXGI_FORMAT_BC2_UNORM                              )
	ENUM_ITEM(DXGI_FORMAT_BC2_UNORM_SRGB                         )
	ENUM_ITEM(DXGI_FORMAT_BC3_TYPELESS                           )
	ENUM_ITEM(DXGI_FORMAT_BC3_UNORM                              )
	ENUM_ITEM(DXGI_FORMAT_BC3_UNORM_SRGB                         )
	ENUM_ITEM(DXGI_FORMAT_BC4_TYPELESS                           )
	ENUM_ITEM(DXGI_FORMAT_BC4_UNORM                              )
	ENUM_ITEM(DXGI_FORMAT_BC4_SNORM                              )
	ENUM_ITEM(DXGI_FORMAT_BC5_TYPELESS                           )
	ENUM_ITEM(DXGI_FORMAT_BC5_UNORM                              )
	ENUM_ITEM(DXGI_FORMAT_BC5_SNORM                              )
	ENUM_ITEM(DXGI_FORMAT_B5G6R5_UNORM                           )
	ENUM_ITEM(DXGI_FORMAT_B5G5R5A1_UNORM                         )
	ENUM_ITEM(DXGI_FORMAT_B8G8R8A8_UNORM                         )
	ENUM_ITEM(DXGI_FORMAT_B8G8R8X8_UNORM                         )
	ENUM_ITEM(DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM             )
	ENUM_ITEM(DXGI_FORMAT_B8G8R8A8_TYPELESS                      )
	ENUM_ITEM(DXGI_FORMAT_B8G8R8A8_UNORM_SRGB                    )
	ENUM_ITEM(DXGI_FORMAT_B8G8R8X8_TYPELESS                      )
	ENUM_ITEM(DXGI_FORMAT_B8G8R8X8_UNORM_SRGB                    )
	ENUM_ITEM(DXGI_FORMAT_BC6H_TYPELESS                          )
	ENUM_ITEM(DXGI_FORMAT_BC6H_UF16                              )
	ENUM_ITEM(DXGI_FORMAT_BC6H_SF16                              )
	ENUM_ITEM(DXGI_FORMAT_BC7_TYPELESS                           )
	ENUM_ITEM(DXGI_FORMAT_BC7_UNORM                              )
	ENUM_ITEM(DXGI_FORMAT_BC7_UNORM_SRGB                         )
	ENUM_ITEM(DXGI_FORMAT_AYUV                                   )
	ENUM_ITEM(DXGI_FORMAT_Y410                                   )
	ENUM_ITEM(DXGI_FORMAT_Y416                                   )
	ENUM_ITEM(DXGI_FORMAT_NV12                                   )
	ENUM_ITEM(DXGI_FORMAT_P010                                   )
	ENUM_ITEM(DXGI_FORMAT_P016                                   )
	ENUM_ITEM(DXGI_FORMAT_420_OPAQUE                             )
	ENUM_ITEM(DXGI_FORMAT_YUY2                                   )
	ENUM_ITEM(DXGI_FORMAT_Y210                                   )
	ENUM_ITEM(DXGI_FORMAT_Y216                                   )
	ENUM_ITEM(DXGI_FORMAT_NV11                                   )
	ENUM_ITEM(DXGI_FORMAT_AI44                                   )
	ENUM_ITEM(DXGI_FORMAT_IA44                                   )
	ENUM_ITEM(DXGI_FORMAT_P8                                     )
	ENUM_ITEM(DXGI_FORMAT_A8P8                                   )
	ENUM_ITEM(DXGI_FORMAT_B4G4R4A4_UNORM                         )
	ENUM_ITEM(DXGI_FORMAT_P208                                   )
	ENUM_ITEM(DXGI_FORMAT_V208                                   )
	ENUM_ITEM(DXGI_FORMAT_V408                                   )
	ENUM_ITEM(DXGI_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE        )
	ENUM_ITEM(DXGI_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE)
	ENUM_ITEM(DXGI_FORMAT_A4B4G4R4_UNORM                         )
ENUM_END(DXGI_FORMAT)

ENUM_BEGIN(D3D12_DEPTH_WRITE_MASK)
	ENUM_ITEM(D3D12_DEPTH_WRITE_MASK_ZERO)
	ENUM_ITEM(D3D12_DEPTH_WRITE_MASK_ALL)
ENUM_END(D3D12_DEPTH_WRITE_MASK)

ENUM_BEGIN(D3D12_SHADER_MIN_PRECISION_SUPPORT)
	ENUM_ITEM(D3D12_SHADER_MIN_PRECISION_SUPPORT_NONE)
	ENUM_ITEM(D3D12_SHADER_MIN_PRECISION_SUPPORT_10_BIT)
	ENUM_ITEM(D3D12_SHADER_MIN_PRECISION_SUPPORT_16_BIT)
ENUM_END(D3D12_SHADER_MIN_PRECISION_SUPPORT)

ENUM_BEGIN(D3D12_TILED_RESOURCES_TIER)
	ENUM_ITEM(D3D12_TILED_RESOURCES_TIER_NOT_SUPPORTED)
	ENUM_ITEM(D3D12_TILED_RESOURCES_TIER_1)
	ENUM_ITEM(D3D12_TILED_RESOURCES_TIER_2)
	ENUM_ITEM(D3D12_TILED_RESOURCES_TIER_3)
	ENUM_ITEM(D3D12_TILED_RESOURCES_TIER_4)
ENUM_END(D3D12_TILED_RESOURCES_TIER)

ENUM_BEGIN(D3D12_RESOURCE_BINDING_TIER)
	ENUM_ITEM(D3D12_RESOURCE_BINDING_TIER_1)
	ENUM_ITEM(D3D12_RESOURCE_BINDING_TIER_2)
	ENUM_ITEM(D3D12_RESOURCE_BINDING_TIER_3)
ENUM_END(D3D12_RESOURCE_BINDING_TIER)

ENUM_BEGIN(D3D12_CONSERVATIVE_RASTERIZATION_TIER)
	ENUM_ITEM(D3D12_CONSERVATIVE_RASTERIZATION_TIER_NOT_SUPPORTED)
	ENUM_ITEM(D3D12_CONSERVATIVE_RASTERIZATION_TIER_1)
	ENUM_ITEM(D3D12_CONSERVATIVE_RASTERIZATION_TIER_2)
	ENUM_ITEM(D3D12_CONSERVATIVE_RASTERIZATION_TIER_3)
ENUM_END(D3D12_CONSERVATIVE_RASTERIZATION_TIER)

ENUM_BEGIN(D3D12_CROSS_NODE_SHARING_TIER)
	ENUM_ITEM(D3D12_CROSS_NODE_SHARING_TIER_NOT_SUPPORTED)
	ENUM_ITEM(D3D12_CROSS_NODE_SHARING_TIER_1_EMULATED)
	ENUM_ITEM(D3D12_CROSS_NODE_SHARING_TIER_1)
	ENUM_ITEM(D3D12_CROSS_NODE_SHARING_TIER_2)
	ENUM_ITEM(D3D12_CROSS_NODE_SHARING_TIER_3)
ENUM_END(D3D12_CROSS_NODE_SHARING_TIER)

ENUM_BEGIN(D3D12_RESOURCE_HEAP_TIER)
	ENUM_ITEM(D3D12_RESOURCE_HEAP_TIER_1)
	ENUM_ITEM(D3D12_RESOURCE_HEAP_TIER_2)
ENUM_END(D3D12_RESOURCE_HEAP_TIER)

ENUM_BEGIN(DXGI_ADAPTER_FLAG)
	ENUM_ITEM(DXGI_ADAPTER_FLAG_NONE)
	ENUM_ITEM(DXGI_ADAPTER_FLAG_REMOTE)
	ENUM_ITEM(DXGI_ADAPTER_FLAG_SOFTWARE)
	ENUM_ITEM(DXGI_ADAPTER_FLAG3_ACG_COMPATIBLE)
	ENUM_ITEM(DXGI_ADAPTER_FLAG3_SUPPORT_MONITORED_FENCES)
	ENUM_ITEM(DXGI_ADAPTER_FLAG3_SUPPORT_NON_MONITORED_FENCES)
	ENUM_ITEM(DXGI_ADAPTER_FLAG3_KEYED_MUTEX_CONFORMANCE)
ENUM_END(DXGI_ADAPTER_FLAG)

ENUM_BEGIN(D3D_FEATURE_LEVEL)
	ENUM_ITEM(D3D_FEATURE_LEVEL_1_0_CORE)
	ENUM_ITEM(D3D_FEATURE_LEVEL_9_1)
	ENUM_ITEM(D3D_FEATURE_LEVEL_9_2)
	ENUM_ITEM(D3D_FEATURE_LEVEL_9_3)
	ENUM_ITEM(D3D_FEATURE_LEVEL_10_0)
	ENUM_ITEM(D3D_FEATURE_LEVEL_10_1)
	ENUM_ITEM(D3D_FEATURE_LEVEL_11_0)
	ENUM_ITEM(D3D_FEATURE_LEVEL_11_1)
	ENUM_ITEM(D3D_FEATURE_LEVEL_12_0)
	ENUM_ITEM(D3D_FEATURE_LEVEL_12_1)
	ENUM_ITEM(D3D_FEATURE_LEVEL_12_2)
ENUM_END(D3D_FEATURE_LEVEL)

ENUM_BEGIN(D3D_SHADER_MODEL)
	ENUM_ITEM(D3D_SHADER_MODEL_5_1)
	ENUM_ITEM(D3D_SHADER_MODEL_6_0)
	ENUM_ITEM(D3D_SHADER_MODEL_6_1)
	ENUM_ITEM(D3D_SHADER_MODEL_6_2)
	ENUM_ITEM(D3D_SHADER_MODEL_6_3)
	ENUM_ITEM(D3D_SHADER_MODEL_6_4)
	ENUM_ITEM(D3D_SHADER_MODEL_6_5)
	ENUM_ITEM(D3D_SHADER_MODEL_6_6)
	ENUM_ITEM(D3D_SHADER_MODEL_6_7)
	ENUM_ITEM(D3D_SHADER_MODEL_6_8)
	#ifndef USE_PREVIEW_AGILITY_SDK
		ENUM_ITEM(D3D_SHADER_MODEL_6_9)
	#endif
ENUM_END(D3D_SHADER_MODEL)

ENUM_BEGIN(D3D_ROOT_SIGNATURE_VERSION)
	ENUM_ITEM(D3D_ROOT_SIGNATURE_VERSION_1)
	ENUM_ITEM(D3D_ROOT_SIGNATURE_VERSION_1_0)
	ENUM_ITEM(D3D_ROOT_SIGNATURE_VERSION_1_1)
	ENUM_ITEM(D3D_ROOT_SIGNATURE_VERSION_1_2)
ENUM_END(D3D_ROOT_SIGNATURE_VERSION)

ENUM_BEGIN(D3D12_PROGRAMMABLE_SAMPLE_POSITIONS_TIER)
	ENUM_ITEM(D3D12_PROGRAMMABLE_SAMPLE_POSITIONS_TIER_NOT_SUPPORTED)
	ENUM_ITEM(D3D12_PROGRAMMABLE_SAMPLE_POSITIONS_TIER_1)
	ENUM_ITEM(D3D12_PROGRAMMABLE_SAMPLE_POSITIONS_TIER_2)
ENUM_END(D3D12_PROGRAMMABLE_SAMPLE_POSITIONS_TIER)

ENUM_BEGIN(D3D12_SHADER_CACHE_SUPPORT_FLAGS)
	ENUM_ITEM(D3D12_SHADER_CACHE_SUPPORT_NONE)
	ENUM_ITEM(D3D12_SHADER_CACHE_SUPPORT_SINGLE_PSO)
	ENUM_ITEM(D3D12_SHADER_CACHE_SUPPORT_LIBRARY)
	ENUM_ITEM(D3D12_SHADER_CACHE_SUPPORT_AUTOMATIC_INPROC_CACHE)
	ENUM_ITEM(D3D12_SHADER_CACHE_SUPPORT_AUTOMATIC_DISK_CACHE)
	ENUM_ITEM(D3D12_SHADER_CACHE_SUPPORT_DRIVER_MANAGED_CACHE)
ENUM_END(D3D12_SHADER_CACHE_SUPPORT_FLAGS)

ENUM_BEGIN(D3D12_HEAP_SERIALIZATION_TIER)
	ENUM_ITEM(D3D12_HEAP_SERIALIZATION_TIER_0)
	ENUM_ITEM(D3D12_HEAP_SERIALIZATION_TIER_10)
ENUM_END(D3D12_HEAP_SERIALIZATION_TIER)

ENUM_BEGIN(D3D12_COMMAND_LIST_SUPPORT_FLAGS)
	ENUM_ITEM(D3D12_COMMAND_LIST_SUPPORT_FLAG_NONE)
	ENUM_ITEM(D3D12_COMMAND_LIST_SUPPORT_FLAG_DIRECT)
	ENUM_ITEM(D3D12_COMMAND_LIST_SUPPORT_FLAG_BUNDLE)
	ENUM_ITEM(D3D12_COMMAND_LIST_SUPPORT_FLAG_COMPUTE)
	ENUM_ITEM(D3D12_COMMAND_LIST_SUPPORT_FLAG_COPY)
	ENUM_ITEM(D3D12_COMMAND_LIST_SUPPORT_FLAG_VIDEO_DECODE)
	ENUM_ITEM(D3D12_COMMAND_LIST_SUPPORT_FLAG_VIDEO_PROCESS)
	ENUM_ITEM(D3D12_COMMAND_LIST_SUPPORT_FLAG_VIDEO_ENCODE)
ENUM_END(D3D12_COMMAND_LIST_SUPPORT_FLAGS)

ENUM_BEGIN(D3D12_VIEW_INSTANCING_TIER)
	ENUM_ITEM(D3D12_VIEW_INSTANCING_TIER_NOT_SUPPORTED)
	ENUM_ITEM(D3D12_VIEW_INSTANCING_TIER_1)
	ENUM_ITEM(D3D12_VIEW_INSTANCING_TIER_2)
	ENUM_ITEM(D3D12_VIEW_INSTANCING_TIER_3)
ENUM_END(D3D12_VIEW_INSTANCING_TIER)

ENUM_BEGIN(D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER)
	ENUM_ITEM(D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER_0)
	ENUM_ITEM(D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER_1)
	ENUM_ITEM(D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER_2)
ENUM_END(D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER)

ENUM_BEGIN(D3D12_RENDER_PASS_TIER)
	ENUM_ITEM(D3D12_RENDER_PASS_TIER_0)
	ENUM_ITEM(D3D12_RENDER_PASS_TIER_1)
	ENUM_ITEM(D3D12_RENDER_PASS_TIER_2)
ENUM_END(D3D12_RENDER_PASS_TIER)

ENUM_BEGIN(D3D12_RAYTRACING_TIER)
	ENUM_ITEM(D3D12_RAYTRACING_TIER_NOT_SUPPORTED)
	ENUM_ITEM(D3D12_RAYTRACING_TIER_1_0)
	ENUM_ITEM(D3D12_RAYTRACING_TIER_1_1)
ENUM_END(D3D12_RAYTRACING_TIER)

ENUM_BEGIN(D3D12_VARIABLE_SHADING_RATE_TIER)
	ENUM_ITEM(D3D12_VARIABLE_SHADING_RATE_TIER_NOT_SUPPORTED)
	ENUM_ITEM(D3D12_VARIABLE_SHADING_RATE_TIER_1)
	ENUM_ITEM(D3D12_VARIABLE_SHADING_RATE_TIER_2)
ENUM_END(D3D12_VARIABLE_SHADING_RATE_TIER)

ENUM_BEGIN(D3D12_MESH_SHADER_TIER)
	ENUM_ITEM(D3D12_MESH_SHADER_TIER_NOT_SUPPORTED)
	ENUM_ITEM(D3D12_MESH_SHADER_TIER_1)
ENUM_END(D3D12_MESH_SHADER_TIER)

ENUM_BEGIN(D3D12_SAMPLER_FEEDBACK_TIER)
	ENUM_ITEM(D3D12_SAMPLER_FEEDBACK_TIER_NOT_SUPPORTED)
	ENUM_ITEM(D3D12_SAMPLER_FEEDBACK_TIER_0_9)
	ENUM_ITEM(D3D12_SAMPLER_FEEDBACK_TIER_1_0)
ENUM_END(D3D12_SAMPLER_FEEDBACK_TIER)

ENUM_BEGIN(D3D12_WAVE_MMA_TIER)
	ENUM_ITEM(D3D12_WAVE_MMA_TIER_NOT_SUPPORTED)
	ENUM_ITEM(D3D12_WAVE_MMA_TIER_1_0)
ENUM_END(D3D12_WAVE_MMA_TIER)

ENUM_BEGIN(DXGI_GRAPHICS_PREEMPTION_GRANULARITY)
	ENUM_ITEM(DXGI_GRAPHICS_PREEMPTION_DMA_BUFFER_BOUNDARY)
	ENUM_ITEM(DXGI_GRAPHICS_PREEMPTION_PRIMITIVE_BOUNDARY)
	ENUM_ITEM(DXGI_GRAPHICS_PREEMPTION_TRIANGLE_BOUNDARY)
	ENUM_ITEM(DXGI_GRAPHICS_PREEMPTION_PIXEL_BOUNDARY)
	ENUM_ITEM(DXGI_GRAPHICS_PREEMPTION_INSTRUCTION_BOUNDARY)
ENUM_END(DXGI_GRAPHICS_PREEMPTION_GRANULARITY)

ENUM_BEGIN(DXGI_COMPUTE_PREEMPTION_GRANULARITY)
	ENUM_ITEM(DXGI_COMPUTE_PREEMPTION_DMA_BUFFER_BOUNDARY)
	ENUM_ITEM(DXGI_COMPUTE_PREEMPTION_DISPATCH_BOUNDARY)
	ENUM_ITEM(DXGI_COMPUTE_PREEMPTION_THREAD_GROUP_BOUNDARY)
	ENUM_ITEM(DXGI_COMPUTE_PREEMPTION_THREAD_BOUNDARY)
	ENUM_ITEM(DXGI_COMPUTE_PREEMPTION_INSTRUCTION_BOUNDARY)
ENUM_END(DXGI_COMPUTE_PREEMPTION_GRANULARITY)

ENUM_BEGIN(D3D12_FORMAT_SUPPORT1)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT1_NONE)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT1_BUFFER)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT1_IA_VERTEX_BUFFER)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT1_IA_INDEX_BUFFER)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT1_SO_BUFFER)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT1_TEXTURE1D)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT1_TEXTURE2D)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT1_TEXTURE3D)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT1_TEXTURECUBE)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT1_SHADER_LOAD)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT1_SHADER_SAMPLE)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT1_SHADER_SAMPLE_COMPARISON)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT1_SHADER_SAMPLE_MONO_TEXT)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT1_MIP)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT1_RENDER_TARGET)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT1_BLENDABLE)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT1_DEPTH_STENCIL)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT1_MULTISAMPLE_RESOLVE)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT1_DISPLAY)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT1_CAST_WITHIN_BIT_LAYOUT)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT1_MULTISAMPLE_RENDERTARGET)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT1_MULTISAMPLE_LOAD)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT1_SHADER_GATHER)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT1_BACK_BUFFER_CAST)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT1_TYPED_UNORDERED_ACCESS_VIEW)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT1_SHADER_GATHER_COMPARISON)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT1_DECODER_OUTPUT)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT1_VIDEO_PROCESSOR_OUTPUT)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT1_VIDEO_PROCESSOR_INPUT)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT1_VIDEO_ENCODER)
ENUM_END(D3D12_FORMAT_SUPPORT1)

ENUM_BEGIN(D3D12_FORMAT_SUPPORT2)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT2_NONE)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_ADD)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_BITWISE_OPS)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_COMPARE_STORE_OR_COMPARE_EXCHANGE)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_EXCHANGE)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_SIGNED_MIN_OR_MAX)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_UNSIGNED_MIN_OR_MAX)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT2_UAV_TYPED_LOAD)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT2_UAV_TYPED_STORE)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT2_OUTPUT_MERGER_LOGIC_OP)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT2_TILED)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT2_MULTIPLANE_OVERLAY)
	ENUM_ITEM(D3D12_FORMAT_SUPPORT2_SAMPLER_FEEDBACK)
ENUM_END(D3D12_FORMAT_SUPPORT2)

ENUM_BEGIN(D3D12_MULTISAMPLE_QUALITY_LEVEL_FLAGS)
	ENUM_ITEM(D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE)
	ENUM_ITEM(D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_TILED_RESOURCE)
ENUM_END(D3D12_MULTISAMPLE_QUALITY_LEVEL_FLAGS)

ENUM_BEGIN(D3D12_TRI_STATE)
	ENUM_ITEM(D3D12_TRI_STATE_UNKNOWN)
	ENUM_ITEM(D3D12_TRI_STATE_FALSE)
	ENUM_ITEM(D3D12_TRI_STATE_TRUE)
ENUM_END(D3D12_TRI_STATE)

ENUM_BEGIN(D3D12_WORK_GRAPHS_TIER)
	ENUM_ITEM(D3D12_WORK_GRAPHS_TIER_NOT_SUPPORTED)
	ENUM_ITEM(D3D12_WORK_GRAPHS_TIER_1_0)
#ifdef USE_PREVIEW_AGILITY_SDK
	ENUM_ITEM(D3D12_WORK_GRAPHS_TIER_1_1)
#endif
ENUM_END(D3D12_WORK_GRAPHS_TIER)

ENUM_BEGIN(D3D12_RECREATE_AT_TIER)
ENUM_ITEM(D3D12_RECREATE_AT_TIER_NOT_SUPPORTED)
ENUM_ITEM(D3D12_RECREATE_AT_TIER_1)
ENUM_END(D3D12_RECREATE_AT_TIER)

ENUM_BEGIN(D3D12_EXECUTE_INDIRECT_TIER)
	ENUM_ITEM(D3D12_EXECUTE_INDIRECT_TIER_1_0)
	ENUM_ITEM(D3D12_EXECUTE_INDIRECT_TIER_1_1)
ENUM_END(D3D12_EXECUTE_INDIRECT_TIER)

ENUM_BEGIN(D3D12_GRAPHICS_STATES)
	ENUM_ITEM(D3D12_GRAPHICS_STATE_NONE)
	ENUM_ITEM(D3D12_GRAPHICS_STATE_IA_VERTEX_BUFFERS)
	ENUM_ITEM(D3D12_GRAPHICS_STATE_IA_INDEX_BUFFER)
	ENUM_ITEM(D3D12_GRAPHICS_STATE_IA_PRIMITIVE_TOPOLOGY)
	ENUM_ITEM(D3D12_GRAPHICS_STATE_DESCRIPTOR_HEAP)
	ENUM_ITEM(D3D12_GRAPHICS_STATE_GRAPHICS_ROOT_SIGNATURE)
	ENUM_ITEM(D3D12_GRAPHICS_STATE_COMPUTE_ROOT_SIGNATURE)
	ENUM_ITEM(D3D12_GRAPHICS_STATE_RS_VIEWPORTS)
	ENUM_ITEM(D3D12_GRAPHICS_STATE_RS_SCISSOR_RECTS)
	ENUM_ITEM(D3D12_GRAPHICS_STATE_PREDICATION)
	ENUM_ITEM(D3D12_GRAPHICS_STATE_OM_RENDER_TARGETS)
	ENUM_ITEM(D3D12_GRAPHICS_STATE_OM_STENCIL_REF)
	ENUM_ITEM(D3D12_GRAPHICS_STATE_OM_BLEND_FACTOR)
	ENUM_ITEM(D3D12_GRAPHICS_STATE_PIPELINE_STATE)
	ENUM_ITEM(D3D12_GRAPHICS_STATE_SO_TARGETS)
	ENUM_ITEM(D3D12_GRAPHICS_STATE_OM_DEPTH_BOUNDS)
	ENUM_ITEM(D3D12_GRAPHICS_STATE_SAMPLE_POSITIONS)
	ENUM_ITEM(D3D12_GRAPHICS_STATE_VIEW_INSTANCE_MASK)
ENUM_END(D3D12_GRAPHICS_STATES)

ENUM_BEGIN(D3D12_META_COMMAND_PARAMETER_STAGE)
	ENUM_ITEM(D3D12_META_COMMAND_PARAMETER_STAGE_CREATION)
	ENUM_ITEM(D3D12_META_COMMAND_PARAMETER_STAGE_INITIALIZATION)
	ENUM_ITEM(D3D12_META_COMMAND_PARAMETER_STAGE_EXECUTION)
ENUM_END(D3D12_META_COMMAND_PARAMETER_STAGE)

ENUM_BEGIN(D3D12_META_COMMAND_PARAMETER_TYPE)
	ENUM_ITEM(D3D12_META_COMMAND_PARAMETER_TYPE_FLOAT)
	ENUM_ITEM(D3D12_META_COMMAND_PARAMETER_TYPE_UINT64)
	ENUM_ITEM(D3D12_META_COMMAND_PARAMETER_TYPE_GPU_VIRTUAL_ADDRESS)
	ENUM_ITEM(D3D12_META_COMMAND_PARAMETER_TYPE_CPU_DESCRIPTOR_HANDLE_HEAP_TYPE_CBV_SRV_UAV)
	ENUM_ITEM(D3D12_META_COMMAND_PARAMETER_TYPE_GPU_DESCRIPTOR_HANDLE_HEAP_TYPE_CBV_SRV_UAV)
ENUM_END(D3D12_META_COMMAND_PARAMETER_TYPE)

ENUM_BEGIN(D3D12_META_COMMAND_PARAMETER_FLAGS)
	ENUM_ITEM(D3D12_META_COMMAND_PARAMETER_FLAG_INPUT)
	ENUM_ITEM(D3D12_META_COMMAND_PARAMETER_FLAG_OUTPUT)
ENUM_END(D3D12_META_COMMAND_PARAMETER_FLAGS)

ENUM_BEGIN(D3D12_RESOURCE_STATES)
	ENUM_ITEM(D3D12_RESOURCE_STATE_COMMON)
	ENUM_ITEM(D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER)
	ENUM_ITEM(D3D12_RESOURCE_STATE_INDEX_BUFFER)
	ENUM_ITEM(D3D12_RESOURCE_STATE_RENDER_TARGET)
	ENUM_ITEM(D3D12_RESOURCE_STATE_UNORDERED_ACCESS)
	ENUM_ITEM(D3D12_RESOURCE_STATE_DEPTH_WRITE)
	ENUM_ITEM(D3D12_RESOURCE_STATE_DEPTH_READ)
	ENUM_ITEM(D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE)
	ENUM_ITEM(D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE)
	ENUM_ITEM(D3D12_RESOURCE_STATE_STREAM_OUT)
	ENUM_ITEM(D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT)
	ENUM_ITEM(D3D12_RESOURCE_STATE_COPY_DEST)
	ENUM_ITEM(D3D12_RESOURCE_STATE_COPY_SOURCE)
	ENUM_ITEM(D3D12_RESOURCE_STATE_RESOLVE_DEST)
	ENUM_ITEM(D3D12_RESOURCE_STATE_RESOLVE_SOURCE)
	ENUM_ITEM(D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE)
	ENUM_ITEM(D3D12_RESOURCE_STATE_SHADING_RATE_SOURCE)
	ENUM_ITEM(D3D12_RESOURCE_STATE_RESERVED_INTERNAL_8000)
	ENUM_ITEM(D3D12_RESOURCE_STATE_RESERVED_INTERNAL_4000)
	ENUM_ITEM(D3D12_RESOURCE_STATE_RESERVED_INTERNAL_100000)
	ENUM_ITEM(D3D12_RESOURCE_STATE_RESERVED_INTERNAL_40000000)
	ENUM_ITEM(D3D12_RESOURCE_STATE_RESERVED_INTERNAL_80000000)
	ENUM_ITEM(D3D12_RESOURCE_STATE_GENERIC_READ)
	ENUM_ITEM(D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE)
	//ENUM_ITEM(D3D12_RESOURCE_STATE_PRESENT) // It has value 0, like COMMON!
	ENUM_ITEM(D3D12_RESOURCE_STATE_PREDICATION)
	ENUM_ITEM(D3D12_RESOURCE_STATE_VIDEO_DECODE_READ)
	ENUM_ITEM(D3D12_RESOURCE_STATE_VIDEO_DECODE_WRITE)
	ENUM_ITEM(D3D12_RESOURCE_STATE_VIDEO_PROCESS_READ)
	ENUM_ITEM(D3D12_RESOURCE_STATE_VIDEO_PROCESS_WRITE)
	ENUM_ITEM(D3D12_RESOURCE_STATE_VIDEO_ENCODE_READ)
	ENUM_ITEM(D3D12_RESOURCE_STATE_VIDEO_ENCODE_WRITE)
ENUM_END(D3D12_RESOURCE_STATES)

#ifdef USE_PREVIEW_AGILITY_SDK

ENUM_BEGIN(DSR_SUPERRES_VARIANT_FLAGS)
	ENUM_ITEM(DSR_SUPERRES_VARIANT_FLAG_NONE)
	ENUM_ITEM(DSR_SUPERRES_VARIANT_FLAG_SUPPORTS_EXPOSURE_SCALE_TEXTURE)
	ENUM_ITEM(DSR_SUPERRES_VARIANT_FLAG_SUPPORTS_IGNORE_HISTORY_MASK)
	ENUM_ITEM(DSR_SUPERRES_VARIANT_FLAG_NATIVE)
	ENUM_ITEM(DSR_SUPERRES_VARIANT_FLAG_SUPPORTS_REACTIVE_MASK)
	ENUM_ITEM(DSR_SUPERRES_VARIANT_FLAG_SUPPORTS_SHARPNESS)
	ENUM_ITEM(DSR_SUPERRES_VARIANT_FLAG_DISALLOWS_REGION_OFFSETS)
ENUM_END(DSR_SUPERRES_VARIANT_FLAGS)

ENUM_BEGIN(DSR_OPTIMIZATION_TYPE)
	ENUM_ITEM(DSR_OPTIMIZATION_TYPE_BALANCED)
	ENUM_ITEM(DSR_OPTIMIZATION_TYPE_HIGH_QUALITY)
	ENUM_ITEM(DSR_OPTIMIZATION_TYPE_MAX_QUALITY)
	ENUM_ITEM(DSR_OPTIMIZATION_TYPE_HIGH_PERFORMANCE)
	ENUM_ITEM(DSR_OPTIMIZATION_TYPE_MAX_PERFORMANCE)
	ENUM_ITEM(DSR_OPTIMIZATION_TYPE_POWER_SAVING)
	ENUM_ITEM(DSR_OPTIMIZATION_TYPE_MAX_POWER_SAVING)
	ENUM_ITEM(DSR_NUM_OPTIMIZATION_TYPES)
ENUM_END(DSR_OPTIMIZATION_TYPE)

ENUM_BEGIN(D3D12_TIGHT_ALIGNMENT_TIER)
	ENUM_ITEM(D3D12_TIGHT_ALIGNMENT_TIER_NOT_SUPPORTED)
	ENUM_ITEM(D3D12_TIGHT_ALIGNMENT_TIER_1)
ENUM_END(D3D12_TIGHT_ALIGNMENT_TIER)

#endif // #ifdef USE_PREVIEW_AGILITY_SDK
