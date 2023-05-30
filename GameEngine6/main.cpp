#include"main.h"
#include<iostream>
#include"Constexpr_Array.h"
#include"Constexpr_String.h"
#include<tuple>




template<int n>
void a(const char(&str)[n])
{

	std::cout << str << std::endl;
	std::cout << typeid(decltype( str)).name() << std::endl;
	
}

int main()
{

	//T<"‚ ‚¢ua"> a;




	N_Constexpr::String str("a");

	N_Constexpr::Array<char,8> a(1,2,3,4,5,6);

	for (int i = 0; i < 8; i++)
	{

		std::cout << str.str[i] << std::endl;
		std::cout << a[i] << std::endl;
	}

	
	return 0;

}
	