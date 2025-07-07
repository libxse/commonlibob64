#pragma once

#include "RE/T/TESGlobal.h"

namespace RE
{
	class Calendar
	{
	public:
		static Calendar* GetSingleton()
		{
			static REL::Relocation<Calendar*> singleton{ ID::Calendar::Singleton };
			return singleton.get();
		}

		float GetDay() const;
		float GetDaysPassed() const;
		float GetHour() const;
		float GetMonth() const;
		float GetTime() const;
		float GetTimeScale() const;
		float GetYear() const;
		void  SetTimeScale(float a_value);

		// members
		TESGlobal* gameYear;        // 000
		TESGlobal* gameMonth;       // 008
		TESGlobal* gameDay;         // 010
		TESGlobal* gameHour;        // 018
		TESGlobal* gameDaysPassed;  // 020
		TESGlobal* timeScale;       // 028
	};
	static_assert(sizeof(Calendar) == 0x30);
}

namespace RE
{
	float Calendar::GetDay() const
	{
		return gameDay ? gameDay->value : 17.0F;
	}

	float Calendar::GetDaysPassed() const
	{
		return gameDaysPassed ? gameDaysPassed->value : 1.0F;
	}

	float Calendar::GetHour() const
	{
		return gameHour ? gameHour->value : 12.0F;
	}

	float Calendar::GetMonth() const
	{
		return gameMonth ? gameMonth->value : 7.0F;
	}

	float Calendar::GetTime() const
	{
		return GetDaysPassed() + (GetHour() / 24.0f);
	}

	float Calendar::GetTimeScale() const
	{
		return timeScale->value;
	}

	float Calendar::GetYear() const
	{
		return gameYear ? gameYear->value : 427.0F;
	}

	void Calendar::SetTimeScale(float a_value)
	{
		if (timeScale)
			timeScale->value = a_value;
	}
}
