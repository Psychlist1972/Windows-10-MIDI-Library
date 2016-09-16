#pragma once


#include <wrl.h>
#include <robuffer.h>

using namespace Windows::Storage::Streams;
using namespace Microsoft::WRL;

namespace PeteBrown
{
    namespace Devices
    {
        namespace Midi
        {
            public ref class MidiMessageHelper sealed
            {
            private:
				// MIDI message numbers for NRPN
				static const byte NRPN_PARAMETER_MSB = 99;
				static const byte NRPN_PARAMETER_LSB = 98;
				static const byte NRPN_VALUE_MSB = 6;
				static const byte NRPN_VALUE_LSB = 38;
				static const byte NRPN_PARAMETER_NUMBER_NULL = 127;	// value to be sent as parameter number after done

				// MIDI message numbers for RPN
				static const byte RPN_PARAMETER_MSB = 101;
				static const byte RPN_PARAMETER_LSB = 100;
				static const byte RPN_VALUE_MSB = 6;
				static const byte RPN_VALUE_LSB = 38;
				static const byte RPN_PARAMETER_NUMBER_NULL = 127;		// value to be sent as parameter number after done


                MidiMessageHelper();

                //inline static byte msb(unsigned short value) { return (value >> 7) & 0x7F; }
                //inline static byte lsb(unsigned short value) { return value & 0x7F;	}
                //inline static byte BuildMidiStatusByte(byte message, byte channel) { return message << 4 | channel; }

            public:		

				inline static byte msb(unsigned short value) { return ConvertTo7Bit((byte)(value >> 7)); }
				inline static byte lsb(unsigned short value) { return ConvertTo7Bit((byte)value); }
				inline static byte BuildMidiStatusByte(byte message, byte channel) { return message << 4 | channel; }

				inline static byte ConvertTo7Bit(byte value) { return value & 0x7f; }
				inline static unsigned short ConvertTo14Bit(unsigned short value) { return value & 0x3FFF; }


				static void GetRawDataBytesFromBuffer(IBuffer^ buffer, byte* bytes)
				{
					ComPtr<IBufferByteAccess> bufferByteAccess;
					reinterpret_cast<IInspectable*>(buffer)->QueryInterface(IID_PPV_ARGS(&bufferByteAccess));

					bytes = nullptr;

					bufferByteAccess->Buffer(&bytes);
				}


            };
        };
    };
};

