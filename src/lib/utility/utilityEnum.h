#ifndef UTILITY_ENUM_H
#define UTILITY_ENUM_H

#include <algorithm>

template <typename T>
T intToEnum(int);

template <typename T>
int enumToInt(T);

template <typename E, typename Iterator>
E findEnum(int i, Iterator begin, Iterator end, E defaultValue)
{
	auto found = std::find_if(begin, end, [=](E e) {
		return i == static_cast<int>(e);
	});
	return found != end ? *found : defaultValue;
}

#endif // UTILITYENUM_H
