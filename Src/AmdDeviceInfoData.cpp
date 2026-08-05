/*
This file is part of D3d12info project:
https://github.com/sawickiap/D3d12info

Copyright (c) 2018-2026 Adam Sawicki, https://asawicki.info
License: MIT

For more information, see files README.md, LICENSE.txt.
*/
#include "AmdDeviceInfoData.hpp"

#include "Enums.hpp"
#include "ReportFormatter/ReportFormatter.hpp"
#include "Utils.hpp"

// Macro set by Cmake.
#if USE_AMD_DEVICE_INFO

////////////////////////////////////////////////////////////////////////////////
// PRIVATE

#include "ThirdParty/AMD_device_info/device_info.hpp"

// Don't forget to update to the date of the last commit when grabbing a new version!
static const wchar_t* AMD_DEVICE_INFO_COMPILED_VERSION = L"2026-06-01 (v1.0)";

ENUM_BEGIN(device_info_AsicType)
    ENUM_ITEM(device_info::AsicType::kUndefinedAsic)
    ENUM_ITEM(device_info::AsicType::kTahitiPro)
    ENUM_ITEM(device_info::AsicType::kTahitiXt)
    ENUM_ITEM(device_info::AsicType::kPitcairnPro)
    ENUM_ITEM(device_info::AsicType::kPitcairnXt)
    ENUM_ITEM(device_info::AsicType::kCapeVerdePro)
    ENUM_ITEM(device_info::AsicType::kCapeVerdeXt)
    ENUM_ITEM(device_info::AsicType::kOland)
    ENUM_ITEM(device_info::AsicType::kHainan)
    ENUM_ITEM(device_info::AsicType::kBonaire)
    ENUM_ITEM(device_info::AsicType::kHawaii)
    ENUM_ITEM(device_info::AsicType::kKalindi)
    ENUM_ITEM(device_info::AsicType::kSpectre)
    ENUM_ITEM(device_info::AsicType::kSpectreSl)
    ENUM_ITEM(device_info::AsicType::kSpectreLite)
    ENUM_ITEM(device_info::AsicType::kSpooky)
    ENUM_ITEM(device_info::AsicType::kIceland)
    ENUM_ITEM(device_info::AsicType::kTonga)
    ENUM_ITEM(device_info::AsicType::kCarrizo)
    ENUM_ITEM(device_info::AsicType::kCarrizoEmb)
    ENUM_ITEM(device_info::AsicType::kFiji)
    ENUM_ITEM(device_info::AsicType::kStoney)
    ENUM_ITEM(device_info::AsicType::kEllesmere)
    ENUM_ITEM(device_info::AsicType::kBaffin)
    ENUM_ITEM(device_info::AsicType::kGfx8_0_4)
    ENUM_ITEM(device_info::AsicType::kVegaM1)
    ENUM_ITEM(device_info::AsicType::kVegaM2)
    ENUM_ITEM(device_info::AsicType::kGfx9_0_0)
    ENUM_ITEM(device_info::AsicType::kGfx9_0_2)
    ENUM_ITEM(device_info::AsicType::kGfx9_0_4)
    ENUM_ITEM(device_info::AsicType::kGfx9_0_6)
    ENUM_ITEM(device_info::AsicType::kGfx9_0_9)
    ENUM_ITEM(device_info::AsicType::kGfx9_0_A)
    ENUM_ITEM(device_info::AsicType::kGfx9_0_C)
    ENUM_ITEM(device_info::AsicType::kGfx9_4_2)
    ENUM_ITEM(device_info::AsicType::kGfx9_5_0)
    ENUM_ITEM(device_info::AsicType::kGfx10_1_0)
    ENUM_ITEM(device_info::AsicType::kGfx10_1_0Xl)
    ENUM_ITEM(device_info::AsicType::kGfx10_1_2)
    ENUM_ITEM(device_info::AsicType::kGfx10_1_2X)
    ENUM_ITEM(device_info::AsicType::kGfx10_1_2Xt)
    ENUM_ITEM(device_info::AsicType::kGfx10_1_1)
    ENUM_ITEM(device_info::AsicType::kGfx10_3_0)
    ENUM_ITEM(device_info::AsicType::kGfx10_3_0Xt)
    ENUM_ITEM(device_info::AsicType::kGfx10_3_0Xtx)
    ENUM_ITEM(device_info::AsicType::kGfx10_3_1)
    ENUM_ITEM(device_info::AsicType::kGfx10_3_2)
    ENUM_ITEM(device_info::AsicType::kGfx10_3_2Xt)
    ENUM_ITEM(device_info::AsicType::kGfx10_3_3)
    ENUM_ITEM(device_info::AsicType::kGfx10_3_4)
    ENUM_ITEM(device_info::AsicType::kGfx10_3_5)
    ENUM_ITEM(device_info::AsicType::kGfx10_3_6)
    ENUM_ITEM(device_info::AsicType::kGfx11_0_0)
    ENUM_ITEM(device_info::AsicType::kGfx11_0_0Xt)
    ENUM_ITEM(device_info::AsicType::kGfx11_0_0Gre)
    ENUM_ITEM(device_info::AsicType::kGfx11_0_0M)
    ENUM_ITEM(device_info::AsicType::kGfx11_0_1)
    ENUM_ITEM(device_info::AsicType::kGfx11_0_1Xt)
    ENUM_ITEM(device_info::AsicType::kGfx11_0_2)
    ENUM_ITEM(device_info::AsicType::kGfx11_0_2Xt)
    ENUM_ITEM(device_info::AsicType::kGfx11_0_3)
    ENUM_ITEM(device_info::AsicType::kGfx11_0_3A)
    ENUM_ITEM(device_info::AsicType::kGfx11_0_3B)
    ENUM_ITEM(device_info::AsicType::kGfx11_5_0)
    ENUM_ITEM(device_info::AsicType::kGfx11_5_1)
    ENUM_ITEM(device_info::AsicType::kGfx11_5_2)
    ENUM_ITEM(device_info::AsicType::kGfx11_5_3)
    ENUM_ITEM(device_info::AsicType::kGfx11_5_3A)
    ENUM_ITEM(device_info::AsicType::kGfx12_0_0)
    ENUM_ITEM(device_info::AsicType::kGfx12_0_0Xt)
    ENUM_ITEM(device_info::AsicType::kGfx12_0_1Gre)
    ENUM_ITEM(device_info::AsicType::kGfx12_0_1)
    ENUM_ITEM(device_info::AsicType::kGfx12_0_1Xt)
    ENUM_ITEM(device_info::AsicType::kTotalAsics)
