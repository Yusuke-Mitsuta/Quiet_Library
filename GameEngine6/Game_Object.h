#pragma once

#include"Core.h"
#include"Object.h"
#include<concepts>



template<class T,N_Constexpr::String U>
concept C_Str = requires(T(&t)[])
{
	requires (N_Constexpr::String(t) == U);
};

template<Core_Name ...t_Root>
class Core<"Game_Object",t_Root...>:
	public Core<"Object",t_Root..., "Game_Object">
{
public:

	int game=5;


	//template<>
	//class Message<"Game_Object", "Test">
	//	: public Message<>
	//{
	//private:
	//public:

	//	constexpr Message() {}

	//	int a_game_main = 6;

	//};

};