#include "array.hpp"

mi32 brb_main()
{
	brb::array<mi32, 4> arr;
	arr.fill(9);

	arr[2] = 5;

	return arr[2];
}
