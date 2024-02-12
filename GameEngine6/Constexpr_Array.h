#pragma once

#include<array>
#include"Tuple.h"
#include"Function_Args_Chack.h"

#define ARRAY_MAX_SIZE 9

namespace N_Tuple
{
	template<class T, size_t N>
	struct S_Parameter<std::array<T, N>> :
		S_Parameter<U_Repeat_Multiple<T, N>>
	{};

	
}

namespace N_Array
{

	template<class T_Base_Type, class ...T_Args>
	static constexpr int args_size = 
		N_Tuple::N_Apply::I_Type_Chack<
		tuple_t<N_Tuple::N_Apply::S_Infinite_Args<T_Base_Type>>,
		tuple_t<T_Base_Type,T_Args...>>::value;
}


//仕様
//ArrayをConstexprで管理する。
//template
//_Ty1::基準となる要素の型
//N::要素の合計
template<class _Ty1, size_t N>
class Array
{
	std::array<_Ty1, N> elems;

public:

	using tuple = N_Tuple::U_Repeat_Multiple<_Ty1, N>;

	//template<convertible_to<_Ty1> ..._Ty2>
	//	requires (sizeof...(_Ty2) == N) 
	//constexpr Array(_Ty2 ...ts) :
	//	elems({static_cast<_Ty1>(ts)...})
	//{}
	template<same_as<int> ..._Ty2>
		requires (sizeof...(_Ty2) == N) 
	constexpr Array(_Ty2 ...ts) :
		elems({static_cast<_Ty1>(ts)...})
	{}

	template<same_as<float> ..._Ty2>
		requires (sizeof...(_Ty2) == N) 
	constexpr Array(_Ty2 ...ts) :
		elems({static_cast<_Ty1>(ts)...})
	{}

	template<class _Ty2, class ..._Ty3>
		requires (N_Tuple::N_Apply::Chack<std::array<_Ty1, N>, _Ty2, _Ty3...>())
	constexpr Array(_Ty2 t, _Ty3 ...ts)
		: elems(N_Tuple::Apply<std::array<_Ty1, N>>(t, ts...))
	{

	}



	//仕様
	//配列のポインタを取得する
	constexpr _Ty1* data();

	//仕様
	//[I]番目の配列の要素を参照で取得する
	template<size_t I>
	constexpr _Ty1& get();

	//仕様
	//[i]番目の配列の要素を参照で取得する
	constexpr auto& operator[](size_t i);
							
};


//template<class _Ty2, class... _Ty3>
	//requires (convertible_to_and<_Ty2,_Ty3...>)
//Array(_Ty2 t, _Ty3 ...ts)->Array<_Ty2,9- N_Array::args_chack<_Ty2, _Ty2, _Ty3...>::size>;

template<class _Ty2, class ..._Ty3>
Array(_Ty2 t, _Ty3 ...ts) -> Array<_Ty2,N_Array::args_size<_Ty2,_Ty3...>>;




template<class _Ty1, size_t N>
inline constexpr _Ty1* Array<_Ty1, N>::data()
{
	return elems.data();
}

template<class _Ty1, size_t N>
template<size_t I>
inline constexpr _Ty1& Array<_Ty1, N>::get()
{
	return elems[I];
}


template<class _Ty1, size_t N>
inline constexpr auto& Array<_Ty1, N>::operator[](size_t i)
{
	return elems[i];
}

