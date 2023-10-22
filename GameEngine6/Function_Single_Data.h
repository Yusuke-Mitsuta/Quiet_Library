#pragma once

#include"Function_Core.h"
#include"Tuple.h"
#include"Concept.h"

#include"Function_Args_Chack.h"

namespace N_Function
{

	//仕様
	//関数オブジェクトの型に対して、続く引数の型が有効か判定する。
	//
	//テンプレート
	//[T_Fn_Parts...]::
	// 第一引数は第二引数の呼び出しに使用するクラスポインターの型である。クラスポインターの型を判定しない場合は指定不要である。静的メソッド、クラスポインターの型を指定済み、の場合は指定不可である。
	// 第二引数は関数の型、若しくは、引数をbindした型[Function_Core],[Method_Core]とする
	// 第三引数以降は、第二引数の関数オブジェクトの引数に指定する型リスト
	template<class ...T_Fn_Parts>
	struct I_Function_Single_Data
	{
	private:

		//仕様
		//関数オブジェクトの型に対して、続く引数の型が有効か判定が無効の場合
		template<class ...T_Fn_Parts>
		struct S_Function_Data
		{
			using function = invalid_t;
			using method = invalid_t;
			using request_args = invalid_t;
			using bind_args = invalid_t;
			using c_name = invalid_t;
			using r_type = invalid_t;

			static constexpr int lelve = -1;
		};

		//仕様
		//tuple_tでまとめられている場合、展開する
		template<class ...T_Fn_Parts>
		struct S_Function_Data<tuple_t<T_Fn_Parts...>> :
			S_Function_Data<T_Fn_Parts...>
		{};

		template<class ...T_Head,class T,class ...T_Tail>
		struct S_Function_Data<tuple_tp<tuple_t<T_Head...>,T,tuple_t<T_Tail...>>> :
			U_if_t1< S_Function_Data<T_Head...,T,T_Tail...>, S_Function_Data<T_Head..., T_Tail...>,not_is_invalid<T>>
		{};

		template<class ...TP_Method_Inner>
		struct S_Parent;

		//仕様
		//[using request_args],[using bind_args]を定義する
		//要求する引数の型に、指定する引数の型が正しいか判定する
		// 
		//テンプレート
		//[T_Parent]::現在の関数オブジェクトの一つ親の型
		//[T_Bind_Args...]::指定する引数の型
		template<class T_Parent, class ...T_Bind_Args>
		struct S_Args :
			S_Args<typename T_Parent::request_args,T_Bind_Args...>
		{};

		//仕様
		//[using request_args],[using bind_args]を定義する
		//要求する引数の型に、指定する引数の型が正しいか判定する
		// 
		//テンプレート
		//[tuple_tp<T_Head,T,T_Tail>]::要求する引数の型、及び、その型の未判定の引数の位置を示す
		//[T_Bind_Args...]::指定する引数の型
		template<class T_Head,class T,class T_Tail, class ...T_Bind_Args>
		struct S_Args<tuple_tp<T_Head,T,T_Tail>,T_Bind_Args...>
		{
		private:
			using args_chack = I_Function_Args_Chack<
				tuple_tp<T_Head, T, T_Tail>, tuple_t<T_Bind_Args...>>;

		public:
			using request_args = args_chack::request_args;

			using bind_args = args_chack::bind_args;

		};


		//仕様
		//[using method]を定義する
		//[method]は使用するクラスポインタの型を未指定のオブジェクトを示す
		//テンプレート
		//[T_Parent]::元にする関数オブジェクト
		//[T_Bind_Args...]::指定する引数の型
		template<class T_Parent, class ...T_Bind_Args>
		struct S_Method
		{
			using function = invalid_t;
			using method = Method_Core<T_Parent, T_Bind_Args...>;
		};

		//仕様
		//第一引数が[Function_Core< ... >]の場合、[Method_Core< ... >]のインナーテンプレートに[Function_Core]が存在させない為に[Function_Core]を[Method_Core]に変換する
		//
		//テンプレート
		//[T_Dedicated_Point*]::[T_Fn]で使用するクラスポインタの型
		//[T_Fn]::関数オブジェクトの型
		//[T_Bind_Args...]::指定する引数の型
		template<class ...TP_Function_Inner, class ...T_Bind_Args>
		struct S_Method<Function_Core<TP_Function_Inner...>, T_Bind_Args...>
		{
			using method = Method_Core<typename S_Method<TP_Function_Inner...>::method, T_Bind_Args...>;
		};

