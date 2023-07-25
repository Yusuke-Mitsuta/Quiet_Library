#pragma once
//#include"Function_BindFn.h"
#include"tuple_convertible_to.h"
#include"Tuple_Unzip.h"
#include"Function.h"
#include"tuple_Helper.h"
#include<tuple>
#include<optional>

namespace N_Function
{
	template<int t_Fn,int ...t_Args>
	struct S_MethodExecution
	{
		template<class ...T_TupleType>
		static constexpr auto Execution(std::tuple<T_TupleType...>& fnsData,auto&... args)
		{
			return std::get<t_Fn>(fnsData)(args..., std::get<t_Args>(fnsData)...);
		}
	};

	//仕様
	//関数ポインターに対して、引数の値が正しいか、後方一致で判定する
	//
	//テンプレート
	//T_Fn_Args::関数ポインター、指定する引数、のTuple
	//
	//補足
	//T_Fn_Argsは関数ポインター、それに指定する引数、次の関数ポインター、となるようにする事
	template<class T_FlontArgs,class T_Data,class ...T_Fn_Args>
	struct IS_FunctionMultiple_Helper
	{
		using T_Tuple = std::tuple <T_Data, T_Fn_Args... >;

		static constexpr int tuple_size = std::tuple_size<T_Tuple>::value;

		template<int _Index>
		using reverse_tuple_element = std::tuple_element<
			tuple_size - _Index, T_Tuple>::type;

		template<int _Index>
		using tuple_element = std::tuple_element_t<
			_Index %tuple_size, T_Tuple>;

		enum class E_Mode
		{
			MethodSearch = 0,
			SetJudge = 2,
		};


		//仕様
		//二種のモードがあり、[t_Mode]で切り替えられる
		//[t_Mode = E_Mode::SetJudge]::関数に対して、「後ろに続く引数の型、関数にバインド済みの引数の型」が関数に対する引数の型の後方部分と互換性があるか判定する
		//[t_Mode = E_Mode::MethodSearch]::関数の型に対して、「[T_FlontArgs]、後ろに続く引数の型、関数にバインド済みの引数の型」で関数に対する引数の型が互換性があるか判定する
		//
		//テンプレート
		//t_Mode:：判定の方法
		//t_FunctionNumber::現在、引数を探査中の関数の番号
		//...t_Datas::[ E_Mode::MethodSearch]時に引数の型の番号を取得するのに使用する
		template<E_Mode t_Mode,bool t_LoopFg=true,int t_FunctionNumber=0,int ...t_Datas>
		struct S_CorrectType
		{

			using Fn = Function<tuple_element<t_FunctionNumber>>;

			//仕様
			//関数ポインターに対して引数をセットする
			template<class T_Args, int t_TupleNumber, int ...t_ArgsNumber>
			struct S_Judge
			{
				using NextClass = S_Judge<tuple_element<t_TupleNumber + 1>, t_TupleNumber + 1,t_ArgsNumber..., t_TupleNumber>;

				using Type = NextClass::Type;

				using NextMethod = NextClass::NextMethod;
			};

			//仕様
			//Functionに対して引数を判定する
			template<class T_CName, class T_RType, class ...T_Args, int t_MethodTupleNumber, int ...t_ArgsNumber>
			struct S_Judge<T_RType(T_CName::*)(T_Args...), t_MethodTupleNumber, t_ArgsNumber...>
			{
				static constexpr bool judge =
					same_as<typename IS_tuple_convertible_to<typename IS_TupleUnzip<T_FlontArgs,tuple_element<t_ArgsNumber>...>::Type,
					typename Fn::Args, static_cast<int>(t_Mode)>::Select,std::bool_constant<static_cast<int>(t_Mode)>>;
					
				using NextClass = S_CorrectType<t_Mode,judge,t_MethodTupleNumber>;

				using NextMethod = S_Judge;

				using Type =NextClass::Type;

			};

			//仕様
			//Functionに対して引数を判定する
			template<class ...T_FunctionInner,int t_MethodTupleNumber, int ...t_ArgsNumber>
			struct S_Judge<Function<T_FunctionInner...>, t_MethodTupleNumber, t_ArgsNumber...>
			{

				//仕様
				//引数が関数に対して、正しいか判定する
				static constexpr bool judge = 
					std::same_as<typename IS_tuple_convertible_to<typename IS_TupleUnzip<T_FlontArgs,tuple_element<t_ArgsNumber>...,typename Fn::BoundArgs>::Type, 
					typename Fn::Args,static_cast<int>(t_Mode)>::Select, std::bool_constant<static_cast<int>(t_Mode)>>;

				using NextClass = S_CorrectType<t_Mode,judge,t_MethodTupleNumber>;
				using NextMethod = S_Judge;

				using Type = NextClass::Type;

			};
			using NextClass = S_Judge<tuple_element<t_FunctionNumber+1>, t_FunctionNumber+1>;

			using Type = NextClass::Type;

			//仕様			
			//パラメータパック内の関数の型まで移動する
			using NextMethod = NextClass::NextMethod;

		};

		//仕様
		//Functionに対してセットした引数が無効な型だった場合
		template<int t_FunctionNumber,int ...t_Datas>
		struct S_CorrectType<E_Mode::SetJudge,0,t_FunctionNumber,t_Datas...>
		{
			using Type = std::nullopt_t;
		};

		//仕様
		//Functionに対してセットした引数の全てが成功した場合
		template<int ...t_Datas>
		struct S_CorrectType<E_Mode::SetJudge,1,tuple_size, t_Datas...>
		{
			using Type = T_Data;

		};


		//仕様
		//Functionsに対して[T_FlontArgs]で呼び出せる関数が存在する場合
		template<int t_FunctionNumber, int ...t_FnArgsNumber>
		struct S_CorrectType<E_Mode::MethodSearch, 0, t_FunctionNumber, t_FnArgsNumber...>
		{
			using Type = S_MethodExecution<t_FunctionNumber,t_FnArgsNumber...>;

		};

		//仕様
		//Functionsに対して[T_FlontArgs]で呼び出せる関数が無かった場合
		template<int ...t_FnArgsNumber>
		struct S_CorrectType<E_Mode::MethodSearch,1, tuple_size, t_FnArgsNumber...>
		{
			using Type = std::nullopt_t;

		};


		using SetJudge= S_CorrectType<E_Mode::SetJudge>::Type;

		using MethodSearch= S_CorrectType<E_Mode::MethodSearch>::Type;


	};

}