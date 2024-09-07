#include "print.hpp"
#include "string.hpp"

mi32 brb_main()
{
	brb::array<mu64, 4> arr;
	arr.fill(0);

	for (mu8 i = 0; i < arr.size(); ++i)
		arr[i] = 2;

	brb::string<64> big_str = "asdfas\n";

	if (arr[2] == 2)
		brb::print(big_str);

	brb::string<8> small_str = "asdfasdfasdf";

	brb::print("this point shouldn't get reached\n");
	return 0;
}