		//仕様
		//[using function]を定義する
		//[function]は呼び出せる状態になっている関数オブジェクトを示す
		//
		//テンプレート
		//[T_Fn]::関数オブジェクトの型
		//[T_Bind_Args...]::指定する引数の型
		//
		//補足
		//[function]はクラスポインターを指定済み、若しくは、静的メソッドの場合に限る
		template<class T_Fn, class ...T_Bind_Args>
		struct S_Function :
			S_Method<T_Fn, T_Bind_Args...>
		{
			using function = Function_Core< T_Fn, T_Bind_Args...>;
		};

		//仕様
		//クラスポインタの型が正しいか判定し、正なら[using function]を定義する
		//
		//テンプレート
		//[T_Dedicated_Point*]::[T_Fn]で使用するクラスポインタの型
		//[T_Fn]::関数オブジェクトの型
		//[T_Bind_Args...]::指定する引数の型
		template<class T_Dedicated_Point,class T_Fn, class ...T_Bind_Args>
		struct S_Function<T_Dedicated_Point*, T_Fn, T_Bind_Args...> :
			S_Method<T_Fn, T_Bind_Args...>
		{
			using function = U_if_t1<Function_Core< T_Fn, T_Bind_Args...>,invalid_t, convertible_to<T_Dedicated_Point, typename S_Function_Data<T_Fn>::c_name>>;
		};

		//仕様
		//関数オブジェクトを何回包み込んだか判定する
		//
		//テンプレート
		//[TP_Method_Inner...]::一回包み込んだ中身
		//
		//補足
		//
		//一回包み込んだ中身とは
		//[Method_Core<TP_Method_Inner...>]or[Function_Core<TP_Method_Inner...>]のインナーテンプレートを指す
		template<class ...TP_Method_Inner>
		struct S_Parent
		{
			using parent = typename S_Function_Data<TP_Method_Inner...>;

			using c_name = parent::c_name;
			using r_type = parent::r_type;

			static constexpr int lelve = parent::lelve + 1;

		};
		
		//仕様
		//関数オブジェクトが静的メソッドの場合
		template<class T_RType, class ...T_Args, class ...T_Bind_Args>
		struct S_Function_Data<T_RType(*)(T_Args...), T_Bind_Args...> :
			S_Function<T_RType(*)(T_Args...), T_Bind_Args...>,
			S_Args<typename tuple_t<T_Args...>::back,T_Bind_Args...>
		{
			using c_name = invalid_t;
			using r_type = T_RType;

			static constexpr int lelve = 0;
		};
		//仕様
		//関数オブジェクトがクラスメソッドの場合、かつクラスポインタの型を判定しない場合
		template<class T_CName, class T_RType, class ...T_Args, class ...T_Bind_Args>
		struct S_Function_Data<T_RType(T_CName::*)(T_Args...), T_Bind_Args...> :
			S_Method<T_RType(T_CName::*)(T_Args...), T_Bind_Args...>,
			S_Args<typename tuple_t<T_Args...>::back, T_Bind_Args...>
		{
			using c_name = T_CName;
			using r_type=T_RType;

			static constexpr int lelve = 0;
		};	

		//仕様
		//関数オブジェクトがクラスメソッドの場合、かつクラスポインタの型を判定する場合
		template<class T_Dedicated_Point, class T_CName, class T_RType, class ...T_Args, class ...T_Bind_Args>
		struct S_Function_Data<T_Dedicated_Point*, T_RType(T_CName::*)(T_Args...), T_Bind_Args...> :
			S_Function<T_Dedicated_Point*,T_RType(T_CName::*)(T_Args...), T_Bind_Args...>,
			S_Args<typename tuple_t<T_Args...>::back, T_Bind_Args...>
		{
			using c_name = T_CName;
			using r_type = T_RType;

			static constexpr int lelve = 0;
		};

