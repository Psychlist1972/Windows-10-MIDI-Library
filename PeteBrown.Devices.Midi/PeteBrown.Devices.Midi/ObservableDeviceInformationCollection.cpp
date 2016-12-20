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

	_backingCollection = ref new Platform::Collections::Vector<CollectionItemType ^>();

	_backingCollection->VectorChanged += ref new VectorChangedEventHandler<CollectionItemType ^>(this, &ObservableDeviceInformationCollection::OnVectorChanged);


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



WFC::IIterator<CollectionItemType^> ^ ObservableDeviceInformationCollection::InternalFirst()
{
	return _backingCollection->First();
}

CollectionItemType^ ObservableDeviceInformationCollection::InternalGetAt(unsigned int index)
{
	return _backingCollection->GetAt(index);
}

WFC::IVectorView<CollectionItemType^> ^ ObservableDeviceInformationCollection::InternalGetView()
{
	return _backingCollection->GetView();
}

bool ObservableDeviceInformationCollection::InternalIndexOf(CollectionItemType^ value, unsigned int *index)
{
	return _backingCollection->IndexOf(value, index);
}


void ObservableDeviceInformationCollection::InternalSetAt(unsigned int index, CollectionItemType^ value)
{
	return _backingCollection->SetAt(index, value);
}

void ObservableDeviceInformationCollection::InternalInsertAt(unsigned int index, CollectionItemType^ value)
{
	return _backingCollection->InsertAt(index, value);
}

void ObservableDeviceInformationCollection::InternalRemoveAt(unsigned int index)
{
	return _backingCollection->RemoveAt(index);
}

void ObservableDeviceInformationCollection::InternalAppend(CollectionItemType^ value)
{
	return _backingCollection->Append(value);
}

void ObservableDeviceInformationCollection::InternalRemoveAtEnd()
{
	return _backingCollection->RemoveAtEnd();
}

void ObservableDeviceInformationCollection::InternalClear()
{
	return _backingCollection->Clear();
}

unsigned int ObservableDeviceInformationCollection::InternalGetMany(unsigned int startIndex, Platform::WriteOnlyArray<CollectionItemType^, 1U> ^items)
{
	return _backingCollection->GetMany(startIndex, items);
}

void ObservableDeviceInformationCollection::InternalReplaceAll(const Platform::Array<CollectionItemType^, 1U> ^items)
{
	return _backingCollection->ReplaceAll(items);
}



// this is where all the observable stuff happens
void ObservableDeviceInformationCollection::OnVectorChanged(WFC::IObservableVector<CollectionItemType^> ^sender, WFC::IVectorChangedEventArgs ^event)
{

	if (_dispatchNotificationEvent && (_dispatcher != nullptr))
	{
		_dispatcher->RunAsync(CoreDispatcherPriority::Normal,
			ref new DispatchedHandler([=]()
		{
			auto args = ref new Details::VectorChangedEventArgs(event->CollectionChange, event->Index);

			_internalIBindableObservableVectorVectorChanged(this, args);
			_internalIObservableVectorVectorChanged(this, args);
		}));
	}
	else
	{
		// raise event without dispatcher
		auto args = ref new Details::VectorChangedEventArgs(event->CollectionChange, event->Index);

		_internalIBindableObservableVectorVectorChanged(this, args);
		_internalIObservableVectorVectorChanged(this, args);
	}

}

