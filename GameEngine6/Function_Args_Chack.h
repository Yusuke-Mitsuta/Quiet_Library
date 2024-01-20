#pragma once

#include"Tuple.h"
#include"Expand.h"

namespace N_Function
{


	template<class T_Request_Args, class T_Bind_Args>
	struct I_Function_Args_Chack
	{
		using type = invalid_t;
	};
	
	//仕様
	//[T_Request_Args]と[T_Bind_Args]を後ろから比較し、
	//　互換性のある型か判定する。
	//
	// テンプレート
	// [T_Request_Args]：要求する引数の型(tuple_tp)
	// [T_Bind_Args]：セットする引数の型(tuple_t)
	// 
	//補足
	// 互換性のある型の定義は、[N_Tuple::S_Parameter]の特殊化にて定義を行う
	//
	template<class T_Request_Args, class T_Bind_Args>
		requires requires
	{
		requires N_Tuple::is_Tuple_t<T_Request_Args>;
		requires N_Tuple::is_Tuple_t<T_Bind_Args>;
	}
	struct I_Function_Args_Chack<T_Request_Args,T_Bind_Args>
	{
	private:


		template<class T_Request_Args_Tuple,
			class T_Bind_Args_Tuple,
			bool t_constructible_from,
			bool t_Bind_Args_Expand,
			class ...T_Bind_Args>
		struct S_Function_Args_Chack;

		//仕様
		// [T_Bind_Args]が[invalid_t]のみで、[T_Bind_Args_Tuple]が最後まで判定しきると、
		//判定成功とする
		template<class T_Request_Args_Tuple,
			class T_Bind_Args_Tuple,
			class ...T_Bind_Args>
		using U_Function_Args_Chack_Next =
			S_Function_Args_Chack<T_Request_Args_Tuple, T_Bind_Args_Tuple,
			std::constructible_from<std::remove_reference_t<typename T_Request_Args_Tuple::type>, typename T_Bind_Args_Tuple::type, T_Bind_Args...> ||
			std::constructible_from<std::remove_pointer_t<typename T_Request_Args_Tuple::type>, typename T_Bind_Args_Tuple::type, T_Bind_Args...> ,
			is_invalid_not<typename N_Tuple::S_Parameter<typename T_Bind_Args_Tuple::type>::tuple>,
			typename T_Bind_Args_Tuple::type, T_Bind_Args...>::type;

		template<class T_Request_Args_Tuple,
			class T_Bind_Args_Tuple,
			class ...T_Bind_Args>
		using U_Function_Args_Chack_Next1 =
			S_Function_Args_Chack<T_Request_Args_Tuple, T_Bind_Args_Tuple,
			std::constructible_from<std::remove_reference_t<typename T_Request_Args_Tuple::type>, typename T_Bind_Args_Tuple::type, T_Bind_Args...> ||
			std::constructible_from<std::remove_pointer_t<typename T_Request_Args_Tuple::type>, typename T_Bind_Args_Tuple::type, T_Bind_Args...>,
			is_invalid_not<typename N_Tuple::S_Parameter<typename T_Bind_Args_Tuple::type>::tuple>,
			typename T_Bind_Args_Tuple::type, T_Bind_Args...>;


		template<class T_Request_Args_Tuple,
			class T_Bind_Args_Tuple,
			bool t_constructible_from,
			bool t_Bind_Args_Expand>
			requires (is_invalid<typename T_Bind_Args_Tuple::type>)
		struct S_Function_Args_Chack<T_Request_Args_Tuple, T_Bind_Args_Tuple, t_constructible_from, t_Bind_Args_Expand, invalid_t>
		{
			using type = T_Request_Args_Tuple::reverse;
		};

		//仕様
		// [T_Bind_Args]が残っている状態で[T_Bind_Args_Tuple]が最後まで判定しきると、
		//判定失敗とする
		template<class T_Request_Args_Tuple,
			class T_Bind_Args_Tuple,
			bool t_constructible_from,
			bool t_Bind_Args_Expand,
			class ...T_Bind_Args>
		requires requires
		{
			requires is_invalid<typename T_Bind_Args_Tuple::type>;
			requires (sizeof...(T_Bind_Args) > 0);
		}
		struct S_Function_Args_Chack<T_Request_Args_Tuple, T_Bind_Args_Tuple, t_constructible_from, t_Bind_Args_Expand, invalid_t,T_Bind_Args...>
		{
			using type = invalid_t;
		};