ENUM_END(device_info_AsicType)

ENUM_BEGIN(device_info_HwGeneration)
    ENUM_ITEM(device_info::HwGeneration::kUndefinedGeneration)
    ENUM_ITEM(device_info::HwGeneration::kNvidia)
    ENUM_ITEM(device_info::HwGeneration::kIntel)
    ENUM_ITEM(device_info::HwGeneration::kSouthernIsland)
    ENUM_ITEM(device_info::HwGeneration::kSeaIsland)
    ENUM_ITEM(device_info::HwGeneration::kVolcanicIsland)
    ENUM_ITEM(device_info::HwGeneration::kGfx9)
    ENUM_ITEM(device_info::HwGeneration::kGfx10)
    ENUM_ITEM(device_info::HwGeneration::kGfx10_3)
    ENUM_ITEM(device_info::HwGeneration::kGfx11)
    ENUM_ITEM(device_info::HwGeneration::kCdna)
    ENUM_ITEM(device_info::HwGeneration::kCdna2)
    ENUM_ITEM(device_info::HwGeneration::kCdna3)
    ENUM_ITEM(device_info::HwGeneration::kGfx12)
    ENUM_ITEM(device_info::HwGeneration::kCdna4)
    ENUM_ITEM(device_info::HwGeneration::kGfx11_5)
    ENUM_ITEM(device_info::HwGeneration::kTotalHwGenerations)
ENUM_END(device_info_HwGeneration)

