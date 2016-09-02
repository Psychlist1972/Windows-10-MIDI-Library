#pragma once

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

			ref class VectorChangedEventArgs sealed :
				public WFC::IVectorChangedEventArgs
			{
			public:
				VectorChangedEventArgs();

				// Inherited via IVectorChangedEventArgs
				virtual property WFC::CollectionChange CollectionChange;
				virtual property unsigned int Index;
			};
		};
	};
};
