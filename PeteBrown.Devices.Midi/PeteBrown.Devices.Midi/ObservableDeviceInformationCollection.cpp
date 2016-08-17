#include "pch.h"

#include <collection.h>

#include "ObservableDeviceInformationCollection.h"

using namespace PeteBrown::Devices::Midi;

using namespace Windows::Devices::Enumeration;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml::Interop;


ObservableDeviceInformationCollection::ObservableDeviceInformationCollection(bool dispatchNotificationEvent)
{
	_dispatchNotificationEvent = dispatchNotificationEvent;

	_backingCollection = ref new Platform::Collections::Vector<DeviceInformation ^>();

	_backingCollection->VectorChanged += ref new VectorChangedEventHandler<DeviceInformation ^>(this, &ObservableDeviceInformationCollection::OnVectorChanged);


	if (_dispatchNotificationEvent)
	{
		auto window = CoreWindow::GetForCurrentThread();

		if (window)
		{
			_dispatcher = window->Dispatcher;
		}
		else
		{
			_dispatcher = nullptr;
			_dispatchNotificationEvent = false;

			// throw an exception of some sort? This is a constructor, so not a great idea
		}

	}
}


Windows::Foundation::Collections::IIterator<DeviceInformation ^> ^ ObservableDeviceInformationCollection::First()
{
	return _backingCollection->First();
}

Windows::Devices::Enumeration::DeviceInformation ^ ObservableDeviceInformationCollection::GetAt(unsigned int index)
{
	return _backingCollection->GetAt(index);
}

Windows::Foundation::Collections::IVectorView<DeviceInformation ^> ^ ObservableDeviceInformationCollection::GetView()
{
	return _backingCollection->GetView();
}

bool ObservableDeviceInformationCollection::IndexOf(DeviceInformation ^value, unsigned int *index)
{
	return _backingCollection->IndexOf(value, index);
}

void ObservableDeviceInformationCollection::SetAt(unsigned int index, DeviceInformation ^value)
{
	return _backingCollection->SetAt(index, value);
}

void ObservableDeviceInformationCollection::InsertAt(unsigned int index, DeviceInformation ^value)
{
	return _backingCollection->InsertAt(index, value);
}

void ObservableDeviceInformationCollection::RemoveAt(unsigned int index)
{
	return _backingCollection->RemoveAt(index);
}

void ObservableDeviceInformationCollection::Append(DeviceInformation ^value)
{
	return _backingCollection->Append(value);
}

void ObservableDeviceInformationCollection::RemoveAtEnd()
{
	return _backingCollection->RemoveAtEnd();
}

void ObservableDeviceInformationCollection::Clear()
{
	return _backingCollection->Clear();
}

unsigned int ObservableDeviceInformationCollection::GetMany(unsigned int startIndex, Platform::WriteOnlyArray<DeviceInformation ^, 1U> ^items)
{
	return _backingCollection->GetMany(startIndex, items);
}

void ObservableDeviceInformationCollection::ReplaceAll(const Platform::Array<DeviceInformation ^, 1U> ^items)
{
	return _backingCollection->ReplaceAll(items);
}


// this is where all the observable stuff happens
void ObservableDeviceInformationCollection::OnVectorChanged(Windows::Foundation::Collections::IObservableVector<DeviceInformation ^> ^sender, IVectorChangedEventArgs ^event)
{
	if (_dispatchNotificationEvent && _dispatcher)
	{
		_dispatcher->RunAsync(CoreDispatcherPriority::Normal,
			ref new DispatchedHandler([=]()
		{
			// do the c#-friendly IObservableCollection bit
			NotifyCollectionChangedEventArgs^ args;
			auto newItems = ref new Platform::Collections::Vector<DeviceInformation ^>();
			auto oldItems = ref new Platform::Collections::Vector<DeviceInformation ^>();


			switch (event->CollectionChange)
			{
			case CollectionChange::ItemInserted:
				newItems->Append(_backingCollection->GetAt(event->Index));
				args = ref new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction::Add, newItems, nullptr, event->Index, -1);
				break;

			case CollectionChange::ItemRemoved:
				args = ref new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction::Remove, nullptr, oldItems, -1, event->Index);
				break;

			case CollectionChange::ItemChanged:
				args = ref new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction::Replace, nullptr, oldItems, event->Index, event->Index);
				break;

			case CollectionChange::Reset:
				args = ref new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction::Reset, nullptr, nullptr, -1, -1);
				break;
			};

			// NotifyCollectionChanged for C#/.NET
			CollectionChanged(this, args);

			// also rethrow this for C++ users
			VectorChanged(this, event);
		}));
	}


	// TODO!

}

//Platform::Object ^ PeteBrown::Devices::Midi::ObservableDeviceInformationCollection::GetAt(unsigned int index)
//{
//	throw ref new Platform::NotImplementedException();
//	// TODO: insert return statement here
//}
//
//Windows::UI::Xaml::Interop::IBindableVectorView ^ PeteBrown::Devices::Midi::ObservableDeviceInformationCollection::GetView()
//{
//	throw ref new Platform::NotImplementedException();
//	// TODO: insert return statement here
//}

//bool PeteBrown::Devices::Midi::ObservableDeviceInformationCollection::IndexOf(Platform::Object ^value, unsigned int *index)
//{
//	return false;
//}
//
//void PeteBrown::Devices::Midi::ObservableDeviceInformationCollection::SetAt(unsigned int index, Platform::Object ^value)
//{
//	throw ref new Platform::NotImplementedException();
//}
//
//void PeteBrown::Devices::Midi::ObservableDeviceInformationCollection::InsertAt(unsigned int index, Platform::Object ^value)
//{
//	throw ref new Platform::NotImplementedException();
//}
//
//void PeteBrown::Devices::Midi::ObservableDeviceInformationCollection::Append(Platform::Object ^value)
//{
//	throw ref new Platform::NotImplementedException();
//}
