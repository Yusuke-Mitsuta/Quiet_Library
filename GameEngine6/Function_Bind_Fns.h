#pragma once
//#include"Function_BindFn.h"
#include"tuple_convertible_to.h"
#include"Tuple_Unzip.h"
#include"Function.h"
#include<tuple>
#include<optional>

namespace N_Function
{
	//仕様
	//関数ポインターに対して、引数の値が正しいか、後方一致で判定する
	//
	//テンプレート
	//T_Fn_Args::関数ポインター、指定する引数、のTuple
	//
	//補足
	//T_Fn_Argsは関数ポインター、それに指定する引数、次の関数ポインター、となるようにする事
	template<class ...T_Fn_Args>
	struct IS_BindFns
	{
		using T_Tuple = IS_TupleUnzip<T_Fn_Args...>::Type;

		static constexpr int tuple_size = std::tuple_size<T_Tuple>::value;

		template<int _Index>
		using tuple_element = std::tuple_element<
			tuple_size - _Index, T_Tuple>::type;

		//仕様
		//引数のバインド済み関数ポインターを格納し、最後の関数なら格納処理を終了する
		//
		//テンプレート
		//t_TupleNumber::現在、精査したタプルの要素数
		//...T_BoundFns::引数のバインド済み関数ポインター
		//補足
		//t_TupleNumberは後ろから何番目にアクセスするかを示す
		template<int t_TupleNumber=1, class ...T_BoundFns>
		struct S_BoundFns
		{
			//仕様
			//関数ポインターに対して引数をセットする
			template<class T_Args, int t_TupleNumber=0, int ...t_ArgsNumber>
			struct S_BindFns
			{
				using Type = S_BindFns<tuple_element<t_TupleNumber + 1>, t_TupleNumber + 1, t_TupleNumber, t_ArgsNumber...>::Type;
			};

			//仕様
			//Functionに対して引数をセットする
			template<class T_CName, class T_RType, class ...T_Args, int t_TupleNumber, int ...t_ArgsNumber>
			struct S_BindFns<T_RType(T_CName::*)(T_Args...), t_TupleNumber, t_ArgsNumber...>
			{
				static constexpr bool judge = tuple_back_part_convertible_to<std::tuple<tuple_element<t_ArgsNumber>...>, std::tuple<T_Args...>>;

				using Type =
					S_BoundFns<(t_TupleNumber + 1)* judge,
					Function<std::tuple<T_RType(T_CName::*)(T_Args...), tuple_element<t_ArgsNumber>...>>,
					T_BoundFns...>::Type;
			};

			//仕様
			//Functionに対して引数をセットする
			template<class T_CName, class T_RType, class ...T_Args, class ...T_DefaultSetArgs, int t_TupleNumber, int ...t_ArgsNumber>
			struct S_BindFns<Function<std::tuple<T_RType(T_CName::*)(T_Args...), T_DefaultSetArgs...>>, t_TupleNumber, t_ArgsNumber...>
			{
				static constexpr bool judge = tuple_back_part_convertible_to<std::tuple<tuple_element<t_ArgsNumber>..., T_DefaultSetArgs...>,std::tuple<T_Args...>>;

				using Type = S_BoundFns<(t_TupleNumber + 1)* judge,
					Function<std::tuple<T_RType(T_CName::*)(T_Args...), tuple_element<t_ArgsNumber>..., T_DefaultSetArgs...>>,
					T_BoundFns...>::Type;
			};

			using Type = S_BindFns<tuple_element<t_TupleNumber>, t_TupleNumber>::Type;
		};

		//仕様
		//Functionに対してセットした引数が無効な型だった場合
		template<class T_FlontBoundFn,class ...T_BoundFns>
		struct S_BoundFns<0,T_FlontBoundFn,T_BoundFns...>
		{
			using Type = S_BoundFns;
			using Judge = std::false_type;
			using FnsType = std::nullopt_t;
		};

		//仕様
		//Functionに対してセットした引数の全てが成功した場合
		template<class ...T_BoundFns>
		struct S_BoundFns<tuple_size+1,T_BoundFns...>
		{
			using Type = S_BoundFns;
			using Judge = std::true_type;
			using FnsType = std::tuple<T_BoundFns...>;
		};

		using Type = S_BoundFns<1>::Type;
		using Judge = Type::Judge;
		using FnsType = Type::FnsType;

		//FnsType fns;

		//IS_BindFns(T_Fn_Args... fn_Args){}

	};
}