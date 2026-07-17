#pragma once

#include "UE/V/VPairingEntry.h"

namespace UE
{
	class VHandlerClassBase
	{
	public:
		// add
		virtual ~VHandlerClassBase();             // 00
		virtual std::uint64_t Execute();          // 01
		virtual std::uint64_t Skip();             // 02
		virtual bool          ShouldBeSkipped();  // 03

		// members
		const char* name;  // 08
	};
	static_assert(sizeof(VHandlerClassBase) == 0x10);

	template <class T, class... Args>
	class VHandlerClass :
		public VHandlerClassBase
	{
	public:
		using Handle_t = void(T, Args...);

		// override
		virtual ~VHandlerClass();                          // 00
		virtual std::uint64_t Execute() override;          // 01
		virtual std::uint64_t Skip() override;             // 02
		virtual bool          ShouldBeSkipped() override;  // 03

		void SetPairingEntry(VPairingEntry* a_pairingEntry)
		{
			pairObject = a_pairingEntry;
			if (pairObject) {
				pairObject->referenceCount++;
			}
		}

		// members
		VPairingEntry*      pairObject;  // 10
		Handle_t*           handler;     // 18
		std::tuple<Args...> arguments;   // 20
	};
	static_assert(sizeof(VHandlerClass<void*>) == 0x28);
}