		//仕様
		//引数をバインド済み、かつクラスポインタの型を判定しない場合
		template<class ...TP_Method_Inner, class ...T_Bind_Args>
		struct S_Function_Data<Method_Core<TP_Method_Inner...>, T_Bind_Args...> :
			S_Method<Method_Core<TP_Method_Inner...>, T_Bind_Args...>,
			S_Args<S_Function_Data<TP_Method_Inner...>, T_Bind_Args...>,
			S_Parent<TP_Method_Inner...>
		{};

		//仕様
		//引数をバインド済み、かつクラスポインタの型を判定する場合
		template<class T_Dedicated_Point, class ...TP_Method_Inner, class ...T_Bind_Args>
		struct S_Function_Data<T_Dedicated_Point*, Method_Core<TP_Method_Inner...>, T_Bind_Args...> :
			S_Function<T_Dedicated_Point*, Method_Core<TP_Method_Inner...>, T_Bind_Args...>,
			S_Args<S_Function_Data<TP_Method_Inner...>, T_Bind_Args...>,
			S_Parent<TP_Method_Inner...>
		{};

		//仕様
		//引数バインド済み、及び、クラスポインタの型を指定済み、又は静的メソッドの場合
		template<class ...TP_Function_Inner, class ...T_Bind_Args>
		struct S_Function_Data<Function_Core<TP_Function_Inner...>, T_Bind_Args...> :
			S_Function<Function_Core<TP_Function_Inner...>, T_Bind_Args...>,
			S_Args<S_Function_Data<TP_Function_Inner...>, T_Bind_Args...>,
			S_Parent<TP_Function_Inner...>
		{};


		//仕様
		//バインド済み引数が無効の場合、[function],[method]を無効値に変更する
		template<class T_Parent, class T_Args_Chack = typename T_Parent::bind_args>
		struct S_is_Valid_Method_Data
		{
			using function = T_Parent::function;
			using method = T_Parent::method;
		};

		template<class T_Parent>
		struct S_is_Valid_Method_Data<T_Parent, invalid_t>
		{
			using function = invalid_t;
			using method = invalid_t;
		};


	public:
		using type = S_Function_Data<T_Fn_Parts...>;

		using function = typename S_is_Valid_Method_Data<type>::function;
		using method = typename S_is_Valid_Method_Data<type>::method;
		using request_args = type::request_args;
		using bind_args = type::bind_args;
		using c_name = type::c_name;
		using r_type = type::r_type;

		static constexpr int lelve = type::lelve;

	};


	template<class ...T_Fn_Parts>
	struct S_Function_Single_Data
	{
		using Function = invalid_t;
		using Method = invalid_t;
		using Request_Args = invalid_t;
		using Bind_Args = invalid_t;
		using Bind_Args_Expand = invalid_t;
		using Bound_Args = invalid_t;
		using CName = invalid_t;
		using RType = invalid_t;

		static constexpr int Lelve = -1;
	};





	template<class T_RType, class ...T_Args, class ...T_Bind_Args>
		requires not_is_invalid
	<typename I_Function_Args_Chack<tuple_t<T_Args...>,
	tuple_t<T_Bind_Args...>>::Request_Args>
	struct S_Function_Single_Data<T_RType(*)(T_Args...), T_Bind_Args...>
	{
	private:
		using Args_Set = I_Function_Args_Chack<tuple_t<T_Args...>,
			tuple_t<T_Bind_Args...>>;
	public:
		using Method = Method_Core<T_RType(*)(T_Args...)>;
		using Function = Function_Core<Method>;


		using RequestArgs = Args_Set::Request_Args;
		using BindArgs = tuple_t<T_Bind_Args...>;

		using BindArgs_Expand = Args_Set::Bind_Args;

		using BoundArgs = BindArgs;

		using CName = invalid_t;
		using RType = T_RType;

		static constexpr int Lelve = 0;

	};

	template<class T_CName, class T_RType, class ...T_Args, class ...T_Bind_Args>
		requires not_is_invalid<typename I_Function_Args_Chack<tuple_t<T_Args...>,
	tuple_t<T_Bind_Args...>>::Request_Args>
	struct S_Function_Single_Data<T_RType(T_CName::*)(T_Args...), T_Bind_Args...> :
		public S_Function_Single_Data<T_RType(*)(T_Args...), T_Bind_Args...>
	{
		using Method = Method_Core<T_RType(T_CName::*)(T_Args...)>;
		using Function = invalid_t;
		using CName = T_CName;

	};


