#include "array.hpp"

mi32 brb_main()
{
	brb::array<mi32, 4> arr;

	for (mi32 i = 0; i < arr.size() + 2; ++i)
		arr[i] = i;

	return arr[2];
}
