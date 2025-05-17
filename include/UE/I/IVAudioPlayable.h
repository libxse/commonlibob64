#pragma once

namespace UE
{
	class UObject;

	class IVAudioPlayable
	{
	public:
		UE_DEFINE_IINTERFACE(IVAudioPlayable, "Altar", "VAudioPlayable");

		// add
		virtual ~IVAudioPlayable();  // 00

		// add
		virtual UObject* _GetUObject();      // 01
		virtual void     LoadAudioEvents();  // 02
	};
	static_assert(sizeof(IVAudioPlayable) == 0x008);
}
