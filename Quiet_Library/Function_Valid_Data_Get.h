#pragma once

#include"Tuple.h"

namespace quiet::N_Function
{
	template<class ...T_Parts>
	struct Function_Core;

	template<class ...T_Parts>
	struct I_Function_Superficial_Data;

	//仕様
	//[T_Parts...]から、各種データを生成する
	template<class ...T_Parts>
	struct I_Function_Valid_Data_Get
	{

		using superficial = I_Function_Superficial_Data<T_Parts...>;


		template<class T_Fns=typename superficial::function,
		class T_Request_Args = typename superficial::request_args,
		class T_Request_Pointer=typename superficial::request_pointer
		>
		struct S_Valid_Data_Get
		{
			using type = S_Valid_Data_Get;

			using function = invalid_t;
			using request_args = invalid_t;
			using request_pointer = invalid_t;
		};


		template<class T_Fns, is_invalid_not T_Request_Args, class T_Request_Pointer>
			requires requires
		{
			requires !N_Tuple::is_Tuple_t<T_Fns>;
		}
		struct S_Valid_Data_Get<T_Fns, T_Request_Args, T_Request_Pointer>
		{
			using type = S_Valid_Data_Get;

			using function = T_Fns;
			using request_args = T_Request_Args;
			using request_pointer = T_Request_Pointer;
		};

		template<class T_Fns, class ...T_Request_Args, class T_Request_Pointer>
			requires requires
		{
			requires !N_Tuple::is_Tuple_t<T_Fns>;
			requires is_invalid_nand<T_Request_Args...>;
		}
		struct S_Valid_Data_Get<T_Fns,tuple_t<T_Request_Args...>, T_Request_Pointer>
		{
			using type = S_Valid_Data_Get;

			using function = T_Fns;
			using request_args = tuple_t<T_Request_Args...>;
			using request_pointer = T_Request_Pointer;
		};



		template<class T_Fns, class T_Request_Args, class T_Request_Pointer>
			requires requires
		{
			requires N_Tuple::is_Tuple_t<T_Fns>;
			requires is_invalid_not<typename T_Fns::type>;
			requires is_invalid_not<typename T_Request_Args::type>;
		}
		struct S_Valid_Data_Get<T_Fns,T_Request_Args, T_Request_Pointer>
		{
			using type = S_Valid_Data_Get<
				typename T_Fns::next,
				typename T_Request_Args::next,
				typename T_Request_Pointer::next
			>::type;
		};


		template<class T_Fns, class T_Request_Args,class T_Request_Pointer>
			requires requires
		{
			requires N_Tuple::is_Tuple_t<T_Fns>;
			requires is_invalid_not<typename T_Fns::type>;
			requires is_invalid<typename T_Request_Args::type>;
		}
		struct S_Valid_Data_Get<T_Fns,T_Request_Args,T_Request_Pointer>
		{
			using type = S_Valid_Data_Get<
				typename T_Fns::remove,
				typename T_Request_Args::remove,
				typename T_Request_Pointer::remove
			>::type;
		};

		template<class T_Fns, class T_Request_Args, class T_Request_Pointer>
			requires requires
		{
			requires N_Tuple::is_Tuple_t<T_Fns>;
			requires is_invalid<typename T_Fns::type>;
			requires T_Fns::size > 0;
		}
		struct S_Valid_Data_Get<T_Fns, T_Request_Args, T_Request_Pointer>
		{
			using type = S_Valid_Data_Get;

			using function = T_Fns::remove_p;
			using request_args = T_Request_Args::remove_p;
			using request_pointer = T_Request_Pointer::remove_p;
		};

		using type = S_Valid_Data_Get<>::type;
	};

}
