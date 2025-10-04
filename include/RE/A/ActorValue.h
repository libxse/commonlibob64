#pragma once

namespace RE::ActorValue
{
	// NOTE: Index is technically int8_t, but all uses of it expect int32_t
	enum class Index : std::int32_t
	{
		Strength = 0,
		Intelligence = 1,
		Willpower = 2,
		Agility = 3,
		Speed = 4,
		Endurance = 5,
		Personality = 6,
		Luck = 7,
		Magicka = 8
	};

	enum class Section : std::int32_t
	{
		Attribute = 0,
		DerivedAttribute = 1,
		Skill = 2,
		Trait = 3,
		Virtue = 4,
		FloatValue = 5,
		IntValue = 6
	};
}
