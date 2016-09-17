#pragma once

#include <Windows.h>
#include <wrl.h>
#include <tchar.h>
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

			public ref class MidiNrpnValueChangeMessage sealed :
				public Windows::Devices::Midi::IMidiMessage
			{

			private:

				// MIDI message numbers for NRPN
				const byte NRPN_VALUE_MSB = 6;
				const byte NRPN_VALUE_LSB = 38;

				// message order is ParameterNumberMsb, ParameterNumberLsb, ParameterValueMsb, ParameterValueLsb
				// each message is sent as a MIDI control change message
				// These need to match what is being sent out. Buffer is initialized using these values, and some pointer math is based on them
				const int TOTAL_MIDI_MESSAGE_COUNT = 2;
				const int BYTES_IN_MIDI_CHANNEL_MESSAGE = 3;
				const int TOTAL_BYTES_IN_MESSAGE = BYTES_IN_MIDI_CHANNEL_MESSAGE * TOTAL_MIDI_MESSAGE_COUNT;

				const int VALUE_MSB_DATA1_BYTE_OFFSET = 1;
				const int VALUE_MSB_DATA2_BYTE_OFFSET = 2;
				const int VALUE_LSB_DATA1_BYTE_OFFSET = 4;
				const int VALUE_LSB_DATA2_BYTE_OFFSET = 5;

				unsigned short _parameterValue;
				byte _channel;

				// IBuffer required for Windows 10 MIDI implementation. _rawBytes required so we can write to the IBuffer
				// _rawBytes is initialized properly in the constructor
				Windows::Storage::Streams::IBuffer ^ _rawData;
				byte * _rawBytes = nullptr;

				Windows::Foundation::TimeSpan _timestamp;
				Windows::Devices::Midi::MidiMessageType _type;

				inline void SetByte(const int offset, byte value)
				{
					*(_rawBytes + offset) = value;
				}


				// Update the Data 2 bytes just for the Parameter Value MSB and LSB
				void UpdateValueBytes()
				{
					SetByte(VALUE_LSB_DATA2_BYTE_OFFSET, MidiMessageHelper::lsb7(_parameterValue));
					SetByte(VALUE_MSB_DATA2_BYTE_OFFSET, MidiMessageHelper::msb7(_parameterValue));
				}

				// Update all MIDI status bytes. Usually this is because the channel changed
				void UpdateStatusBytes()
				{
					const byte controlChange = 11;

					byte status = MidiMessageHelper::BuildMidiStatusByte(controlChange, _channel);

					// update each status byte in the array.
					for (int i = 0; i < TOTAL_MIDI_MESSAGE_COUNT; i++)
					{
						SetByte(BYTES_IN_MIDI_CHANNEL_MESSAGE * i, status);
					}
				}

				// Build the base messages. This is done once on construction.
				void BuildBaseMessages()
				{
					// build the base message layout

					SetByte(VALUE_LSB_DATA1_BYTE_OFFSET, NRPN_VALUE_LSB);
					SetByte(VALUE_MSB_DATA1_BYTE_OFFSET, NRPN_VALUE_MSB);

					UpdateStatusBytes();
				}

			public:
				MidiNrpnValueChangeMessage();


				/// <summary>
				/// 14 bit value. This will be split into MSB and LSB messages.
				/// </summary>
				property unsigned short ParameterValue
				{
					unsigned short get()
					{
						return _parameterValue;
					}
					void set(unsigned short value)
					{
						_parameterValue = value;
						UpdateValueBytes();
					}
				}

				/// <summary>
				/// MIDI channel for the message
				/// </summary>
				property byte Channel
				{
					byte get()
					{
						return _channel;
					}
					void set(byte value)
					{
						_channel = value;
						UpdateStatusBytes();
					}

				}


				// Inherited via IMidiMessage
				virtual property Windows::Storage::Streams::IBuffer ^ RawData
				{
					Windows::Storage::Streams::IBuffer ^ get()
					{
						//wchar_t s[256];
						//swprintf(s, 255, L"--- RawData requested. Length is %d\n", _rawData->Length);
						//OutputDebugString(s);

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
}