	template<class T_Dedicated_Point, class T_CName, class T_RType, class ...T_Args, class ...T_Bind_Args>
		requires not_is_invalid<typename I_Function_Args_Chack<tuple_t<T_Args...>,
		tuple_t<T_Bind_Args...>>::Request_Args>
			&& convertible_to<T_Dedicated_Point, T_CName>
	struct S_Function_Single_Data<T_Dedicated_Point*, T_RType(T_CName::*)(T_Args...), T_Bind_Args...> :
		public S_Function_Single_Data<T_RType(T_CName::*)(T_Args...), T_Bind_Args...>
	{
		using Parent = S_Function_Single_Data<T_RType(T_CName::*)(T_Args...), T_Bind_Args...>;

		using Function = Function_Core<typename Parent::Method>;
	};


	template<class ...TP_Method_Inner, class ...T_Bind_Args>
		requires not_is_invalid<typename I_Function_Args_Chack<typename S_Function_Single_Data<TP_Method_Inner...>::RequestArgs,
			tuple_t<T_Bind_Args...>>::Request_Args>
	struct S_Function_Single_Data<Method_Core<TP_Method_Inner...>, T_Bind_Args...> :
		public S_Function_Single_Data<TP_Method_Inner...>
	{
	private:
		using Parent = S_Function_Single_Data<TP_Method_Inner...>;
		using Args_Set = I_Function_Args_Chack<typename Parent::RequestArgs,
			tuple_t<T_Bind_Args...>>;
	public:

		using Method = Method_Core<Method_Core<TP_Method_Inner...>>;
		using BindArgs = tuple_t<T_Bind_Args...>;
		using BindArgs_Expand = Args_Set::Bind_Args;
		using RequestArgs = Args_Set::Request_Args;
		using BoundArgs = U_Merge_Element_t<T_Bind_Args..., typename Parent::BoundArgs>;

		static constexpr int Lelve = Parent::Lelve + 1;
	};

	template<class T_Dedicated_Point, class ...TP_Method_Inner, class ...T_Bind_Args>
		requires not_is_invalid<typename S_Function_Single_Data<Method_Core<TP_Method_Inner...>, T_Bind_Args...>::RequestArgs> &&
	convertible_to<T_Dedicated_Point,typename  S_Function_Single_Data<Method_Core<TP_Method_Inner...>, T_Bind_Args...>::CName>
	struct S_Function_Single_Data<T_Dedicated_Point*, Method_Core<TP_Method_Inner...>, T_Bind_Args...> :
		public S_Function_Single_Data<Method_Core<TP_Method_Inner...>, T_Bind_Args...>
	{
		using Parent = S_Function_Single_Data<Method_Core<TP_Method_Inner...>, T_Bind_Args...>;
		using Function = Function_Core<typename Parent::Method>;
	};

	template<class ...TP_Function_Inner, class ...T_Bind_Args>
		requires not_is_invalid<typename I_Function_Args_Chack<
			typename S_Function_Single_Data<Function_Core<TP_Function_Inner...>>::RequestArgs,
			tuple_t<T_Bind_Args...>>::Request_Args>
	struct S_Function_Single_Data<Function_Core<TP_Function_Inner...>, T_Bind_Args...> :
		public S_Function_Single_Data<TP_Function_Inner...>
	{
	private:
		using Parent = S_Function_Single_Data<TP_Function_Inner...>;
		using Args_Set = I_Function_Args_Chack<typename Parent::RequestArgs,
			tuple_t<T_Bind_Args...>>;
	public:

		using Method = Method_Core<Method_Core<TP_Function_Inner...>>;
		using Function = Function_Core<Function_Core<TP_Function_Inner...>>;
		using BindArgs = tuple_t<T_Bind_Args...>;
		using BindArgs_Expand = Args_Set::Bind_Args;
		using RequestArgs = Args_Set::Request_Args;
		using BoundArgs = U_Merge_Element_t<T_Bind_Args...,typename Parent::BoundArgs>;

		static constexpr int Lelve = Parent::Lelve + 1;
	};


}
