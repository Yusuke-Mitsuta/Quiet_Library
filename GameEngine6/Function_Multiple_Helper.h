#pragma once
#include"tuple_convertible_to.h"
#include"Tuple_Unzip.h"

#define FUNCTION_MULTIPLE(Variable,...)\
S_MoveTupleInnerType<FunctionMultiple,decltype(std::tuple(__VA_ARGS__))>::Type Variable = { __VA_ARGS__ };\

namespace N_Function
{

	template<class T_Method, class ...T_Args>
	struct S_MethodData;

	template<not_same_as<std::nullopt_t> T_Method, class ...TP_Args>
	class Function_Single;


	//仕様
	//関数ポインターに対して、引数の値が正しいか、後方一致で判定する
	//
	//テンプレート
	//T_Fn_Args::関数ポインター、指定する引数、のTuple
	//
	//補足
	//T_Fn_Argsは関数ポインター、それに指定する引数、次の関数ポインター、となるようにする事
	// //SetJudge::関数に対して、「後ろに続く引数の型、関数にバインド済みの引数の型」が関数に対する引数の型の後方部分と互換性があるか判定する
	//Fns::関数ポインターor[Function_Single]と、後ろに続く引数の型を[Function_Single]としてまとめ、その動作を[T_Fn_Args...]がなくなるまで繰り返す
	template<class T_FlontFn,class ...T_Fn_Args>
	struct IS_Function_Multiple_Helper
	{
	private:
		using T_Tuple = std::tuple<T_FlontFn, T_Fn_Args... >;

		static constexpr int tuple_size = std::tuple_size<T_Tuple>::value;

		template<int _Index>
		using tuple_element = std::tuple_element_t<
			(_Index-1) %tuple_size, T_Tuple>;

		//仕様
		//関数に対して、「後ろに続く引数の型、関数にバインド済みの引数の型」が関数に対する引数の型の後方部分と互換性があるか判定し、互換性があれば[Function_Single]にまとめる
		//
		//テンプレート
		//t_FunctionNumber::引数を精査する関数ポインターor[Function_Single]の番号+１
		//...T_BoundFns::[Function_Single]でまとめた型
		template<int t_FunctionNumber=1,class ...T_BoundFns>
		struct S_CorrectType
		{

			using Method = N_Function::S_MethodData<tuple_element<t_FunctionNumber>>;

			//仕様
			//関数ポインターに対して引数をセットする
			template<class TP_Args, int t_TupleNumber, int ...t_ArgsNumber>
			struct S_Judge
			{
				using Type = S_Judge<tuple_element<t_TupleNumber + 1>, t_TupleNumber + 1, t_ArgsNumber..., t_TupleNumber>::Type;
			};


			//仕様
			//Functionに対して引数を判定する
			template<class T_CName, class T_RType, class ...TP_Args, int t_MethodTupleNumber, int ...t_ArgsNumber>
			struct S_Judge<T_RType(T_CName::*)(TP_Args...), t_MethodTupleNumber, t_ArgsNumber...>
			{
				static constexpr bool judge =
					tuple_back_part_convertible_to<typename IS_TupleUnzip<tuple_element<t_ArgsNumber>...>::Type, typename Method::Args>;

				using Type = S_CorrectType<t_MethodTupleNumber* judge,
					T_BoundFns...,
					Function_Single<tuple_element<t_FunctionNumber>, tuple_element<t_ArgsNumber>...>>::Type;

			};

			//仕様
			//Functionに対して引数を判定する
			template<class ...T_FunctionInner,int t_MethodTupleNumber, int ...t_ArgsNumber>
			struct S_Judge<Function_Single<T_FunctionInner...>, t_MethodTupleNumber, t_ArgsNumber...>
			{

				//仕様
				//引数が関数に対して、正しいか判定する
				static constexpr bool judge = 
					tuple_back_part_convertible_to<typename IS_TupleUnzip<tuple_element<t_ArgsNumber>..., typename Method::BoundArgs>::Type, typename Method::Args>;

				using Type = S_CorrectType<t_MethodTupleNumber* judge,
					T_BoundFns...,
					Function_Single<tuple_element<t_FunctionNumber>, tuple_element<t_ArgsNumber>...>>::Type;

			};
			using Type = S_Judge<tuple_element<t_FunctionNumber + 1>, t_FunctionNumber + 1>::Type;

		};

		//仕様
		//Functionに対してセットした引数が無効な型だった場合
		template<class ...T_BoundFns>
		struct S_CorrectType<0,T_BoundFns...>
		{
			using Type = S_CorrectType;
			using Judge = std::nullopt_t;
		};

		//仕様
		//Functionに対してセットした引数の全てが成功した場合
		template<class ...T_BoundFns>
		struct S_CorrectType<tuple_size+1, T_BoundFns...>
		{
			using Type = S_CorrectType;
			using Judge = T_FlontFn;
			using Fns = std::tuple<T_BoundFns...>;
		};
	public:
		using Judge= S_CorrectType<>::Type::Judge;

		using Fns= S_CorrectType<>::Type::Fns;

	};

}