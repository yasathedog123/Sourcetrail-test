#ifndef UTILITY_ENUM_H
#define UTILITY_ENUM_H

#include <ranges>

template <typename T>
T intToEnum(int);

template <typename E, typename Range>
E lookupEnum(int i, Range &&enums, E &&defaultValue)
{
	if (i >= 0 && i < std::ranges::ssize(enums))
		return *(std::ranges::begin(enums) + i);
	else
		return defaultValue;
}

#endif // UTILITYENUM_H
