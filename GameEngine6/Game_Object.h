#pragma once

//#include"Core.h"
#include"Object.h"
#include<concepts>



template<class T,N_Constexpr::String U>
concept C_Str = requires(T(&t)[])
{
	requires (N_Constexpr::String(t) == U);
};

template<>
class Core<"Game_Object"> :
	public Core<"Object">
{
public:

	int game = 5;


	
};