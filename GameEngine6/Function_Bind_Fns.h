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
		using reverse_tuple_element = std::tuple_element<
			tuple_size - _Index, T_Tuple>::type;

		//仕様
		//引数のバインド済み関数ポインターを格納し、最後の関数なら格納処理を終了する
		//
		//テンプレート
		//t_MethodTupleNumber::現在、精査したタプルの要素数
		//...T_BoundFns::引数のバインド済み関数ポインター
		//補足
		//t_TupleNumberは後ろから何番目にアクセスするかを示す
		template<int t_TupleNumber=1, class ...T_BoundFns>
		struct S_BoundFns
		{

			//仕様
			//関数ポインターに対して引数をセットする
			template<class T_Args, int t_TupleNumber, int ...t_ArgsNumber>
			struct S_BindFns
			{
				using NextClass = S_BindFns<reverse_tuple_element<t_TupleNumber + 1>, t_TupleNumber + 1, t_TupleNumber, t_ArgsNumber...>;

				using Type = NextClass::Type;

				using NextMethod = NextClass::NextMethod;
			};

			//仕様
			//Functionに対して引数をセットする
			template<class T_CName, class T_RType, class ...T_Args, int t_MethodTupleNumber, int ...t_ArgsNumber>
			struct S_BindFns<T_RType(T_CName::*)(T_Args...), t_MethodTupleNumber, t_ArgsNumber...>
			{
				static constexpr bool judge = tuple_back_part_convertible_to<std::tuple<reverse_tuple_element<t_ArgsNumber>...>, std::tuple<T_Args...>>;

				using NextClass = S_BoundFns<(t_MethodTupleNumber + 1)* judge,
					Function<std::tuple<T_RType(T_CName::*)(T_Args...), reverse_tuple_element<t_ArgsNumber>...>>,
					T_BoundFns...>;

				using NextMethod = S_BindFns;

				using Type =NextClass::Type;

				template<class T_InputTuple>
				static constexpr void BindFns(T_InputTuple& inputTuple, auto& tuple)
				{
					std::get<(std::tuple_size_v<T_InputTuple>-1) - sizeof...(T_BoundFns)>(inputTuple).emplace(std::get<tuple_size - t_MethodTupleNumber>(tuple), std::get<tuple_size - t_ArgsNumber>(tuple)...);
				}
			};

			//仕様
			//Functionに対して引数をセットする
			template<class T_FunctionInner, int t_MethodTupleNumber>
			struct S_BindFns<Function<T_FunctionInner>, t_MethodTupleNumber>
			{
				using Fn = Function<T_FunctionInner>;

				using NextClass = S_BoundFns<(t_MethodTupleNumber + 1),
					Fn, T_BoundFns...>;

				using NextMethod = S_BindFns;

				using Type = NextClass::Type;

				template<class T_InputTuple>
				static constexpr void BindFns(T_InputTuple& inputTuple, auto& tuple)
				{
					std::get<(std::tuple_size_v<T_InputTuple>-1) - sizeof...(T_BoundFns)>(inputTuple).emplace(std::get<tuple_size - t_MethodTupleNumber>(tuple));
				}
			};
			//仕様
			//Functionに対して引数をセットする
			template<class T_FunctionInner,int t_MethodTupleNumber, int ...t_ArgsNumber>
			struct S_BindFns<Function<T_FunctionInner>, t_MethodTupleNumber, t_ArgsNumber...>
			{
				using Fn = Function<T_FunctionInner>;

				//メモ
				//Defaultの引数と設定した引数を分ける
				static constexpr bool judge = tuple_back_part_convertible_to<typename 
					IS_TupleUnzip<std::tuple<reverse_tuple_element<t_ArgsNumber>..., 
					typename Fn::SetArgs>>::Type,typename Fn::Args>;

				using NextClass = S_BoundFns<(t_MethodTupleNumber + 1)* judge,Function<std::tuple<Fn,reverse_tuple_element<t_ArgsNumber>...>>,
					T_BoundFns...>;

				using NextMethod = S_BindFns;

				using Type = NextClass::Type;

				template<class T_InputTuple>
				static constexpr void BindFns(T_InputTuple& inputTuple, auto& tuple)
				{
					std::get<(std::tuple_size_v<T_InputTuple>-1) - sizeof...(T_BoundFns)>(inputTuple).emplace(std::get<tuple_size - t_MethodTupleNumber>(tuple), std::get<tuple_size - t_ArgsNumber>(tuple)...);

				}
			};
			using NextClass = S_BindFns<reverse_tuple_element<t_TupleNumber>, t_TupleNumber>;

			using Type = NextClass::Type;

			//仕様			
			//パラメータパック内の関数の型まで移動する
			using NextMethod = NextClass::NextMethod;

			//仕様			
			//関数に対して、引数をセットする
			static constexpr void BoundFns(auto& inputTuple, auto& tuple)
			{
				NextMethod::BindFns(inputTuple, tuple);
				NextMethod::NextClass::BoundFns(inputTuple, tuple);
			}
		};

		//仕様
		//Functionに対してセットした引数が無効な型だった場合
		template<class T_FlontBoundFn,class ...T_BoundFns>
		struct S_BoundFns<0,T_FlontBoundFn,T_BoundFns...>
		{
			using Type = S_BoundFns;
			using Judge = std::false_type;
			using FnsType = std::nullopt_t;

			static constexpr void BoundFns(auto& inputTuple, auto& tuple){}
		};

		//仕様
		//Functionに対してセットした引数の全てが成功した場合
		template<class ...T_BoundFns>
		struct S_BoundFns<tuple_size+1,T_BoundFns...>
		{
			using Type = S_BoundFns;
			using Judge = std::true_type;
			using FnsType = std::tuple<T_BoundFns...>;

			static constexpr void BoundFns(auto& inputTuple, auto& tuple) {}
		};

		using Type = S_BoundFns<1>::Type;
		using Judge = Type::Judge;
		using FnsType = Type::FnsType;

		FnsType fns;

		//仕様
		//[FnsType]に対して、[fn_Args...]を関数ごとに分け格納する
		template<size_t ...t_DivideOptionalTuple>
		static constexpr auto BindFns(std::index_sequence<t_DivideOptionalTuple...>,auto&... fn_Args)
		{
			typename S_EnvelopOptional<FnsType>::Type optionalTuple;
			IS_TupleUnzip unzipTuple(fn_Args...);

			S_BoundFns<1>::BoundFns(optionalTuple,unzipTuple.tuple);
			return FnsType(std::get<t_DivideOptionalTuple>(optionalTuple).value()...);
		}

		//仕様
		//複数の関数のとそれに対する引数をセットする
		//
		//引数
		//fn_Args::関数とそれに対する引数のパラメータパック
		constexpr IS_BindFns(T_Fn_Args... fn_Args)
			:fns(BindFns(std::make_index_sequence<std::tuple_size_v<FnsType>>(), fn_Args...)){}

		operator FnsType()
		{
			return fns;
		}

	};

}