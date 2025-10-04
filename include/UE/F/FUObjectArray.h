#pragma once

#include "UE/F/FChunkedFixedUObjectArray.h"
#include "UE/F/FCriticalSection.h"
#include "UE/F/FThreadSafeCounter.h"
#include "UE/T/TArray.h"
#include "UE/U/UObjectBase.h"

namespace UE
{
	class FUObjectItem;

	class FUObjectArray
	{
	public:
		class FUObjectCreateListener
		{
		public:
			virtual ~FUObjectCreateListener() = default;

			virtual void NotifyUObjectCreated(const UObjectBase* a_object, std::int32_t a_index) = 0;
			virtual void OnUObjectArrayShutdown() = 0;
		};

		class FUObjectDeleteListener
		{
		public:
			virtual ~FUObjectDeleteListener() = default;

			virtual void NotifyUObjectDeleted(const UObjectBase* a_object, std::int32_t a_index) = 0;
			virtual void OnUObjectArrayShutdown() = 0;
		};

		class TIterator
		{
		public:
			TIterator(const FUObjectArray& a_array, bool a_onlyGCedObjects = false) :
				array(a_array), index(a_onlyGCedObjects ? a_array.objLastNonGCIndex : -1)
			{
				Advance();
			}

			void operator++()
			{
				Advance();
			}

			bool operator==(const TIterator& a_rhs) const
			{
				return index == a_rhs.index;
			}

			bool operator!=(const TIterator& a_rhs) const
			{
				return index != a_rhs.index;
			}

			explicit operator bool() const
			{
				return !!current;
			}

			bool operator!() const
			{
				return !(bool)*this;
			}

			std::int32_t GetIndex() const
			{
				return index;
			}

			const FUObjectArray& GetIteratedArray() const
			{
				return array;
			}

			FUObjectItem* GetObject() const
			{
				return current;
			}

			bool Advance()
			{
				FUObjectItem* next = nullptr;
				current = nullptr;

				while (++index < array.GetObjectArrayNum()) {
					next = const_cast<FUObjectItem*>(&array.objObjects[index]);
					if (next->object) {
						current = next;
						return true;
					}
				}

				return false;
			}

		private:
			const FUObjectArray&  array;               // 00
			std::int32_t          index;               // 08
			mutable FUObjectItem* current{ nullptr };  // 0C
		};
		static_assert(sizeof(TIterator) == 0x18);

		static FUObjectArray* GetSingleton()
		{
			static REL::Relocation<FUObjectArray*> ptr{ ID::FUObjectArray::GetSingleton };
			return ptr.get();
		}

		std::int32_t AllocateSerialNumber(std::int32_t a_index)
		{
			using func_t = decltype(&FUObjectArray::AllocateSerialNumber);
			static REL::Relocation<func_t> func{ ID::FUObjectArray::AllocateSerialNumber };
			return func(this, a_index);
		}

		std::int32_t GetObjectArrayCapacity() const
		{
			return objObjects.Capacity();
		}

		std::int32_t GetObjectArrayNum() const
		{
			return objObjects.Num();
		}

		FUObjectItem* IndexToObject(std::int32_t a_index)
		{
			if (a_index < objObjects.Num())
				return const_cast<FUObjectItem*>(&objObjects[a_index]);

			return nullptr;
		}

		void LockInternalArray() const
		{
			objObjectsCritical.Lock();
		}

		std::int32_t ObjectToIndex(const UObjectBase* a_object) const
		{
			return a_object->internalIndex;
		}

		void UnlockInternalArray() const
		{
			objObjectsCritical.Unlock();
		}

		// members
		std::int32_t                    objFirstGCIndex;
		std::int32_t                    objLastNonGCIndex;
		std::int32_t                    maxObjectsNotConsideredByGC;
		bool                            openForDisregardForGC;
		FChunkedFixedUObjectArray       objObjects;
		mutable FCriticalSection        objObjectsCritical;
		TArray<std::int32_t>            objAvailableList;
		TArray<FUObjectCreateListener*> objCreateListeners;
		TArray<FUObjectDeleteListener*> objDeleteListeners;
		FCriticalSection                objDeleteListenersCritical;
		FThreadSafeCounter              primarySerialNumber;
		bool                            shouldRecycleObjectIndices;
	};
	static_assert(sizeof(FUObjectArray) == 0xB8);
}
