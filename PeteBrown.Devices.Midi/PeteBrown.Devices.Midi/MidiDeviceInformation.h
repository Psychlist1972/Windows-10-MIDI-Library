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
				Network,
				Other
			};



			public ref class MidiDeviceInformation sealed
			{
			private:
				::Windows::Devices::Enumeration::DeviceInformation^ _info;
				MidiInterfaceType _interfaceType;

				Platform::String^ _deviceInstanceId;


			public:
				MidiDeviceInformation(::Windows::Devices::Enumeration::DeviceInformation^ info)
				{
					_info = info;


					std::wstring id(info->Id->Data());
					//std::wstring name(info->Name->Data());

					//std::transform(id.begin(), id.end(), id.begin(), ::tolower);
					//std::transform(name.begin(), name.end(), name.begin(), ::tolower);

//					if ((id.find(L".ble") != std::string::npos) ||
//						(name.find(L"bluetooth") != std::string::npos))

					
					if (id.find(L".BLE") != std::string::npos)						
					{
						_interfaceType = MidiInterfaceType::Bluetooth;
					}
					else
					{
						// Default to other until we nail down WiFi/Ethernet/software interfaces
						_interfaceType = MidiInterfaceType::Other;
					}

					// TODO: Find fast way to ID USB vs Network vs other types of interfaces.
					// Right now, USB and things like loopMIDI and rtpMIDI all look the same


					// device instance ID is a bit cleaner. No class GUID, for example
					_deviceInstanceId = info->Properties->Lookup(L"System.Devices.DeviceInstanceId")->ToString();

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




				property ::Platform::String^ DeviceInstanceId
				{
					::Platform::String^ get() { return _deviceInstanceId; }
				}








				// booleans are provided to help with xaml triggers, should you want to use them

				property bool IsInterfaceTypeBluetooth
				{
					bool get() { return _interfaceType == MidiInterfaceType::Bluetooth; }
				}

				property bool IsInterfaceTypeUsb
				{
					bool get() { return _interfaceType == MidiInterfaceType::Usb; }
				}

				property bool IsInterfaceTypeNetwork
				{
					bool get() { return _interfaceType == MidiInterfaceType::Network; }
				}

				property bool IsInterfaceTypeOther
				{
					bool get() { return _interfaceType == MidiInterfaceType::Other; }
				}


			};
		};
	};
};

