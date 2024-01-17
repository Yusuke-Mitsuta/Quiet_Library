#pragma once

#include<array>
#include"Tuple.h"
#include"Function_Args_Chack.h"

namespace N_Constexpr
{


	namespace N_Array
	{

		template<class T_Base_Type, class ...T_Args>
		using args_chack = typename
			N_Function::I_Function_Args_Chack<N_Tuple::U_Repeat_Multiple<T_Base_Type, 99>,
			tuple_t<T_Args...>>::type;

	}


	//仕様
	//ArrayをConstexprで管理する。
	//template
	//_Ty1::基準となる要素の型
	//N::要素の合計
	template<class _Ty1, size_t N>
	class Array
	{
		std::array<_Ty1, N> data;

	public:

		using tuple = N_Tuple::U_Repeat_Multiple<_Ty1, N>;

		template<class ..._Ty2>
			requires is_invalid_not<typename
		N_Tuple::I_Convert_Action<std::array<_Ty1, N>, _Ty2...>::type>
		constexpr Array(_Ty2 ...ts) :
			data(N_Tuple::Apply<std::array<_Ty1, N>>(ts...)) {}

		template<class _Ty2,class ..._Ty3>
			requires is_invalid_not< N_Array::args_chack<_Ty2, _Ty2, _Ty3...>>
		constexpr Array(_Ty2 t, _Ty3 ...ts) :
			data(N_Tuple::Apply<std::array<_Ty1, N>>(t, ts...)) {}

		template<size_t I>
		constexpr _Ty1& get();

		constexpr auto& operator[](size_t i);
	
	};


	template<class _Ty2, class ..._Ty3>
		requires is_invalid_not< N_Array::args_chack<_Ty2, _Ty2, _Ty3...>>
	Array(_Ty2 t, _Ty3 ...ts)->Array<_Ty2, N_Array::args_chack<_Ty2, _Ty2, _Ty3...>::tail_size>;

	template<class _Ty1, size_t N>
	template<size_t I>
	inline constexpr _Ty1& Array<_Ty1, N>::get()
	{
		return data[i];
	}

	template<class _Ty1, size_t N>
	inline constexpr auto& Array<_Ty1, N>::operator[](size_t i)
	{
		return data[i];
	}

}
