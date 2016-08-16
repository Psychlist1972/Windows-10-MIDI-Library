#pragma once


namespace PeteBrown
{
	namespace Devices
	{
		namespace Midi
		{
			// NOTE: This doesn't yet fully work with C# XAML binding. Change notifications after the fact are not
			// reflected in UI controls.
			//
			// TODO: INOtifyPropertyChanged

			[Windows::Foundation::Metadata::WebHostHidden]
			public ref class ObservableDeviceInformationCollection sealed :
				Windows::Foundation::Collections::IObservableVector<Windows::Devices::Enumeration::DeviceInformation^>
			{
			private:
				Platform::Collections::Vector<Windows::Devices::Enumeration::DeviceInformation^>^ _backingCollection;

			public:
				ObservableDeviceInformationCollection();

				// Inherited via IObservableVector
				virtual event Windows::Foundation::Collections::VectorChangedEventHandler<Windows::Devices::Enumeration::DeviceInformation ^> ^ VectorChanged;

				// Inherited via INotifyCollectionChanged
				//virtual event Windows::UI::Xaml::Interop::NotifyCollectionChangedEventHandler ^ CollectionChanged;

				virtual property unsigned int Size { unsigned int get() { return _backingCollection->Size; }}

				virtual Windows::Foundation::Collections::IIterator<Windows::Devices::Enumeration::DeviceInformation ^> ^ First();
				virtual Windows::Devices::Enumeration::DeviceInformation ^ GetAt(unsigned int index);
				virtual Windows::Foundation::Collections::IVectorView<Windows::Devices::Enumeration::DeviceInformation ^> ^ GetView();
				virtual bool IndexOf(Windows::Devices::Enumeration::DeviceInformation ^value, unsigned int *index);
				virtual void SetAt(unsigned int index, Windows::Devices::Enumeration::DeviceInformation ^value);
				virtual void InsertAt(unsigned int index, Windows::Devices::Enumeration::DeviceInformation ^value);
				virtual void RemoveAt(unsigned int index);
				virtual void Append(Windows::Devices::Enumeration::DeviceInformation ^value);
				virtual void RemoveAtEnd();
				virtual void Clear();
				virtual unsigned int GetMany(unsigned int startIndex, Platform::WriteOnlyArray<Windows::Devices::Enumeration::DeviceInformation ^, 1U> ^items);
				virtual void ReplaceAll(const Platform::Array<Windows::Devices::Enumeration::DeviceInformation ^, 1U> ^items);

				void OnVectorChanged(Windows::Foundation::Collections::IObservableVector<Windows::Devices::Enumeration::DeviceInformation ^> ^sender, Windows::Foundation::Collections::IVectorChangedEventArgs ^event);
			};
		};
	};
};

