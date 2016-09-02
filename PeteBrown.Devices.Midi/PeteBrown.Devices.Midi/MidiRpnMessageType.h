#pragma once

namespace PeteBrown
{
	namespace Devices
	{
		namespace Midi
		{
			enum MidiRpnMessageType
			{
				PitchBendSensitivity = 0,
				MasterFineTuning = 1,
				MaserCoarseTuning = 2,
				RpnNull = 127
			};
		};
	};
};