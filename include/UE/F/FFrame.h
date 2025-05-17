#pragma once

#include "UE/F/FOutputDevice.h"
#include "UE/T/TArray.h"
#include "UE/T/TInlineAllocator.h"

namespace UE
{
	class FField;
	class FOutParmRec;
	class FProperty;
	class UFunction;
	class UObject;

	using FlowStackType = TArray<std::uint32_t, TInlineAllocator<8>>;

	class FFrame :
		public FOutputDevice
	{
	public:
		// override
		virtual ~FFrame();  // 00

		static void KismetExecutionMessage(const wchar_t* a_message, ELogVerbosity a_verbosity, FName a_warningID = FName())
		{
			using func_t = decltype(&FFrame::KismetExecutionMessage);
			REL::Relocation<func_t> func{ UE::ID::FFrame::KismetExecutionMessage };
			func(a_message, a_verbosity, a_warningID);
		}

		// members
		UFunction*    node;                         // 010
		UObject*      object;                       // 018
		std::uint8_t* code;                         // 020
		std::uint8_t* locals;                       // 028
		FProperty*    mostRecentProperty;           // 030
		std::uint8_t* mostRecentPropertyAddress;    // 038
		std::uint8_t* mostRecentPropertyContainer;  // 040
		FlowStackType flowStack;                    // 048
		FFrame*       previousFrame;                // 078
		FOutParmRec*  outParms;                     // 080
		FField*       propertyChainForCompiledIn;   // 088
		UFunction*    currentNativeFunction;        // 090
		FFrame*       previousTrackingFrame;        // 098
		bool          arrayContextFailed;           // 0A0
		bool          abortingExecution;            // 0A1
	};
	static_assert(sizeof(FFrame) == 0xA8);
}
