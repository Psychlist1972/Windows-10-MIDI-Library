#pragma once

using namespace std;

namespace PeteBrown
{
	namespace Devices
	{
		namespace Midi
		{
			public enum class MidiInterfaceType
			{
				Usb,
				Bluetooth,
				Other
			};



			public ref class MidiDeviceInformation sealed
			{
			private:
				::Windows::Devices::Enumeration::DeviceInformation^ _info;
				MidiInterfaceType _interfaceType;

			public:
				MidiDeviceInformation(::Windows::Devices::Enumeration::DeviceInformation^ info)
				{
					_info = info;


					std::wstring id(info->Id->Data());
					std::wstring name(info->Name->Data());

					std::transform(id.begin(), id.end(), id.begin(), ::tolower);
					std::transform(name.begin(), name.end(), name.begin(), ::tolower);

					if ((id.find(L".ble") != std::string::npos) ||
						(name.find(L"bluetooth") != std::string::npos))
					{
						_interfaceType = MidiInterfaceType::Bluetooth;
					}
					else
					{
						// Default to other until we nail down WiFi/Ethernet/software interfaces
						_interfaceType = MidiInterfaceType::Other;
					}

					// TODO: Find fast way to ID USB vs Network vs other types of interfaces.

				}

				property ::Windows::Devices::Enumeration::DeviceInformation^ DeviceInformation
				{
					::Windows::Devices::Enumeration::DeviceInformation^ get() { return _info; }
				}


				property ::Platform::String^ Name
				{
					::Platform::String^ get() { return _info->Name; }
				}

				property ::Platform::String^ Id
				{
					::Platform::String^ get() { return _info->Id; }
				}

				property bool IsEnabled
				{
					bool get() { return _info->IsEnabled; }
				}

				property MidiInterfaceType InterfaceType
				{
					MidiInterfaceType get() { return _interfaceType; }
				}

			};
		};
	};
};

