#pragma once

#include <collection.h>
#include "MidiDeviceInformation.h"

namespace WFC = ::Windows::Foundation::Collections;
namespace WUXI = ::Windows::UI::Xaml::Interop;
namespace WDE = ::Windows::Devices::Enumeration;
namespace Details = ::Platform::Collections::Details;

namespace PeteBrown
{
	namespace Devices
	{
		namespace Midi
		{
			//typedef ::Windows::Devices::Enumeration::DeviceInformation CollectionItemType;
			typedef MidiDeviceInformation CollectionItemType;

			[Windows::Foundation::Metadata::WebHostHidden]
			public interface class IObservableDeviceInformationCollection
			{
				property unsigned int Size { unsigned int get(); }
				CollectionItemType ^ GetAt(unsigned int index);
				WFC::IIterator<CollectionItemType ^> ^ First();
				WFC::IVectorView<CollectionItemType ^> ^ GetView();
				bool IndexOf(CollectionItemType ^value, unsigned int *index);
				void SetAt(unsigned int index, CollectionItemType ^value);
				void InsertAt(unsigned int index, CollectionItemType ^value);
				void RemoveAt(unsigned int index);
				void Append(PeteBrown::Devices::Midi::CollectionItemType ^value);
				void RemoveAtEnd();
				void Clear();
				unsigned int GetMany(unsigned int startIndex, Platform::WriteOnlyArray<CollectionItemType ^, 1U> ^items);
				void ReplaceAll(const Platform::Array<CollectionItemType ^, 1U> ^items);
			};
		};
	};
};