#pragma once

//ファイル名
//Array_Capacity.h
//
//作成日
//2023/03/01
//
//製作者
//YUSUKE
//=================================================================

#include<concepts>
#include <type_traits>
#include<tuple>
//#include"Constexpr_Array.h"

namespace N_Constexpr
{

	template<class T, unsigned int t_Size>
	class Array;
};


	//仕様
	//クラス[Array]の要素数の上限値に対して、引数にとる要素数が適正か判定する
	//
	//テンプレート
	//remaining_Capacity::クラス[Array]の要素数
	//T::Arrayの管理する型
	//U::引数の一つ目型
	//...V::引数の2つ目以降の型
	//
	//補足
	//[Array_Capacity::Type]が判定の結果、可能なら[std::true_type],不可能なら[std::false_type]になる
	//型TがArray型でなく、引数の型がArray型の時、Arrayが分解され、それぞれ一つの型として確認する
template<class T,size_t remaining_Capacity, class U, class ...V>
class Array_Capacity
{
private:

	enum class State
	{
		T_CONVERTIBLE_U,
		ARRAY_DISASSEMBLY,
		ARRAY_DISASSEMBLY_END

	};

	template<class U,class ...V>
	State GetState()
	{
		if (std::convertible_to<U, T>)
		{
			return State::T_CONVERTIBLE_U;
		}
	}

	template<class Array_T,size_t t_ArraySize, class ...V>
	State GetState<N_Constexpr::Array<Array_T,t_ArraySize>,V...>()
	{
		if (std::convertible_to<N_Constexpr::Array<Array_T, t_ArraySize>,T>)
		{
			return State::T_CONVERTIBLE_U;
		}
		else if(t_ArraySize>1)
		{
			return State::ARRAY_DISASSEMBLY;
		}
		return State::ARRAY_DISASSEMBLY_END;
	}




	//仕様
	//型[U]がArrayに格納な型か判定する
	template<size_t remaining_Capacity, class U, class ...V,State t_State = GetState<U, V...>>
	class Capacity_Calcu
	{
	public:
		using Type = Capacity_Calcu<remaining_Capacity - 1,V...>::Type;
		
	};


	//仕様
	//型[U]がArrayに格納な型か判定する
	template<size_t remaining_Capacity, class U, class ...V>
	class Capacity_Calcu<remaining_Capacit,U,V...,State::ARRAY_DISASSEMBLY>
	{
	public:
		using Type = Capacity_Calcu<remaining_Capacity -, V...>::Type;

	};











public:

	//仕様
	//クラス[Array]の要素数の上限値に対して、引数にとる要素数が適正か判定した結果を返す
	//
	//補足
	//[Array_Capacity::Type]が判定の結果、可能なら[std::true_type],不可能なら[std::false_type]になる
	using Type = Capacity_Calcu<T,remaining_Capacity, U, V...>::Type;

};
