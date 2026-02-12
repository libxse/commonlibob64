#pragma once

#include "RE/B/BSStringT.h"
#include "RE/B/BSTList.h"
#include "RE/C/CHUNK_ID.h"
#include "RE/F/FILE_HEADER.h"
#include "RE/F/FORM.h"
#include "RE/N/NiFile.h"
#include "RE/N/NiTPointerMap.h"
#include "RE/T/TES_RETURN_CODE.h"

namespace RE
{
	class BSFile;
	class TESObjectCELL;

	class TESFile
	{
	public:
		enum class RecordFlag
		{
			kNone = 0,
			kMaster = 1 << 0,
			kAltered = 1 << 1,
			kChecked = 1 << 2,
			kActive = 1 << 3,
			kOptimizedFile = 1 << 4,
			kTempIDOwner = 1 << 5,
			kDelocalized = 1 << 7,
			kPrecalcDataOnly = 1 << 8,
			kSmallFile = 1 << 9
		};

		[[nodiscard]] std::uint8_t     GetCompileIndex() const noexcept { return compileIndex; }
		[[nodiscard]] std::string_view GetFilename() const noexcept { return { filename }; }
		[[nodiscard]] bool             IsActive() const noexcept { return GetCompileIndex() != 0xFF; }

		bool CloseTES()
		{
			using func_t = decltype(&TESFile::CloseTES);
			static REL::Relocation<func_t> func{ ID::TESFile::CloseTES };
			return func(this);
		}

		CHUNK_ID GetTESChunk()
		{
			using func_t = decltype(&TESFile::GetTESChunk);
			static REL::Relocation<func_t> func{ ID::TESFile::GetTESChunk };
			return func(this);
		}

		bool GetChunkData(void* a_data, std::uint32_t a_size)
		{
			using func_t = decltype(&TESFile::GetChunkData);
			static REL::Relocation<func_t> func{ ID::TESFile::GetChunkData };
			return func(this, a_data, a_size);
		}

		bool NextChunk()
		{
			using func_t = decltype(&TESFile::NextChunk);
			static REL::Relocation<func_t> func{ ID::TESFile::NextChunk };
			return func(this);
		}

		bool NextForm(bool a_skipIgnored)
		{
			using func_t = decltype(&TESFile::NextForm);
			static REL::Relocation<func_t> func{ ID::TESFile::NextForm };
			return func(this, a_skipIgnored);
		}

		bool OpenTES(NiFile::OpenMode a_accessMode, bool a_lock)
		{
			using func_t = decltype(&TESFile::OpenTES);
			static REL::Relocation<func_t> func{ ID::TESFile::OpenTES };
			return func(this, a_accessMode, a_lock);
		}

		// members
		REX::TEnumSet<TES_RETURN_CODE, std::int32_t> lastError;                     // 000
		TESFile*                                     threadSafeParent;              // 008
		NiTPointerMap<std::uint32_t, TESFile*>*      threadSafeFileMap;             // 010
		BSFile*                                      lockedFile;                    // 018
		BSFile*                                      file;                          // 020
		char                                         filename[REX::W32::MAX_PATH];  // 028
		char                                         path[REX::W32::MAX_PATH];      // 12C
		char*                                        buffer;                        // 230
		std::uint32_t                                bufferAllocSize;               // 238
		std::uint32_t                                firstCellOffset;               // 23C
		std::uint32_t                                currCellOffset;                // 240
		TESObjectCELL*                               currCell;                      // 248
		std::uint32_t                                currRefOffset;                 // 250
		FORM                                         currentform;                   // 254
		REX::TEnumSet<CHUNK_ID, std::int32_t>        currentchunkID;                // 268
		std::uint32_t                                actualChunkSize;               // 26C
		std::uint32_t                                filesize;                      // 270
		std::uint32_t                                fileoffset;                    // 274
		std::uint32_t                                formoffset;                    // 278
		std::uint32_t                                chunkoffset;                   // 27C
		FORM                                         saveform;                      // 280
		std::uint32_t                                saveformoffset;                // 294
		std::uint32_t                                savechunkoffset;               // 298
		BSSimpleList<FORM_GROUP*>                    grouplist;                     // 2A0
		bool                                         hasGroups;                     // 2B0
		REX::W32::WIN32_FIND_DATAA                   fileInfo;                      // 2B4
		FILE_HEADER                                  fileHeaderInfo;                // 3F4
		REX::TEnumSet<RecordFlag, std::uint32_t>     flags;                         // 400
		BSSimpleList<char*>                          listMasters;                   // 408
		BSSimpleList<std::uint64_t*>                 listMastersData;               // 418
		std::uint32_t                                masterCount;                   // 428
		TESFile**                                    masterPtrs;                    // 430
		REX::W32::FILETIME                           deletedFormTime;               // 438
		std::uint8_t                                 compileIndex;                  // 440
		BSString                                     createdBy;                     // 448
		BSString                                     summary;                       // 458
		char*                                        decompressedFormBuffer;        // 468
		std::uint32_t                                decompressedFormBufferSize;    // 470
	};
	static_assert(sizeof(TESFile) == 0x478);
}
