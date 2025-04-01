#include "LocationType.h"

using namespace std;

namespace
{

const LocationType LOCATION_TYPES[] = {
	LocationType::TOKEN,
	LocationType::SCOPE,
	LocationType::QUALIFIER,
	LocationType::LOCAL_SYMBOL,
	LocationType::SIGNATURE,
	LocationType::COMMENT,
	LocationType::ERROR,
	LocationType::FULLTEXT_SEARCH,
	LocationType::SCREEN_SEARCH,
	LocationType::UNSOLVED
};

}

template <>
LocationType intToEnum(int value)
{
	return lookupEnum(value, LOCATION_TYPES, LocationType::TOKEN);
}

size_t operator << (size_t bits, LocationType type)
{
	return bits << static_cast<int>(type);
}

string to_string(LocationType type)
{
	return std::to_string(static_cast<int>(type));
}
