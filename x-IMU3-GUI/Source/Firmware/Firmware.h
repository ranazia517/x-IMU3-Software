#pragma once

#include <BinaryData.h>
#include <juce_gui_basics/juce_gui_basics.h>

namespace Firmware
{
    static const juce::String fileName = "x-IMU3-Firmware-v1.0.2.hex";
    static const juce::String version = "v1.0.2";
    static const juce::MemoryBlock memoryBlock { BinaryData::xIMU3Firmwarev1_0_2_hex, BinaryData::xIMU3Firmwarev1_0_2_hexSize };
}
