#include "pch.h"

#include <collection.h>

#include "ObservableDeviceInformationCollection.h"

using namespace PeteBrown::Devices::Midi;

using namespace Windows::Devices::Enumeration;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml::Interop;

ObservableDeviceInformationCollection::ObservableDeviceInformationCollection()
{
	_backingCollection = ref new Platform::Collections::Vector<DeviceInformation ^>();

	_backingCollection->VectorChanged += ref new VectorChangedEventHandler<DeviceInformation ^>(this, &ObservableDeviceInformationCollection::OnVectorChanged);
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
	// first, rethrow this for C++ users
	VectorChanged(this, event);

	//// second, do the c#-friendly IObservableCollection bit
	//NotifyCollectionChangedEventArgs^ args;
	//
	//switch (event->CollectionChange)
	//{
	//case CollectionChange::ItemChanged:
	//	args = ref new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction::Replace);
	//	break;
	//case CollectionChange::ItemInserted:
	//	args = ref new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction::Add);
	//	break;
	//case CollectionChange::ItemRemoved:
	//	args = ref new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction::Remove);
	//	break;
	//case CollectionChange::Reset:
	//	args = ref new NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction::Reset);
	//	break;
	//};
	//
	//


	//CollectionChanged(this, e);
}
