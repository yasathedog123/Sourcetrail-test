#include "LocationType.h"

#include <iterator>

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
	return findEnum(value, begin(LOCATION_TYPES), end(LOCATION_TYPES), LocationType::TOKEN);
}

template <>
int enumToInt(LocationType type)
{
	return static_cast<int>(type);
}
