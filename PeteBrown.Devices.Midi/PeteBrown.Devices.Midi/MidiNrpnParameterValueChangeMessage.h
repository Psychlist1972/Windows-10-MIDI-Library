#pragma once

#include <wrl.h>
#include <robuffer.h>

#include "MidiMessageHelper.h"

using namespace Windows::Storage::Streams;
using namespace Microsoft::WRL;
using namespace PeteBrown::Devices::Midi;

namespace PeteBrown
{
	namespace Devices
	{
		namespace Midi
		{

			public ref class MidiNrpnParameterValueChangeMessage sealed :
				public Windows::Devices::Midi::IMidiMessage
			{

			private:

				// MIDI message numbers for NRPN
				const byte NRPN_PARAMETER_MSB = 99;
				const byte NRPN_PARAMETER_LSB = 98;
				const byte NRPN_VALUE_MSB = 6;
				const byte NRPN_VALUE_LSB = 38;

				// message order is ParameterNumberMsb, ParameterNumberLsb, ParameterValueMsb, ParameterValueLsb
				// each message is sent as a MIDI control change message
				const int BYTES_IN_MESSAGE = 12;

				const int PARAMETER_MSB_BYTE_OFFSET = 2;
				const int PARAMETER_LSB_BYTE_OFFSET = 5;

				const int VALUE_MSB_BYTE_OFFSET = 8;
				const int VALUE_LSB_BYTE_OFFSET = 11;



				unsigned short _parameterNumber;
				unsigned short _value;

				Windows::Storage::Streams::IBuffer ^ _rawData;
				byte * _rawBytes = nullptr;

				Windows::Foundation::TimeSpan _timestamp;
				Windows::Devices::Midi::MidiMessageType _type;

			public:
				MidiNrpnParameterValueChangeMessage();


				/// <summary>
				/// 14 bit number for the Non Registered Parameter Number
				/// </summary>
				property unsigned short ParameterNumber;

				/// <summary>
				/// 14 bit value
				/// </summary>
				property unsigned short Value;


				// Inherited via IMidiMessage
				virtual property Windows::Storage::Streams::IBuffer ^ RawData
				{
					Windows::Storage::Streams::IBuffer ^ get()
					{
						return _rawData;
					}
				}

				virtual property Windows::Foundation::TimeSpan Timestamp
				{
					Windows::Foundation::TimeSpan get()
					{
						return _timestamp;
					}
				}


				virtual property Windows::Devices::Midi::MidiMessageType Type
				{
					Windows::Devices::Midi::MidiMessageType get()
					{
						return _type;
					}
				}

			};
		};
	};
};