////////////////////////////////////////////////////////////////////////////////
// PUBLIC

void AmdDeviceInfo_Initialize_RAII::PrintStaticParams()
{
    ReportFormatter::GetInstance().AddFieldString(
        L"AMD device_info compiled version", AMD_DEVICE_INFO_COMPILED_VERSION);
}

void AmdDeviceInfo_Initialize_RAII::PrintDeviceData(const DeviceId& id)
{
    const std::optional<device_info::CardInfo> cardInfo = device_info::GetCardInfo(
        { .vendor_id = id.vendorId, .device_id = id.deviceId, .revision_id = id.revisionId });
    if(!cardInfo)
        return;

    ReportFormatter& formatter = ReportFormatter::GetInstance();

    {
        ReportScopeObject region{ L"AMD device_info::CardInfo" };
        formatter.AddFieldEnum(L"asicType", uint32_t(cardInfo->asic_type), Enum_device_info_AsicType);
        formatter.AddFieldEnum(L"generation", uint32_t(cardInfo->generation), Enum_device_info_HwGeneration);
        formatter.AddFieldBool(L"APU", cardInfo->is_apu);
        // device_info v1.0 replaces the old CAL name with the compiler/driver GFX target.
        formatter.AddFieldString(L"GfxTarget", StrToWstr(cardInfo->gfx_target, CP_UTF8).c_str());
        formatter.AddFieldString(L"MarketingName", StrToWstr(cardInfo->marketing_name, CP_UTF8).c_str());
    }

    // device_info v1.0 uses an empty optional instead of an in-structure validity flag.
    if(const std::optional<device_info::DeviceInfo> deviceInfo = device_info::GetDeviceInfo(*cardInfo))
    {
        ReportScopeObject region(L"AMD device_info::DeviceInfo");
        formatter.AddFieldUint32(L"NumShaderEngines", deviceInfo->num_shader_engines); // Number of shader engines.
        formatter.AddFieldUint32(L"MaxWavePerSIMD", deviceInfo->max_wave_per_simd); // Number of wave slots per SIMD.
        formatter.AddFieldUint32(
            L"ClocksPrim", deviceInfo->clocks_per_primitive); // Number of clocks to process a primitive.
        formatter.AddFieldUint32(L"NumSQMaxCounters", deviceInfo->num_sq_counters); // Maximum number of SQ counters.
        formatter.AddFieldUint32(L"NumPrimPipes", deviceInfo->num_prim_pipes); // Number of primitive pipes.
        formatter.AddFieldUint32(L"WaveSize", deviceInfo->wave_size); // Wavefront size.
        formatter.AddFieldUint32(
            L"NumSHPerSE", deviceInfo->num_sh_per_se); // Number of shader arrays per shader engine.
        formatter.AddFieldUint32(L"NumCUs", deviceInfo->num_cus); // Number of compute units.
        formatter.AddFieldUint32(L"NumSIMDPerCU", deviceInfo->num_simd_per_cu); // Number of SIMDs per compute unit.
        formatter.AddFieldUint32(L"NumVGPRPerSIMD", deviceInfo->num_vgpr_per_simd); // Number of VGPRs per SIMD.
        formatter.AddFieldUint32(L"TotalSIMDs", device_info::TotalSimds(*deviceInfo)); // Total number of SIMDs.
        formatter.AddFieldUint32(
            L"TotalShaderArrays", device_info::TotalShaderArrays(*deviceInfo)); // Total number of shader arrays.
        // Returns zero for older architectures where the number of VGPRs per SIMD is unknown.
        formatter.AddFieldUint32(L"TotalVGPRs", device_info::TotalVgprs(*deviceInfo));

        if(const std::optional<uint32_t> totalLdsSize =
                device_info::GetTotalLdsSizeInBytes(cardInfo->generation, *deviceInfo))
        {
            // Total local data share memory across all compute units.
            formatter.AddFieldUint32(L"TotalLDSSizeInBytes", *totalLdsSize);
        }
    }
}

#endif // #if USE_AMD_DEVICE_INFO
