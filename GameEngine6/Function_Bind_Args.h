#pragma once
#include"Function_Address.h"
#include<optional>

namespace N_Function
{
	//仕様
	//関数ポインターに対して、引数の値が正しいか、後方一致で判定する
	//
	//テンプレート
	//T_Fn_Args::関数ポインター、指定する引数、のパラメータパック
	//
	//補足
	//T_Fn_Argsは関数ポインター、それに指定する引数、次の関数ポインター、となるようにする事
	template<class ...T_Fn_Args>
	struct IS_BindArgs
	{
	private:

		template<class ...T_Fn_Args>
		struct S_BindArgs {};

		template<class C_Name, class R_Type, class ...T_Args, class ...T_Fn_Args>
		struct S_BindArgs<R_Type(C_Name::*)(T_Args...), T_Fn_Args...>
		{
			using Type = S_BindArgs<S_Address
				<R_Type(C_Name::*)(T_Args...), std::tuple<>>, T_Fn_Args...>::Type;
		};

		template<class ...T_Zip_Fn_Args, class ...T_Fn_Args>
		struct S_BindArgs<std::tuple<T_Zip_Fn_Args...>, T_Fn_Args...>
		{
			using Type = S_BindArgs<T_Zip_Fn_Args..., T_Fn_Args...>::Type;
		};

		//仕様
		//関数ポインターを指定し、引数を精査する
		template< class C_Name, class R_Type, class ...T_Args, class ...T_DefaultSetArgs, class ...T_Fn_Args>
		struct S_BindArgs<S_Address<R_Type(C_Name::*)(T_Args...), std::tuple<T_DefaultSetArgs...>>, T_Fn_Args...>
		{
			using T_Method = R_Type(C_Name::*)(T_Args...);

			template<class Args, class ...T_Fn_Args>
			struct S_BindArgsExecution {};

			//仕様
			//指定した関数に対して、引数の型を集める
			template<class ...T_NewDefaultSetArgs, class ...T_Fn_Args>
			struct S_BindArgsExecution<std::tuple<T_NewDefaultSetArgs...>, std::nullopt_t, T_Fn_Args...>
			{
				using Type = S_BindArgsExecution;
				using Judge = std::bool_constant<tuple_back_part_convertible_to<std::tuple<T_NewDefaultSetArgs..., T_DefaultSetArgs...>, std::tuple<T_Args...>>>;
				using Tuple = std::tuple<T_Fn_Args..., S_Address<T_Method, std::tuple<T_NewDefaultSetArgs..., T_DefaultSetArgs...>>>;
			};

			//仕様
			//指定した関数に対して、引数の型を集める
			template<class ...T_NewDefaultSetArgs, class T_SetArgs, class ...T_Fn_Args>
			struct S_BindArgsExecution<std::tuple<T_NewDefaultSetArgs...>, T_SetArgs, T_Fn_Args...>
			{
				using Type = S_BindArgsExecution<std::tuple<T_NewDefaultSetArgs..., T_SetArgs>, T_Fn_Args...>::Type;
			};

			//仕様
			//ヒットした関数ポインターをS_Address型に変換し、引数を集めるのを終了する。
			template<class ...T_NewDefaultSetArgs, class C_Name, class R_Type, class ...T_Args, class ...T_Fn_Args>
			struct S_BindArgsExecution<std::tuple<T_NewDefaultSetArgs...>, R_Type(C_Name::*)(T_Args...), T_Fn_Args...>
			{
				using Type = S_BindArgsExecution<std::tuple<T_NewDefaultSetArgs...>,
					S_Address<R_Type(C_Name::*)(T_Args...), std::tuple<>>, T_Fn_Args...>::Type;
			};

			//仕様
			//次の関数ポインターがヒットした際、指定した関数に対しての引数を集めるのを終了し、それが正しい型の引数か判定する
			//その後ヒットした関数ポインターに対しての、引数を集めを開始する
			template<class ...T_NewDefaultSetArgs, class ...T_Flont_Fn, class ...T_Fn_Args>
				requires tuple_back_part_convertible_to<std::tuple<T_NewDefaultSetArgs..., T_DefaultSetArgs...>, std::tuple<T_Args...>>
			struct S_BindArgsExecution<std::tuple<T_NewDefaultSetArgs...>, S_Address<T_Flont_Fn...>, T_Fn_Args...>
			{
				using Type = S_BindArgs<S_Address<T_Flont_Fn...>, T_Fn_Args...,
					S_Address<T_Method, std::tuple<T_NewDefaultSetArgs..., T_DefaultSetArgs...>>>::Type;
			};

			//仕様
			//指定した関数に対しての引数を集めるのを終了し、それが正しくない場合、処理を終了する
			template<class ...T_NewDefaultSetArgs, class ...T_Flont_Fn, class ...T_Fn_Args>
			struct S_BindArgsExecution<std::tuple<T_NewDefaultSetArgs...>, S_Address<T_Flont_Fn...>, T_Fn_Args...>
			{
				using Type = S_BindArgsExecution<std::tuple<T_NewDefaultSetArgs...>, std::nullopt_t>::Type;
			};

			using Type = S_BindArgsExecution<std::tuple<>, T_Fn_Args...>::Type;
		};

		using Type = S_BindArgs<T_Fn_Args..., std::nullopt_t>::Type;

	public:
		//仕様
		//関数ポインター、引数の型をtupleのS_Address型にまとめた型が返る
		using TupleType = Type::Tuple;

		//仕様
		//関数ポインター、引数の型をtupleのS_Address型にまとめた結果、成功どうか返る
		using Judge = Type::Judge;

	};

}
