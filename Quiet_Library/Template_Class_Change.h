#pragma once

#include<tuple>


namespace quiet::N_Template
{

	//仕様
	//[T_Old]のテンプレートパラメータを[T_New_Outer]に移す
	//
	//テンプレート
	// 
	//[T_Old]::テンプレートパラメータを取り出すクラス
	//[T_New_Outer]::テンプレートパラメータを移すクラス
	//
	//補足
	//[T_Old]が[std::tuple_size,std::tuple_element]に対応していない場合、
	//	[invalid_t]を返す
	template<class T_Old, template<class...> class T_New_Outer>
	struct S_Class_Change
	{
	private:

		template<class T_Old>
		struct S_Index_Sequence
		{
			using type = invalid_t;
		};

		template<class T_Old>
			requires requires
		{
			requires std::tuple_size_v<T_Old> >= 0;
			{ typename std::tuple_element_t<0, T_Old> };
		}
		struct S_Index_Sequence<T_Old>
		{
			using type = N_Tuple::I_index_sequence<std::tuple_size_v<T_Old>>::type;
		};

		template<class T_Indexs = typename S_Index_Sequence<T_Old>::type >
		struct S_Tuple_Create
		{
			using type = invalid_t;
		};

		template<size_t ...t_indexs>
		struct S_Tuple_Create<tuple_v<t_indexs...>>
		{
			using type = T_New_Outer<std::tuple_element_t<t_indexs, T_Old>...>;
		};

	public:

		using type = typename S_Tuple_Create<>::type;
	};

	//仕様
	//[T_Old]のテンプレートパラメータを[T_New_Outer]に移す
	//
	//テンプレート
	// 
	//[T_Old]::テンプレートパラメータを取り出すクラス
	//[T_New_Outer]::テンプレートパラメータを移すクラス
	//
	//補足
	//[T_Old]が[std::tuple_size,std::tuple_element]に対応していない場合、
	//	[invalid_t]を返す
	template<class T_Old, template<class...> class T_New_Outer>
	using U_Class_Change =typename S_Class_Change<T_Old, T_New_Outer>::type;
	
}