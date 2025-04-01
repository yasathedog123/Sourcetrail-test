#include "RefreshInfo.h"

using namespace std;

wostream &operator << (wostream &stream, RefreshMode mode)
{
	return stream << static_cast<int>(mode);
}
