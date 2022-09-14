#pragma once

#include "DataMessages/DataMessages.h"
#include "DecodeError.h"
#include "DiscoveredSerialDevice.h"
#include "FileConverterProgress.h"
#include "NetworkAnnouncementMessage.h"
#include "Result.h"
#include "Statistics.h"

using namespace System;

namespace Ximu3
{
    public ref class OpenEventArgs : public EventArgs
    {
    public:
        Result result;

    internal:
        OpenEventArgs(Result result) : result(result)
        {
        }
    };

    public ref class SendCommandsEventArgs : public EventArgs
    {
    public:
        array<String^>^ responses;

    internal:
        SendCommandsEventArgs(array<String^>^ responses) : responses(responses)
        {
        }
    };

    public ref class DecodeErrorEventArgs : public EventArgs
    {
    public:
        DecodeError decodeError;

    internal:
        DecodeErrorEventArgs(DecodeError decodeError) : decodeError(decodeError)
        {
        }
    };

    public ref class StatisticsEventArgs : public EventArgs
    {
    public:
        Statistics^ statistics;

    internal:
        StatisticsEventArgs(Statistics^ statistics) : statistics(statistics)
        {
        }
    };

    // Start of code block #0 generated by x-IMU3-API/Rust/src/data_messages/generate_data_messages.py

    public ref class InertialEventArgs : public EventArgs
    {
    public:
        InertialMessage^ message;

    internal:
        InertialEventArgs(InertialMessage^ message) : message(message)
        {
        }
    };

    public ref class MagnetometerEventArgs : public EventArgs
    {
    public:
        MagnetometerMessage^ message;

    internal:
        MagnetometerEventArgs(MagnetometerMessage^ message) : message(message)
        {
        }
    };

    public ref class QuaternionEventArgs : public EventArgs
    {
    public:
        QuaternionMessage^ message;

    internal:
        QuaternionEventArgs(QuaternionMessage^ message) : message(message)
        {
        }
    };

    public ref class RotationMatrixEventArgs : public EventArgs
    {
    public:
        RotationMatrixMessage^ message;

    internal:
        RotationMatrixEventArgs(RotationMatrixMessage^ message) : message(message)
        {
        }
    };

    public ref class EulerAnglesEventArgs : public EventArgs
    {
    public:
        EulerAnglesMessage^ message;

    internal:
        EulerAnglesEventArgs(EulerAnglesMessage^ message) : message(message)
        {
        }
    };

    public ref class LinearAccelerationEventArgs : public EventArgs
    {
    public:
        LinearAccelerationMessage^ message;

    internal:
        LinearAccelerationEventArgs(LinearAccelerationMessage^ message) : message(message)
        {
        }
    };

    public ref class EarthAccelerationEventArgs : public EventArgs
    {
    public:
        EarthAccelerationMessage^ message;

    internal:
        EarthAccelerationEventArgs(EarthAccelerationMessage^ message) : message(message)
        {
        }
    };

    public ref class HighGAccelerometerEventArgs : public EventArgs
    {
    public:
        HighGAccelerometerMessage^ message;

    internal:
        HighGAccelerometerEventArgs(HighGAccelerometerMessage^ message) : message(message)
        {
        }
    };

    public ref class TemperatureEventArgs : public EventArgs
    {
    public:
        TemperatureMessage^ message;

    internal:
        TemperatureEventArgs(TemperatureMessage^ message) : message(message)
        {
        }
    };

    public ref class BatteryEventArgs : public EventArgs
    {
    public:
        BatteryMessage^ message;

    internal:
        BatteryEventArgs(BatteryMessage^ message) : message(message)
        {
        }
    };

    public ref class RssiEventArgs : public EventArgs
    {
    public:
        RssiMessage^ message;

    internal:
        RssiEventArgs(RssiMessage^ message) : message(message)
        {
        }
    };

    public ref class SerialAccessoryEventArgs : public EventArgs
    {
    public:
        SerialAccessoryMessage^ message;

    internal:
        SerialAccessoryEventArgs(SerialAccessoryMessage^ message) : message(message)
        {
        }
    };

    public ref class NotificationEventArgs : public EventArgs
    {
    public:
        NotificationMessage^ message;

    internal:
        NotificationEventArgs(NotificationMessage^ message) : message(message)
        {
        }
    };

    public ref class ErrorEventArgs : public EventArgs
    {
    public:
        ErrorMessage^ message;

    internal:
        ErrorEventArgs(ErrorMessage^ message) : message(message)
        {
        }
    };
    // End of code block #0 generated by x-IMU3-API/Rust/src/data_messages/generate_data_messages.py

    public ref class DataLoggerEventArgs : public EventArgs
    {
    public:
        Result result;

    internal:
        DataLoggerEventArgs(Result result) : result(result)
        {
        }
    };

    public ref class FileConverterEventArgs : public EventArgs
    {
    public:
        FileConverterProgress^ progress;

    internal:
        FileConverterEventArgs(FileConverterProgress^ progress) : progress(progress)
        {
        }
    };

    public ref class NetworkAnnouncementEventArgs : public EventArgs
    {
    public:
        NetworkAnnouncementMessage^ message;

    internal:
        NetworkAnnouncementEventArgs(NetworkAnnouncementMessage^ message) : message(message)
        {
        }
    };

    public ref class SerialDiscoveryEventArgs : public EventArgs
    {
    public:
        array<DiscoveredSerialDevice^>^ devices;

    internal:
        SerialDiscoveryEventArgs(array<DiscoveredSerialDevice^>^ devices) : devices(devices)
        {
        }
    };
}
