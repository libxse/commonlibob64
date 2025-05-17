#pragma once

namespace UE
{
	class UObject;
	class USceneComponent;
	class UVTransformPairingComponent;

	class IVTransformPairable
	{
	public:
		UE_DEFINE_IINTERFACE(IVTransformPairable, "Altar", "VTransformPairable");

		// add
		virtual ~IVTransformPairable();  // 00

		// add
		virtual UObject*                     _GetUObject();                                                // 01
		virtual FTransform&                  GetReverseTransform();                                        // 02
		virtual USceneComponent*             GetForwardTransformPairingTarget();                           // 03
		virtual bool                         IsTransformPairingComponentOptional();                        // 04
		virtual UVTransformPairingComponent* GetTransformPairingComponent();                               // 05
		virtual bool                         AdjustTransformToEnvironment(FTransform&, std::uint32_t);     // 06
		virtual void                         ApplyOTATransformOffset(FTransform&, std::uint32_t);          // 07
		virtual void                         MoveToForwardPairedTransform(const FTransform&, const bool);  // 08
	};
	static_assert(sizeof(IVTransformPairable) == 0x008);
}
