#pragma once

#include"Function_Core.h"
#include"Tuple.h"
#include"Concept.h"

#include"Function_Args_Chack.h"

template<class TP_Fns, class TP_Args_type>
class Function;

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

		


	//private:

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

			static constexpr size_t fn_count = 0;
		};
		



		//仕様
		//先頭の型がクラス型かつ、ポインター型であり、メソッドが指定されているなら、
		//クラスのポインター型の判定を行う
		template<class T_Dedicated_Point, class ...T_Fn_Parts>
			requires (std::is_class_v<T_Dedicated_Point>)
		struct S_Function_Data<T_Dedicated_Point*, T_Fn_Parts...> :
			S_Function_Data<T_Fn_Parts...>
		{

			template<class T_Fns, class ...T_Bind_Args>
			struct method_change_function
			{
				using type = Method_Core<T_Fns, T_Bind_Args...>;
			};


			template<same_as_template_type<Function_Core> ...T_Fns, class ...T_Bind_Args>
			struct method_change_function<tuple_t<T_Fns...>, T_Bind_Args... >
			{
				using type = Function_Core<tuple_t<T_Fns...>, T_Bind_Args...>;
			};


			template<class ...T_Fn_parts, class ...T_Bind_Args>
			struct method_change_function<Function_Core<T_Fn_parts...>, T_Bind_Args... >
			{
				using type = Function_Core<Function_Core<T_Fn_parts...>, T_Bind_Args...>;
			};


			template<class T_Fns>
			struct Method_Point_Chack 
			{
				using type = T_Fns;
			};

			template<class T_Fn, class ...T_Bind_Args>
				requires (convertible_to<T_Dedicated_Point, typename S_Function_Data<T_Fn>::c_name>)
			struct Method_Point_Chack<Method_Core<T_Fn, T_Bind_Args...>>
			{
				using type = Function_Core<T_Fn, T_Bind_Args...>;
			};

			template<class T_Fn, class ...T_Bind_Args>
				requires (S_Function_Data<T_Fn>::fn_count != 1 )
			struct Method_Point_Chack<Method_Core<T_Fn, T_Bind_Args...>>
			{

				using type = method_change_function<
					typename Method_Point_Chack< T_Fn>::type,T_Bind_Args...>::type;
			};

			template<class ...T_Fns,class ...T_Bind_Args>
			struct Method_Point_Chack<Method_Core<tuple_t<T_Fns...>,T_Bind_Args...>>
			{

				using type = typename method_change_function<tuple_t<typename Method_Point_Chack<T_Fns>::type...>>::type;

			};

			using base = typename S_Function_Data<T_Fn_Parts...>;
			

			using function = typename Method_Point_Chack<typename base::function>::type;

				
		};
		

		template<class T_Fns, class ...T_Bind_Args>
		struct S_Args;


		//仕様
		//[using request_args],[using bind_args]を定義する
		//要求する引数の型に、指定する引数の型が正しいか判定する
		//
		//テンプレート
		//[T_Parent]::現在の関数オブジェクトの一つ親の型
		//[T_Bind_Args...]::指定する引数の型
		template<class T_Fns, class ...T_Bind_Args>
		struct S_Args
		{
			using request_args = invalid_t;


			using bind_args = invalid_t;
		};

		template<class ...T_Fns, class ...T_Bind_Args>
		struct S_Args<tuple_t<T_Fns...>, T_Bind_Args...>
		{

			using request_args = tuple_t<typename S_Args<T_Fns, T_Bind_Args...>::request_args...>;

			using bind_args = tuple_t<T_Bind_Args...>;

		};

		//仕様
		//[using request_args],[using bind_args]を定義する
		//要求する引数の型に、指定する引数の型が正しいか判定する
		// 
		//テンプレート
		//[tuple_tp<T_Head,T,T_Tail>]::要求する引数の型、及び、その型の未判定の引数の位置を示す
		//[T_Bind_Args...]::指定する引数の型
		template<class T_Head, class T, class T_Tail, class ...T_Bind_Args>
		struct S_Args<tuple_tp<T_Head, T, T_Tail>, T_Bind_Args...>
		{
		private:
			using args_chack = I_Function_Args_Chack<
				tuple_tp<T_Head, T, T_Tail>, tuple_t<T_Bind_Args...>>;

		public:

			using request_args = args_chack::request_args;

			using bind_args = tuple_t<T_Bind_Args...>;
			//args_chack::bind_args;

		};




		//仕様
		//関数オブジェクトが静的メソッドの場合
		template<class T_RType, class ...T_Args, class ...T_Bind_Args>
		struct S_Function_Data<T_RType(*)(T_Args...), T_Bind_Args...> :
			S_Args<typename tuple_t<T_Args...>::back, T_Bind_Args...>
		{

			using function = Function_Core<T_RType(*)(T_Args...), T_Bind_Args...>;
			using c_name = invalid_t;
			
			using r_type = T_RType;

			static constexpr size_t fn_count = 1;
		};


		//仕様
		//関数オブジェクトがクラスメソッドの場合、かつクラスポインタの型を判定する場合
		template<class T_CName, class T_RType, class ...T_Args, class ...T_Bind_Args>
		struct S_Function_Data<T_RType(T_CName::*)(T_Args...), T_Bind_Args...> :
			S_Args<typename tuple_t<T_Args...>::back, T_Bind_Args...>
		{

			using function = Method_Core<T_RType(T_CName::*)(T_Args...), T_Bind_Args...>;
			using c_name = T_CName;
			using r_type = T_RType;

			static constexpr size_t fn_count = 1;
		};


		//仕様
		//既に引数を設定済みの関数オブジェクトに新たに引数を設定する場合
		template<template<class...>class T_Outer_Core, class T_Fn, class ...T_before_Bind_Args, class ...T_Bind_Args>
		struct S_Function_Data<T_Outer_Core<T_Fn, T_before_Bind_Args...>, T_Bind_Args...> :
			S_Args<typename S_Function_Data<T_Fn, T_before_Bind_Args...>::request_args, T_Bind_Args...>
		{
			using function = T_Outer_Core<T_Outer_Core<T_Fn, T_before_Bind_Args...>, T_Bind_Args...>;

			using c_name = S_Function_Data<T_Fn>::c_name;
			static constexpr size_t fn_count = S_Function_Data<T_Fn>::fn_count;
		};


		//仕様
		//複数に纏められている関数を展開する
		template<template<class...>class T_Outer_Core,  class ...T_Fns, class ...T_before_Bind_Args, class ...T_Bind_Args>
		struct S_Function_Data<T_Outer_Core<tuple_t<T_Fns...>, T_before_Bind_Args...>, T_Bind_Args...>
		{
			using function = T_Outer_Core<T_Outer_Core<tuple_t<T_Fns...>, T_before_Bind_Args...>, T_Bind_Args... >;

			static constexpr size_t fn_count = (S_Function_Data<T_Fns>::fn_count + ...);
			using c_name = invalid_t;
			using request_args = tuple_t<typename S_Function_Data<Function_Core<T_Fns, T_before_Bind_Args...>, T_Bind_Args...>::request_args...>;
			using bind_args = tuple_t<T_Bind_Args...>;

		};


		template<class ...T_Fns,class T_type_numbers , class T_Tuple_Args_types,class ...T_Bind_Args>
		struct S_Function_Data<Function<tuple_t<tuple_t<T_Fns...>,T_type_numbers>, T_Tuple_Args_types>, T_Bind_Args...> :
			S_Function_Data<Function_Core<tuple_t<T_Fns...>, T_Bind_Args...>>
		{
		};

		//template<class ...T_Fns, class T_type_numbers, class ...T_Bind_Args>
		//struct S_Function_Data<Function<tuple_t<tuple_t<T_Fns...>, T_type_numbers>>, T_Bind_Args...> :
		//	S_Function_Data<Method_Core<tuple_t<T_Fns...>, T_Bind_Args...>>
		//{
		//};




		//仕様
		//バインド済み引数が無効の場合、[function],[method]を無効値に変更する
		template<class T_Parent, class T_Args_Chack = typename T_Parent::bind_args>
		struct S_is_Valid_Method_Data
		{
			using function = T_Parent::function;
		};

		template<class T_Parent>
		struct S_is_Valid_Method_Data<T_Parent, invalid_t>
		{
			using function = invalid_t;
		};



		//仕様
		//tuple_tでまとめられている場合、展開する
		template<class ...T_Fn_Parts>
		struct S_Function_Data<tuple_t<T_Fn_Parts...>> :
			S_Function_Data<T_Fn_Parts...>
		{};

		template<class ...T_Head, class T, class ...T_Tail>
		struct S_Function_Data<tuple_tp<tuple_t<T_Head...>, T, tuple_t<T_Tail...>>> :
			S_Function_Data<T_Head..., T, T_Tail...> {};

		template<class ...T_Head, class ...T_Tail>
		struct S_Function_Data<tuple_tp<tuple_t<T_Head...>, invalid_t, tuple_t<T_Tail...>>> :
			S_Function_Data<T_Head..., T_Tail...> {};


	public:



		using type = N_Tuple::I_Expand_Set<S_Function_Data, T_Fn_Parts...>::type;
		using function =
			//type::function;
			typename S_is_Valid_Method_Data<type>::function;
		using request_args = type::request_args;
		using bind_args = type::bind_args;

		using c_name = type::c_name;

		static constexpr size_t fn_count = type::fn_count;

	};

}









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




	//private:

		//仕様
		//関数オブジェクトの型に対して、続く引数の型が有効か判定が無効の場合
		template<class T_Result,class ...T_Fn_Parts>
		struct S_Function_Data
		{


			using function = invalid_t;
			using method = invalid_t;
			using request_args = invalid_t;
			using bind_args = invalid_t;
			using c_name = invalid_t;
			using r_type = invalid_t;

			static constexpr size_t fn_count = 0;
		};

		template<class T_Fn_Core,class T_pointer>
		struct I_pointer_check
		{
			using type = invalid_t;
		};

		template<class ...T_Parts, class T_pointer>
		struct I_pointer_check<Function_Core<T_Parts...>, T_pointer>
		{
			template<class T_Core,class T_Fn = typename T_Core::function , class T_request_point = U_Parts_Search_InnerType<"request_pointer", T_Fn>>
			struct S_point_check
			{

			};

			template<class T_Core, class T_Fns, class T_request_point>
			struct S_point_check<T_Core,tuple_t<T_Fns...>>
			{

			};

			using type = invalid_t;
		};
		
		template<class ...T_Result, class T_Dedicated_Point, class ...T_Fn_Parts>
			requires (std::is_class_v<T_Dedicated_Point>)
		struct S_Function_Data<Function_Core<T_Result...>,T_Dedicated_Point*, T_Fn_Parts...>
		{

			using pointer_check = S_Function_Data<Function_Core<T_Result...,
				Parts<"pointer",T_Dedicated_Point>>,T_Fn_Parts...>::type;
			using type = 
		};

		//仕様
		//関数オブジェクトがクラスメソッドの場合、かつクラスポインタの型を判定する場合
		template<class ...T_Result, class T_CName, class T_RType, class ...T_Args, class ...T_Bind_Args>
		struct S_Function_Data<Function_Core<T_Result...>, T_RType(T_CName::*)(T_Args...), T_Bind_Args...>
		{
			using fn = T_RType(T_CName::*)(T_Args...);

			using type = S_Function_Data<
				Function_Core<T_Result...,
				Parts<"function",
					Function_Core<Parts<"function", fn>,
					Parts<"request_args", typename tuple_t<T_Args...>::back>,
					Parts<"c_name", T_CName>,
					Parts<"request_pointer", T_CName>,
					Parts<"r_type", T_RType>>>,
				Parts<"bind_args", tuple_t<T_Bind_Args...>>
				>>::type;
		};

		//仕様
		//関数オブジェクトが静的メソッドの場合
		template<class ...T_Result, class T_RType, class ...T_Args, class ...T_Bind_Args>
		struct S_Function_Data<Function_Core<T_Result...>, T_RType(*)(T_Args...), T_Bind_Args...>
		{
			using fn = T_RType(*)(T_Args...);

			using type = S_Function_Data<
				Function_Core<T_Result...,
				Parts<"function",
					Function_Core<Parts<"function",fn>,
					Parts<"request_args", typename tuple_t<T_Args...>::back>,
					Parts<"r_type", T_RType>>>,
				Parts<"bind_args", tuple_t<T_Bind_Args...>>
				>>::type;


		};

		template<class ...T_Result, class T_Fn, class ...T_Bind_Args>
		struct S_Function_Data<Function_Core<T_Result...>, T_Fn,T_Bind_Args...>
		{
			using type = S_Function_Data<
				Function_Core<T_Result...,
					Parts<"function",T_Fn>,
					Parts<"bind_args",tuple_t<T_Bind_Args...>>
				>>::type;
		};



		template<class T_Core, class T_Fn = typename T_Core::function, class T_request_args = U_Parts_Search_InnerType<"request_args", T_Fn>>
		struct S_Args
		{
			using type = I_Function_Args_Chack<T_request_args, typename T_Core::bind_args>::request_args;

		};

		template<class T_Core, class T_Fn, class ...T_request_args>
		struct S_Args<T_Core, T_Fn,tuple_t<T_request_args...>>
		{
			using type = tuple_t<typename S_Args<T_Core, T_Fn, T_request_args>::type...>;
		};


		template<class T_Core,class ...T_Fns ,class T_request_args>
		struct S_Args<T_Core,tuple_t<T_Fns...>,T_request_args>
		{
			using type = tuple_t<typename S_Args<T_Core,T_Fns>::type...>;
		};


		template<class ...T_Result>
		struct S_Function_Data<Function_Core<T_Result...>>
		{
			using core = Function_Core<T_Result...>;

			using type = 
				Function_Core<T_Result...,
				Parts<"request_args" , S_Args<core>>
				>>;
		};




		template<class T_Core>
		struct I_Request
		{
			template<N_Constexpr::String t_request_name, class T_Fn = typename T_Core::function,
				class T_request = typename U_Parts_Search_InnerType<t_request_name, T_Fn>::type>
			struct S_Request
			{
				template<N_Constexpr::String t_request_name = t_request_name, class T_Fn = T_Fn, class T_request = T_request>
				struct S_Switch
				{
					using type = T_request;
				};

				template<class T_Fn, class T_request>
				struct S_Switch<"request_args", T_Fn, T_request >
				{
					using type = I_Function_Args_Chack<T_request, typename T_Core::bind_args>::request_args;
				};

				template<class T_Fn, class T_request>
					requires(convertible_to<typename U_Parts_Search_InnerType<"pointer", T_Core>::type, T_request>)
				struct S_Switch<"request_pointer", T_Fn, T_request>
				{
					using type = invalid_t;
				};

				using type = S_Switch<>::type;
			};


			template<N_Constexpr::String t_request_name, class T_Fn, class ...T_request>
			struct S_Request<t_request_name, T_Fn, tuple_t<T_request...>>
			{
				using type = tuple_t<typename S_Request<t_request_name, T_Fn, T_request>::type...>;
			};

			template<N_Constexpr::String t_request_name, class ...T_Fns, class T_request>
			struct S_Request<t_request_name, tuple_t<T_Fns...>, T_request>
			{
				using type = tuple_t<typename S_Request<t_request_name, T_Fns>::type...>;
			};

			using request_args = S_Request<"request_args">::type;

			using request_pointer = S_Request<"request_pointer">::type;

		};




		//仕様
		//バインド済み引数が無効の場合、[function],[method]を無効値に変更する
		template<class T_Parent, class T_Args_Chack = typename T_Parent::request_args>
		struct S_is_Valid_Method_Data
		{
			using function = T_Parent::function;
		};

		template<class T_Parent>
		struct S_is_Valid_Method_Data<T_Parent, invalid_t>
		{
			using function = invalid_t;
		};



		//仕様
		//tuple_tでまとめられている場合、展開する
		template<class ...T_Fn_Parts>
		struct S_Function_Data<tuple_t<T_Fn_Parts...>> :
			S_Function_Data<T_Fn_Parts...>
		{};

		template<class ...T_Head, class T, class ...T_Tail>
		struct S_Function_Data<tuple_tp<tuple_t<T_Head...>, T, tuple_t<T_Tail...>>> :
			S_Function_Data<T_Head..., T, T_Tail...> {};

		template<class ...T_Head, class ...T_Tail>
		struct S_Function_Data<tuple_tp<tuple_t<T_Head...>, invalid_t, tuple_t<T_Tail...>>> :
			S_Function_Data<T_Head..., T_Tail...> {};


	public:



		using type = N_Tuple::I_Expand_Set<S_Function_Data, T_Fn_Parts...>::type;
		using function =
			//type::function;
			typename S_is_Valid_Method_Data<type>::function;
		using request_args = type::request_args;
		using bind_args = type::bind_args;

		using c_name = type::c_name;

		static constexpr size_t fn_count = type::fn_count;

	};

}

