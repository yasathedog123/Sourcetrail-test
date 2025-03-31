#include "Catch2.hpp"

#include "utilityEnum.h"

enum class Color {
	NONE = 0,
	
	RED = 1,
	GREEN = 2,
	BLUE = 3
};

const Color COLORS[] = {
	Color::NONE,
	Color::RED,
	Color::GREEN,
	Color::BLUE
};

template<>
Color intToEnum(int value)
{
	return lookupEnum(value, COLORS, Color::NONE);
}

TEST_CASE("enum lookup valid value")
{
	REQUIRE(intToEnum<Color>(static_cast<int>(Color::GREEN)) == Color::GREEN);
}

TEST_CASE("enum lookup invalid value too small")
{
	REQUIRE(intToEnum<Color>(static_cast<int>(Color::NONE) - 1) == Color::NONE);
}

TEST_CASE("enum lookup invalid value too large")
{
	REQUIRE(intToEnum<Color>(static_cast<int>(Color::BLUE) + 1) == Color::NONE);
}

	
