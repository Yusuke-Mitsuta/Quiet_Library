#pragma once

#include"Tuple_Declare.h"
#include"Tuple_Apply_Type.h"
#include"Tuple_Apply_Fn.h"
#include"Tuple_Apply_Array_Set.h"
#include"Tuple_Apply_Request.h"
#include"Tuple_Apply_Class_Create.h"
#include"Tuple_Infinite.h"
#include"If_Type.h"

namespace N_Tuple::N_Apply
{

	template<class T_Expand, size_t t_point>
	struct S_Conversion_Expand;

	template<class T_Zip, size_t t_point>
	struct S_Conversion_Zip;

	template<class T_Request_Types_Tuple,
		class T_Set_Types_Tuple>
	struct I_Type_Chack
	{

		using request_expand = U_Expand_All<T_Request_Types_Tuple>;

		using set_expand = U_Expand_All<T_Set_Types_Tuple>;
		

		template<class T_Expand_Number =
			U_index_sequence<
			request_expand::size - is_Infinite_Args<typename T_Request_Types_Tuple::back_t>>
		struct S_Type_Chack
		{

		};



		template<size_t ...t_Expand_Number>
			requires requires
		{
			requires convertible_to<
				U_Element_t<t_Expand_Number, set_expand>,
				U_Element_t<t_Expand_Number, request_expand>> && ...;

			requires request_expand::size == sizeof...(t_Expand_Number);
		}
		struct S_Type_Chack
		{
			using type = std::true_type;
		};

		template<size_t ...t_Expand_Number>
			requires requires
		{
			requires convertible_to<
				U_Element_t<t_Expand_Number, set_expand>,
				U_Element_t<t_Expand_Number, request_expand>> && ...;

			requires request_expand::size != sizeof...(t_Expand_Number);
		}
		struct S_Type_Chack
		{
			using infinite_args_expand = U_Expand_All<typename T_Request_Types_Tuple::back_t::type>;
			using set_expand_rest = U_Range<set_expand, sizeof...(t_Expand_Number), set_expand::size>;

			template<
				class T_Infinite_Args_Expand_Number = U_index_sequence<infinite_args_expand::size>>
				struct S_Infinite_Args_Chack
			{

			};

			template<size_t ...t_Infinite_Args_Expand_Number>
				requires requires
			{
				requires convertible_to<
					U_Element_t<t_Infinite_Args_Expand_Number, set_expand_rest>,
					U_Element_t<t_Infinite_Args_Expand_Number% infinite_args_expand::size, infinite_args_expand>> &&...;
			}
			struct S_Infinite_Args_Chack<tuple_v<t_Infinite_Args_Expand_Number...>>
			{
				using type = S_Infinite_Args_Chack<
					tuple_v<(infinite_args_expand::size + t_Infinite_Args_Expand_Number)...>>::type;

			};

			template<class T_Infinite_Args_Expand_Number>
				requires requires
			{
				requires T_Infinite_Args_Expand_Number::front_v == set_expand_rest::size;
			}
			struct S_Infinite_Args_Chack<T_Infinite_Args_Expand_Number>
			{
				using type = std::true_type;

			};


			using type = S_Infinite_Args_Chack<>::type;

		};


	}

	//仕様
	//供給する型のリストから、要求する型のリストに、型の展開を伴い変換を出来るか判定する。
	//
	//補足
	// 型の判定は後ろから実施する。
	//template<class T_Request_Types_Tuple,
	//	class T_Set_Types_Tuple>
	//struct I_Apply_Type_Chack
	//{



	//	using conversion = type;

	//};



}