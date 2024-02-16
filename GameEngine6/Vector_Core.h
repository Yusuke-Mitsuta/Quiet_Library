#pragma once

#include"Constexpr_Array.h"

#include"Vector_Storge.h"

namespace N_Vector
{

	//仕様
	//Vectorの実動作部分
	//
	//補足
	//コンストラクタの引数に対して、
	// [N_Tuple::Apply]を用いて適切に変換の結果、
	//	要素数が不足している場合、
	// デフォルトで型を構築可能な場合かつ、
	// 暗黙的な変換でない場合は不足分をデフォルトで構築する
	// 
	//	void Hoge(S_Core<int, 3>　);
	//	
	//	void main()
	//	{
	//		Hoge(1); //これは[int]から[S_Core<int, 3>]に暗黙的に変換されている為、不可となる
	//		Hoge(S_Core<int, 2>()); //これは[S_Core<int, 3>]から[S_Core<int, 3>]に暗黙的に変換されている為、不可となる
	//		Hoge(S_Core<int, 3>(1)); ////これは[S_Core<int, 3>]のコンストラクタを[int]で呼び出す為、可となる
	//	}
	template<class T,size_t t_vec>
	struct S_Core :
		S_Storge<T, t_vec>
	{
		using tuple = N_Tuple::U_Repeat_Multiple<T, t_vec>;


		//仕様
		// [N_Tuple::Apply]を用いて適切に変換の結果、成功した場合
		template<size_t N = t_vec, class T = T, class ...Ts>
			requires requires
		{
			requires N_Array::args_size<T, Ts...> == N;
		}
		constexpr S_Core(Ts... ts) :
			S_Storge<T, t_vec>({N_Tuple::I_Apply_Action<Array<T, N>,Ts...>::Apply(ts...)}) {}

		//仕様
		// [N_Tuple::Apply]を用いて適切に変換の結果、
		// 要素が不足している場合は、デフォルトで構築を行う
		template<size_t N = t_vec,class T=T, class ...Ts>
			requires requires
		{
			requires !(N_Array::args_size<T, Ts...> < 1);
			requires !(N_Array::args_size<T, Ts...> >= N);
			T{};
		}
		explicit constexpr S_Core(Ts... ts) :
			S_Storge<T, t_vec>({ N_Tuple::I_Apply_Action<Array<T, N>,Ts...>::Apply(ts...) }) {}

		//仕様
		//引数がゼロ、かつデフォルトで構築可能な場合
		template<size_t N = t_vec, class T = T>
			requires requires
		{
			T{};
		}
		explicit constexpr S_Core()
			:S_Storge<T, t_vec>({}) {}

		//仕様
		//[I]番目の配列の要素を参照で取得する
		template<size_t I>
		constexpr T& get();

		//仕様
		//[i]番目の配列の要素を参照で取得する
		constexpr T& operator[](const size_t& i);

		//仕様
		//単一の要素で配列を全て埋め尽くす
		constexpr void operator=(const convertible_to<T> auto& copy);
	};

	template<class T, size_t t_vec>
	template<size_t I>
	inline constexpr T& S_Core<T, t_vec>::get()
	{
		return S_Storge<T, t_vec>::elems[I];
	}

	template<class T, size_t t_vec>
	inline constexpr T& S_Core<T, t_vec>::operator[](const size_t& i)
	{
		return S_Storge<T, t_vec>::elems[i];
	}
	template<class T, size_t t_vec>
	inline constexpr void S_Core<T, t_vec>::operator=(const convertible_to<T> auto& copy)
	{
		S_Storge<T, t_vec>::elems = copy;
	}
}
