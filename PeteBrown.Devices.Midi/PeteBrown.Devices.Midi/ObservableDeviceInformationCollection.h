#pragma once

#include <collection.h>
#include "IObservableDeviceInformationCollection.h"

namespace WF =		::Windows::Foundation;
namespace WFC =		::Windows::Foundation::Collections;
namespace WUXI =	::Windows::UI::Xaml::Interop;
namespace WDE =		::Windows::Devices::Enumeration;
namespace Details = ::Platform::Collections::Details;

namespace PeteBrown
{
	namespace Devices
	{
		namespace Midi
		{
			[Windows::Foundation::Metadata::WebHostHidden]
			public ref class ObservableDeviceInformationCollection sealed :
				IObservableDeviceInformationCollection,
				public WFC::IObservableVector<CollectionItemType^>,
				WUXI::IBindableObservableVector
			{
			private:
				Platform::Collections::Vector<CollectionItemType^>^ _backingCollection;
				
				Windows::UI::Core::CoreDispatcher^ _dispatcher;
				bool _dispatchNotificationEvent;

				property unsigned int InternalSize { unsigned int get() { return _backingCollection->Size; }}
				CollectionItemType ^ InternalGetAt(unsigned int index);

				WFC::IVectorView<CollectionItemType ^> ^ InternalGetView();
				WFC::IIterator<CollectionItemType ^> ^ InternalFirst(); 
				bool InternalIndexOf(CollectionItemType ^value, unsigned int *index);
				void InternalSetAt(unsigned int index, CollectionItemType ^value);
				void InternalInsertAt(unsigned int index, CollectionItemType ^value);
				void InternalRemoveAt(unsigned int index);
				void InternalAppend(CollectionItemType ^value);
				void InternalRemoveAtEnd();
				void InternalClear();
				unsigned int InternalGetMany(unsigned int startIndex, Platform::WriteOnlyArray<CollectionItemType ^, 1U> ^items);
				void InternalReplaceAll(const Platform::Array<CollectionItemType ^, 1U> ^items);


				void OnVectorChanged(WFC::IObservableVector<CollectionItemType^> ^sender, WFC::IVectorChangedEventArgs ^event);

				event WFC::VectorChangedEventHandler<CollectionItemType ^> ^ _internalIObservableVectorVectorChanged;
				event WUXI::BindableVectorChangedEventHandler ^ _internalIBindableObservableVectorVectorChanged;


			public:
				ObservableDeviceInformationCollection(bool dispatchNotificationEvent);

				// Inherited via IVector
				virtual WFC::IIterator<CollectionItemType ^> ^ IVectorFirst() = WFC::IVector<CollectionItemType^>::First
				{
					return InternalFirst();
				}


				// Inherited via IObservableVector
				virtual property unsigned int IObservableSize
				{
					unsigned int IObservableSize::get() = WFC::IObservableVector<CollectionItemType^>::Size::get{ return InternalSize; }
				}

				virtual CollectionItemType ^ IObservableVectorGetAt(unsigned int index) = WFC::IObservableVector<CollectionItemType^>::GetAt
				{
					return InternalGetAt(index);
				}

				virtual WFC::IVectorView<CollectionItemType ^> ^ IObservableVectorGetView() = WFC::IObservableVector<CollectionItemType^>::GetView
				{
					return InternalGetView();
				}

				virtual bool IObservableVectorIndexOf(CollectionItemType ^value, unsigned int *index) = WFC::IObservableVector<CollectionItemType^>::IndexOf
				{
					return InternalIndexOf(value, index);
				}

				virtual void IObservableVectorSetAt(unsigned int index, CollectionItemType ^value) = WFC::IObservableVector<CollectionItemType^>::SetAt
				{
					InternalSetAt(index, value);
				}

				virtual void IObservableVectorInsertAt(unsigned int index, CollectionItemType ^value) = WFC::IObservableVector<CollectionItemType^>::InsertAt
				{
					InternalInsertAt(index, value);
				}

				virtual void IObservableVectorRemoveAt(unsigned int index) = WFC::IObservableVector<CollectionItemType^>::RemoveAt
				{
					InternalRemoveAt(index);
				}

				virtual void IObservableVectorAppend(CollectionItemType ^value) = WFC::IObservableVector<CollectionItemType^>::Append
				{
					InternalAppend(value);
				}

				virtual void IObservableVectorRemoveAtEnd() = WFC::IObservableVector<CollectionItemType^>::RemoveAtEnd
				{
					InternalRemoveAtEnd();
				}

				virtual void IObservableVectorClear() = WFC::IObservableVector<CollectionItemType^>::Clear
				{
					InternalClear();
				}

				virtual unsigned int IObservableVectorGetMany(unsigned int startIndex, Platform::WriteOnlyArray<CollectionItemType ^, 1U> ^items) = WFC::IObservableVector<CollectionItemType^>::GetMany
				{
					return InternalGetMany(startIndex, items);
				}

				virtual void IObservableVectorReplaceAll(const Platform::Array<CollectionItemType ^, 1U> ^items) = WFC::IObservableVector<CollectionItemType^>::ReplaceAll
				{
					InternalReplaceAll(items);
				}


				event WFC::VectorChangedEventHandler<CollectionItemType ^> ^ VectorChanged
				{
					virtual WF::EventRegistrationToken add(WFC::VectorChangedEventHandler<CollectionItemType ^> ^ handler) 
						= WFC::IObservableVector<CollectionItemType ^>::VectorChanged::add{ return _internalIObservableVectorVectorChanged += handler; }

					virtual void remove(WF::EventRegistrationToken token) 
						= WFC::IObservableVector<CollectionItemType ^>::VectorChanged::remove{ _internalIObservableVectorVectorChanged -= token; }

					//private void raise(parameters);
				}




				// Inherited via IBindableVector
				virtual WUXI::IBindableIterator ^ IBindableVectorFirst() = WUXI::IBindableVector::First
				{
					return safe_cast<WUXI::IBindableIterator^>(InternalFirst());
				}


				// Inherited via IBindableObservableVector

				virtual property unsigned int IBindableObservableVectorSize
				{
					unsigned int IBindableObservableVectorSize::get() = WUXI::IBindableObservableVector::Size::get{ return InternalSize; }
				}

				virtual Platform::Object ^ IBindableObservableVectorGetAt(unsigned int index) = WUXI::IBindableObservableVector::GetAt
				{
					return InternalGetAt(index);
				}

				virtual WUXI::IBindableVectorView ^ IBindableObservableVectorGetView() = WUXI::IBindableObservableVector::GetView
				{
					return safe_cast<WUXI::IBindableVectorView^>((WUXI::IBindableObservableVector^)(_backingCollection)->GetView());
				}


				virtual bool IBindableObservableVectorIndexOf(Platform::Object ^value, unsigned int *index) = WUXI::IBindableObservableVector::IndexOf
				{
					return InternalIndexOf(safe_cast<CollectionItemType^>(value), index);
				}

				virtual void IBindableObservableVectorSetAt(unsigned int index, Platform::Object ^value) = WUXI::IBindableObservableVector::SetAt
				{
					InternalSetAt(index, safe_cast<CollectionItemType^>(value));
				}

				virtual void IBindableObservableVectorInsertAt(unsigned int index, Platform::Object ^value) = WUXI::IBindableObservableVector::InsertAt
				{
					InternalInsertAt(index, safe_cast<CollectionItemType^>(value));
				}

				virtual void IBindableObservableVectorRemoveAt(unsigned int index) = WUXI::IBindableObservableVector::RemoveAt
				{
					InternalRemoveAt(index);
				}

				virtual void IBindableObservableVectorAppend(Platform::Object ^value) = WUXI::IBindableObservableVector::Append
				{
					InternalAppend(safe_cast<CollectionItemType^>(value));
				}

				virtual void IBindableObservableVectorRemoveAtEnd() = WUXI::IBindableObservableVector::RemoveAtEnd
				{
					InternalRemoveAtEnd();
				}

				virtual void IBindableObservableVectorClear() = WUXI::IBindableObservableVector::Clear
				{
					InternalClear();
				}


				event WUXI::BindableVectorChangedEventHandler ^ IBindableObservableVectorVectorChanged 
				{
					virtual WF::EventRegistrationToken add(WUXI::BindableVectorChangedEventHandler ^ handler) 
						= WUXI::IBindableObservableVector::VectorChanged::add{ return _internalIBindableObservableVectorVectorChanged += handler; }

					virtual void remove(WF::EventRegistrationToken token) 
						= WUXI::IBindableObservableVector::VectorChanged::remove{ _internalIBindableObservableVectorVectorChanged -= token; }
				}







					// Inherited via IObservableDeviceInformationCollection
				virtual property unsigned int Size
				{
					unsigned int Size::get() = IObservableDeviceInformationCollection::Size::get{ return InternalSize; }
				}

				// Inherited via IVector
				virtual WFC::IIterator<CollectionItemType ^> ^ First() = IObservableDeviceInformationCollection::First
				{
					return InternalFirst();
				}

				virtual CollectionItemType ^ GetAt(unsigned int index) = IObservableDeviceInformationCollection::GetAt
				{
					return InternalGetAt(index);
				}

				virtual WFC::IVectorView<CollectionItemType^>^ GetView() = IObservableDeviceInformationCollection::GetView
				{
					return InternalGetView();
				}

				virtual bool IndexOf(CollectionItemType ^ value, unsigned int * index) = IObservableDeviceInformationCollection::IndexOf
				{
					return InternalIndexOf(value, index);
				}

				virtual void SetAt(unsigned int index, CollectionItemType ^ value) = IObservableDeviceInformationCollection::SetAt
				{
					InternalSetAt(index, value);
				}

				virtual void InsertAt(unsigned int index, CollectionItemType ^ value) = IObservableDeviceInformationCollection::InsertAt
				{
					InternalInsertAt(index, value);
				}

				virtual void RemoveAt(unsigned int index) = IObservableDeviceInformationCollection::RemoveAt
				{
					InternalRemoveAt(index);
				}

				virtual void Append(CollectionItemType ^ value) = IObservableDeviceInformationCollection::Append
				{
					InternalAppend(value);
				}

				virtual void RemoveAtEnd() = IObservableDeviceInformationCollection::RemoveAtEnd
				{
					InternalRemoveAtEnd();
				}

				virtual void Clear() = IObservableDeviceInformationCollection::Clear
				{
					InternalClear();
				}

				virtual unsigned int GetMany(unsigned int startIndex, Platform::WriteOnlyArray<CollectionItemType^, 1U>^ items) = IObservableDeviceInformationCollection::GetMany
				{
					return InternalGetMany(startIndex, items);
				}

				virtual void ReplaceAll(const Platform::Array<CollectionItemType^, 1U>^ items) = IObservableDeviceInformationCollection::ReplaceAll
				{
					InternalReplaceAll(items);
				}



			};
		};
	};
};

