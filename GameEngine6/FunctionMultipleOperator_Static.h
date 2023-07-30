#pragma once

#include<iostream>
#include<tuple>
#include"Function.h"
#include"Parameter_Element.h"

namespace N_Function
{
	//仕様
	//[FunctionMultipleStatic]のOperator部分の実装
	//
	//template
	//t_Fns...::関数ポインターor[FunctionStatic]、それに対する引数、の繰り返し
	//
	//補足
	//[IS_FunctionMultipleOperatorStatic::Type]を継承する事
	//t_Fnsに[FunctionStatic]をセットする際は[static constexpr]で修飾する事
	template <auto ...t_Fns>
	struct IS_FunctionMultipleOperatorStatic
	{
		using Fns = typename IS_FunctionMultiple_Helper<std::remove_const_t<decltype(t_Fns)>...>::Fns;

		template<size_t _Index>
		using Fns_element = std::tuple_element_t<_Index, Fns>;
		
		template<size_t _Index>
		static constexpr auto Parameter_Element_v = S_Parameter_Element_v<_Index, t_Fns...>;
		
		template<size_t t_Parameter_FnNumber,size_t ...t_Parameter_ArgsNumber>
		using Fn_Static =FunctionStatic<Parameter_Element_v<t_Parameter_FnNumber>,
		Parameter_Element_v<(t_Parameter_FnNumber+1)+t_Parameter_ArgsNumber>...>;

		static constexpr int Fns_Num = std::tuple_size_v<Fns>;

		template<size_t _Index>
		static constexpr int Bind_Args_Num= std::tuple_size_v<
			typename Fns_element<_Index>::BindArgs>;


		template<class T_Fn_Static = std::tuple<>, int t_FnCount = 0, int t_Parameter_Number = 0,class T_Bind_ArgsNum= std::make_index_sequence<Bind_Args_Num<t_FnCount>>>
		struct S_CreateFunctionStatic;

		//仕様
		//[t_fns...]から[FunctionStatic]を構成する
		//
		//template
		//T_Fn_Static::構成した[FunctionStatic]のtuple
		//t_FnCount::現在作成中の[FunctionStatic]の番号
		//t_Parameter_Number::[t_FnCount]番目の[FunctionStatic]を作成する為要素が[t_Fns...]の何番目から示す番号
		template<class ...T_Fn_Static,int t_FnCount, int t_Parameter_Number ,
			size_t ...t_Bind_ArgsNum>
		struct S_CreateFunctionStatic<std::tuple<T_Fn_Static...>,t_FnCount, t_Parameter_Number,
			std::index_sequence<t_Bind_ArgsNum...>>
		{
			using T_FnStatic_Add = std::tuple<Fn_Static<t_Parameter_Number, t_Bind_ArgsNum...>, T_Fn_Static...>;

			using Type = S_CreateFunctionStatic<T_FnStatic_Add, t_FnCount + 1, t_Parameter_Number + 1 + Bind_Args_Num<t_FnCount>>::Type;
		};

		template<class ...T_Fn_Static,int t_Parameter_Number,
			size_t ...t_Bind_ArgsNum>
		struct S_CreateFunctionStatic<std::tuple<T_Fn_Static...>, Fns_Num-1, t_Parameter_Number,
			std::index_sequence<t_Bind_ArgsNum...>>
		{
			using Type = std::tuple<
				Fn_Static<t_Parameter_Number, t_Bind_ArgsNum...>, 
				T_Fn_Static...>;

		};

		template<class T_FnsStatic>
		struct S_FunctionMultipleOperatorStatic;

		//仕様
		//構成した[FunctionStatic]を全て継承する
		template<class ...T_FnsStatic>
		struct S_FunctionMultipleOperatorStatic<std::tuple<T_FnsStatic...>> :
			public T_FnsStatic...
		{
			using T_FnsStatic::operator()...;
			using T_FnsStatic::Execution...;
		};

		using Type =
			S_FunctionMultipleOperatorStatic<typename S_CreateFunctionStatic<>::Type>;
	};

}