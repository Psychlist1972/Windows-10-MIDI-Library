#pragma once

namespace PeteBrown
{
	namespace Devices
	{
		namespace Midi
		{

			ref class MidiNrpnValueChange sealed
			{
			public:
				MidiNrpnValueChange();

				/// <summary>
				/// 14 bit value
				/// </summary>
				property unsigned short Value;

			};
		};
	};
}

