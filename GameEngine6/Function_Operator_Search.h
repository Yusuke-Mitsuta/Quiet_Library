#pragma once

#include"Tuple.h"
#include"Function_Operator_Helper.h"
#include"Function_Operator_Sort.h"

template<is_invalid_not T_Front_Parts, class ...T_Parts>
class Function;

namespace N_Function
{

	template<class T_Fn,class T_Set_Types>
	struct I_Function_Operator_Search
	{};

	template<class ...T_Parts, class T_Set_Types>
	struct I_Function_Operator_Search<Function<T_Parts...>,T_Set_Types>
	{
	//private:
		using function_operator_data_list = typename I_Function_Operator_Helper<T_Parts...>::type;


		//仕様
		//ポインターを要求する場合、要求する引数の先頭に付け加える。
		template<class T_Operator_data,
			class T_Request_Args = N_Tuple::U_Element_t<1, T_Operator_data>,
			class T_Request_Pointer = N_Tuple::U_Element_t<2, T_Operator_data>>
			struct S_Merge_Pointer
		{
			using type = T_Request_Args;
		};

		template<class T_Operator_data, class ...T_Request_Args, class T_Request_Pointer>
			requires requires
		{
			requires is_invalid_not<T_Request_Pointer>;
		}
		struct S_Merge_Pointer<T_Operator_data, tuple_t<T_Request_Args...>, T_Request_Pointer>
		{
			using type = tuple_t<T_Request_Pointer*, T_Request_Args...>;
		};


		//仕様
		//[operator_data_list]から、[T_Args]と互換性のある引数を要求するデータを取得する
		template<class T_Args, class T_Operator_Parameter = function_operator_data_list>
		struct S_Function_Operator_Search
		{
			using merge_pointer = S_Merge_Pointer<typename T_Operator_Parameter::type>::type::back;

			using args_chack = I_Function_Args_Chack<merge_pointer, T_Args>::type;

			template<bool t_detect_fg = (N_Tuple::S_Size<args_chack>::tail_size == merge_pointer::size)>
			struct S_Next_Search
			{
				using type = I_Function_Operator_Search<T_Args, typename T_Operator_Parameter::remove>::type;
			};

			template<>
			struct S_Next_Search<true>
			{
				using type = T_Operator_Parameter::type;
			};

			using type = S_Next_Search<>::type;
		};


		template<class T_Args, class T_Operator_Parameter>
			requires requires
		{
			requires is_invalid<typename T_Operator_Parameter::type>;
		}
		struct S_Function_Operator_Search<T_Args, T_Operator_Parameter>
		{
			using type = invalid_t;

		};
	public:

		using type = S_Function_Operator_Search<T_Set_Types>::type;
	};

};