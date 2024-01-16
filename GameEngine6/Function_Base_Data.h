#pragma once

#include"Tuple.h"
#include"Concept.h"

template<is_invalid_not T_Front_Parts, class ...T_Parts>
class Function;

namespace N_Function
{
	template<class ...T_Parts>
	struct Function_Core;

	template<class ...T_Fn_Parts>
	struct I_Function_Helper;

	//仕様
	//[T_Fn_Parts...]から、関数にアクセスするポインター、関数オブジェクト、バインドする引数を分別する
	//
	//補足
	//[Function]は[Function_Core]に変更される
	template<class ...T_Fn_Parts>
	struct I_Function_Base_Data
	{

		//仕様
		//存在しないパラメータの参照先
		template<class ...T_Fn_Parts>
		struct S_Function_Data
		{
			using function = invalid_t;
			using bind_args = invalid_t;
			using pointer = invalid_t;
			using c_name = invalid_t;
			using r_type = invalid_t;

		};

		//仕様
		//共通で使用するポインターの型をセットする
		//
		//補足
		//[T_Dedicated_Point]が[Function]の場合はスキップする
		template<class T_Dedicated_Point, class ...T_Fn_Parts>
			requires requires
		{
			requires std::is_class_v<T_Dedicated_Point>;
			requires !same_as_template_type<T_Dedicated_Point, Function>;
		}
		struct S_Function_Data<T_Dedicated_Point*, T_Fn_Parts...> :
			S_Function_Data<T_Fn_Parts...>
		{
			using pointer = T_Dedicated_Point;
		};

		//仕様
		//共通で使用するポインターの型をセットする
		//
		//補足
		//[T_Dedicated_Point]が[Function]の場合はスキップする
		template<class T_Dedicated_Point, class ...T_Fn_Parts>
			requires requires
		{
			requires std::is_class_v<T_Dedicated_Point>;
			requires !same_as_template_type<T_Dedicated_Point, Function>;
		}
		struct S_Function_Data<T_Dedicated_Point*&, T_Fn_Parts...> :
			S_Function_Data<T_Fn_Parts...>
		{
			using pointer = T_Dedicated_Point;
		};


		//仕様
		//引数の型をセットする
		template<class T_Fn, class ...T_Bind_Args>
		struct S_Function_Data<T_Fn, T_Bind_Args...> :
			S_Function_Data<T_Fn>
		{
			using bind_args = tuple_t<T_Bind_Args...>;
		};


		//仕様
		//クラスメソッドの型から、各種パラメータをセットする
		template<class T_CName, class T_RType, class ...T_Args>
		struct S_Function_Data<T_RType(T_CName::*)(T_Args...)> :
			S_Function_Data<>
		{
			using function = T_RType(T_CName::*)(T_Args...);

			using c_name = T_CName;

			using r_type = T_RType;
		};

		//仕様
		//関数の型から、各種パラメータをセットする
		template<class T_RType, class ...T_Args>
		struct S_Function_Data<T_RType(*)(T_Args...)> :
			S_Function_Data<>
		{
			using function = T_RType(*)(T_Args...);

			using r_type = T_RType;
		};


		//仕様
		//[Function]内の[Function]を[Function_Core]に変更し、
		// 複数の関数を1つずつの[Function_Core]に分別し[tuple_t]で纏め、再度functionの判定を行う
		template<class ...T_Parts>
		struct S_Function_Data<Function<T_Parts...>> :
			S_Function_Data<typename I_Function_Helper<T_Parts...>::type>
		{};


		//仕様
		//[Function]のポインターを外し、
		// 再度、functionの判定を行う
		template<class ...T_Parts>
		struct S_Function_Data<Function<T_Parts...>*> :
			S_Function_Data<Function<T_Parts...>>
		{};

		//仕様
		//[Function]の参照を外し、
		// 再度、functionの判定を行う
		template<class ...T_Parts>
		struct S_Function_Data<Function<T_Parts...>&> :
			S_Function_Data<Function<T_Parts...>>
		{};

		//仕様
		//親となる関数オブジェクトの型をセットする
		template<class ...T_Parts>
		struct S_Function_Data<Function_Core<T_Parts...>> :
			S_Function_Data<>
		{
			using function = Function_Core<T_Parts...>;
		};

		//仕様
		//親となる関数オブジェクトが複数存在する場合、tuple_tで纏めてセットする
		template<class ...T_Fns>
		struct S_Function_Data<tuple_t<T_Fns...>> :
			S_Function_Data<>
		{
			using function = tuple_t<T_Fns...>;
		};

		//仕様
		//親となる関数オブジェクトの型をセットする
		template<class T_Fn>
		struct S_Function_Data<tuple_t<T_Fn>> :
			S_Function_Data<>
		{
			using function = T_Fn;
		};

		//仕様
		//参照が付いている場合、参照を外し再判定を実施する
		template<class T_Fn>
		struct S_Function_Data<T_Fn&> :
			S_Function_Data<T_Fn>
		{};

		//仕様
		//関数オブジェクトの型でない場合、セットしない
		template<class T_Fn>
		struct S_Function_Data<T_Fn> :
			S_Function_Data<>
		{};

	public:

		using type = S_Function_Data<T_Fn_Parts...>;

	protected:

		//仕様
		//[T_Fn_Parts...]を処理した結果の[Function_Core]を出力する
		struct I_Core_Molding
		{
			template<class T_Core, class T_Add>
			struct S_Add_p
			{
				using type = T_Core;
			};

			template<class ...T_Parts, is_invalid_not T_Add>
			struct S_Add_p<Function_Core<T_Parts...>, T_Add>
			{
				using type = Function_Core<T_Add*, T_Parts...>;
			};

			template<class T_Core, class T_Add>
			struct S_Add_fn
			{
				using type = T_Core;
			};

			template<class ...T_Parts, is_invalid_not T_Add>
			struct S_Add_fn<Function_Core<T_Parts...>, T_Add>
			{
				using type = Function_Core<T_Add, T_Parts...>;
			};

			template<class T_Bind_Args = typename type::bind_args>
			struct S_Add_bind_args
			{
				using type = Function_Core<>;
			};

			template<class ...T_Bind_Args >
			struct S_Add_bind_args<tuple_t<T_Bind_Args...>>
			{
				using type = Function_Core<T_Bind_Args...>;
			};

			using type = S_Add_p<typename S_Add_fn<typename S_Add_bind_args<>::type,
				typename type::function>::type, typename type::pointer>::type;

		};

	public:

		using core = I_Core_Molding::type;

	};

}

