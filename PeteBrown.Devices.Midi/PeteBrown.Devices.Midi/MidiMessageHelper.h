#pragma once

namespace PeteBrown
{
	namespace Devices
	{
		namespace Midi
		{
			private ref class MidiMessageHelper sealed
			{
			private:
				MidiMessageHelper();

				inline static byte msb(unsigned short value) { return value >> 7; }
				inline static byte lsb(unsigned short value) { return value & 0x7F;	}

			public:				
				static void SendNrpnMessage(Windows::Devices::Midi::MidiOutPort^ outputPort, byte channelZeroBased, unsigned short parameterNumber, unsigned short parameterValue);
				static void SendRpnMessage(Windows::Devices::Midi::MidiOutPort^ outputPort, byte channelZeroBased, unsigned short parameterNumber, unsigned short parameterValue);

				

			};
		};
	};
};