		//仕様
		//要求する引数の型に対して、[T_Bind_Args...]の型で生成でき無い場合の動作
		// [T_Bind_Args...]を引継ぎ、[T_Bind_Args_Tuple]を次に進める
		//
		//補足
		//[U_Function_Args_Chack_Next]内で、引継いだ[T_Bind_Args...]に対して、
		// [T_Bind_Args_Tuple]を次に進めた際の選択中の型を追加する。
		template<class T_Request_Args_Tuple,
			class T_Bind_Args_Tuple,
			class ...T_Bind_Args>
		requires requires
		{
			requires is_invalid_not<typename T_Bind_Args_Tuple::type>;
		}
		struct S_Function_Args_Chack<T_Request_Args_Tuple, T_Bind_Args_Tuple, false, false, T_Bind_Args...>
		{
			using type = U_Function_Args_Chack_Next<T_Request_Args_Tuple,
				typename T_Bind_Args_Tuple::next,T_Bind_Args...>;
		};

		//仕様
		//要求する引数の型に対して、[T_Bind_Args...]の型で生成できる場合の動作
		// [T_Bind_Args...]をリセットし、[T_Request_Args_Tuple][T_Bind_Args_Tuple]を次の判定に進める、
		template<class T_Request_Args_Tuple,
			class T_Bind_Args_Tuple,
			bool t_Bind_Args_Expand,
			class ...T_Bind_Args>
			requires requires
		{
			requires is_invalid_not<typename T_Bind_Args_Tuple::type>;
		}
		struct S_Function_Args_Chack<T_Request_Args_Tuple,T_Bind_Args_Tuple,true,t_Bind_Args_Expand,T_Bind_Args...>
		{

			template<class T = typename S_Function_Args_Chack<T_Request_Args_Tuple, T_Bind_Args_Tuple, false, t_Bind_Args_Expand,
				T_Bind_Args...>::type>
			struct S_last_args_chack
			{
				using type = typename S_Function_Args_Chack<T_Request_Args_Tuple, T_Bind_Args_Tuple, false, t_Bind_Args_Expand,
					T_Bind_Args...>::type;
			};

			template<>
			struct S_last_args_chack<invalid_t>
			{
				using type = U_Function_Args_Chack_Next<
					typename T_Request_Args_Tuple::next,
					typename T_Bind_Args_Tuple::next>;

				using type3 = U_Function_Args_Chack_Next1<
					typename T_Request_Args_Tuple::next,
					typename T_Bind_Args_Tuple::next>;
			};

			using type = S_last_args_chack<>::type;
			using type2 = S_last_args_chack<>;

		};

		//仕様
		//互換性のある型の定義がされている場合、その形に変換を実施する
		// 
		//補足
		// 互換性のある型の定義は、[N_Tuple::S_Parameter]の特殊化にて定義を行う
		template<class T_Request_Args_Tuple,
			class T_Bind_Args_Tuple,
			class T_Front_Bind_Args,
			class ...T_Bind_Args>
		requires requires
		{
			requires is_invalid_not<typename T_Bind_Args_Tuple::type>;
		}
		struct S_Function_Args_Chack<T_Request_Args_Tuple,T_Bind_Args_Tuple,false, true, T_Front_Bind_Args,T_Bind_Args...>
		{
			using convert = N_Tuple::S_Parameter<T_Front_Bind_Args>::tuple;
		
			using insert_bind_args = N_Tuple::U_Insert_tuple_expand<typename T_Bind_Args_Tuple::remove, convert>;
		
			using type = U_Function_Args_Chack_Next<T_Request_Args_Tuple, insert_bind_args, T_Bind_Args...>;
		};

	public:

		using type =U_Function_Args_Chack_Next<typename T_Request_Args::reverse,
			typename T_Bind_Args::reverse>;

		using type1 = U_Function_Args_Chack_Next1<typename T_Request_Args::reverse,
			typename T_Bind_Args::reverse>;
	};

}
