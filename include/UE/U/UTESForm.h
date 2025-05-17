#pragma once

#include "UE/E/EFormID.h"
#include "UE/T/TSoftClassPtr.h"
#include "UE/T/TSoftObjectPtr.h"
#include "UE/U/UTESBaseFormComponent.h"

namespace UE
{
	class AVActor;
	class AVPairedCharacter;
	class ExportTESForm;
	class LightComponentData;
	class UAnimBlueprint;
	class UBlueprint;
	class UPhysicsAsset;
	class USkeletalMesh;
	class USoundWave;
	class UStaticMesh;
	class UTESBipedModelForm;

	class UTESForm :
		public UTESBaseFormComponent
	{
	public:
		UE_DEFINE_UOBJECT(UTESForm, UTESBaseFormComponent, "Altar", "TESForm");

		// override
		virtual ~UTESForm();  // 00

		// add
		virtual FString                             GetFormDetailedString();
		virtual TSoftClassPtr<AVActor>              GetEquipableBlueprintClass();
		virtual bool                                CanFormBeUsedAsPropItem();
		virtual bool                                HasAnyStaticMeshVariant();
		virtual TSoftObjectPtr<UStaticMesh>         GetStaticMesh(const AVPairedCharacter*);
		virtual TSoftObjectPtr<UStaticMesh>         GetStaticMesh();
		virtual TSoftObjectPtr<USkeletalMesh>       GetSkeletalMesh();
		virtual TSoftObjectPtr<UPhysicsAsset>       GetPhysicsAsset();
		virtual TSoftObjectPtr<UAnimBlueprint>      GetAnimBlueprint();
		virtual UTESBipedModelForm*                 GetBipedModelForm();
		virtual LightComponentData*                 GetLightComponentData();
		virtual TArray<TSoftObjectPtr<USoundWave>>* GetSoundWaves();
		virtual FString                             GetFolderName();
		virtual UClass*                             GetComponent();
		virtual void                                Reset();
		virtual bool                                IsLoadingNiagaraSystemsAllowed();
		virtual void                                Fill(const ExportTESForm*);

		// members
		std::int64_t                       formID;                   // 028
		FString                            formEditorID;             // 030
		EFormID                            formType;                 // 040
		std::int64_t                       formFlags;                // 048
		TSoftObjectPtr<UBlueprint>         blueprint;                // 050
		TSoftClassPtr<AVActor>             blueprintClass;           // 078
		bool                               canBeUsedAsPropItem;      // 0A0
		std::int64_t                       bsxFlags;                 // 0A8
		TArray<TSoftObjectPtr<UBlueprint>> blueprintVariants;        // 0B0
		TArray<TSoftClassPtr<UClass>>      blueprintVariantClasses;  // 0C0
		bool                               hasModifiedESPData;       // 0D0
	};
	static_assert(sizeof(UTESForm) == 0xD8);
}
