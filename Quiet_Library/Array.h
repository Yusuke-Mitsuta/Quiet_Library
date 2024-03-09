/*!
 * Array.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include<array>
#include"Tuple.h"
#include"Tuple_Repeat_Multiple.h"
#include"Array_deduction_guide.h"

namespace quiet::N_Tuple
{
	template<class T, size_t N>
	struct S_Parameter<std::array<T, N>> :
		S_Parameter<U_Repeat_Multiple<T, N>>
	{};

}

namespace quiet
{

	//仕様
	//[_Ty1[t_array_size] elems]の配列を生成し、管理する
	//
	//補足
	//コンストラクタの引数に対して、
	// [N_Tuple::Apply]を用いて適切に変換の結果、
	//	要素数が不足している場合、
	// デフォルトで型を構築可能な場合かつ、
	// 暗黙的な変換でない場合は不足分をデフォルトで構築する
	// 
	//	void Hoge(Array<int, 3>　);
	//	
	//	void main()
	//	{
	//	　Hoge(1); //これは[int]から[Array<int, 3>]に暗黙的に変換されている為、不可となる
	//	　Hoge(Array<int, 2>()); //これは[Array<int, 3>]から[Array<int, 3>]に暗黙的に変換れている為、不可となる
	//	　Hoge(Array<int, 3>(1)); ///これは[Array<int, 3>]のコンストラクタを[int]で呼び出為、可となる
	//	}
	template<class _Ty1, size_t N>
	class Array :
		public std::array<_Ty1, N>
	{
	public:

		using tuple = quiet::N_Tuple::U_Repeat_Multiple<_Ty1, N>;

		using std::array<_Ty1, N>::operator[];

		template<size_t t_array_size_limit = N, class T_Base = _Ty1, class ..._Ty2>
			requires requires
		{
			requires sizeof...(_Ty2) == t_array_size_limit;
			requires convertible_from_and<T_Base, _Ty2...>;
		}
		constexpr Array(_Ty2... t)
			:std::array<_Ty1, N>({ static_cast<_Ty1>(t)... })
		{}

		//仕様
		// [N_Tuple::Apply]を用いて適切に変換の結果、成功した場合
		template<size_t t_array_size_limit = N, class T_Base = _Ty1, class ..._Ty2>
			requires requires
		{
			requires N_Array::args_size<T_Base, _Ty2...> == t_array_size_limit;
			requires convertible_from_nand<T_Base, _Ty2...>;
		}
		constexpr Array(_Ty2... t)
			:std::array<_Ty1, N>({ N_Tuple::I_Apply_Action<std::array<_Ty1, N>, _Ty2...>::Apply(t...) })
		{}


		//仕様
		// [N_Tuple::Apply]を用いて適切に変換の結果、
		// 要素が不足している場合は、デフォルトで構築を行う
		template<size_t t_array_size_limit = N, class T_Base = _Ty1, class ..._Ty2>
			requires requires
		{
			requires !(N_Array::args_size<T_Base, _Ty2...> <= 0);
			requires !(N_Array::args_size<T_Base, _Ty2...> >= t_array_size_limit);
			_Ty1{};
		}
		explicit constexpr Array(_Ty2 ...t)
			:std::array<_Ty1, N>({ N_Tuple::I_Apply_Action<std::array<_Ty1, N>, _Ty2...>::Apply(t...) })
		{}

		template<size_t t_array_size_limit = N, class T_Base = _Ty1>
			requires requires
		{
			T_Base{};
		}
		constexpr Array() :
			std::array<_Ty1, N>({})
		{}


		//仕様
		//単一の要素で配列を全て埋め尽くす
		constexpr void operator=(const convertible_to<_Ty1> auto& copy);

	};

	template<class ..._Ty2>
		requires (static_cast<bool>(N_Array::I_deduction_guide<_Ty2...>::size))
	Array(_Ty2 ...ts)->
		Array<typename N_Array::I_deduction_guide<_Ty2...>::type, 
		N_Array::I_deduction_guide<_Ty2...>::size>;



	template<class _Ty1, size_t N>
	inline constexpr void Array<_Ty1, N>::operator=(const convertible_to<_Ty1> auto& copy)
	{
		std::array<_Ty1, N>::fill(static_cast<_Ty1>(copy));
	}
}
