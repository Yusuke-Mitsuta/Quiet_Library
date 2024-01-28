#pragma once

#include"iostream"
#include"Tuple_Declare.h"

namespace N_Tuple::N_Apply
{

	template<class T_Expand, size_t t_point>
	struct S_Conversion_Expand;

	template<class T_Zip, size_t t_point>
	struct S_Conversion_Zip;

	template<class T_Request_Types_Tuple,
		class T_Set_Types_Tuple>
	struct I_Apply_Type_Chack;
	
	
	template<
		class T_Request_Types_Tuple,
		class T_Args_Types_Tuple>
	struct I_Args_Convert_Action
	{
		
		using conversion = I_Apply_Type_Chack<T_Request_Types_Tuple, T_Args_Types_Tuple>::type;

		using conversion_expand_list = conversion::conversion_expand_list;

		using conversion_zip_list = conversion::conversion_zip_list;

		//仕様
		//互換性のある型に展開する
		// [using tuple}にて定義される型
		template<class T_Tuple>
		using expand = N_Tuple::S_Parameter<T_Tuple>::tuple;


		//仕様
		//選択中のタイプを展開する
		template<class T_Types_Tuple>
		using select_type_expand = N_Tuple::U_Insert_tuple_expand<
			typename T_Types_Tuple::remove,
			U_Reverse<expand<typename T_Types_Tuple::type>>>;


		template<class T_Args_Expand_Order_List= conversion_expand_list,
			class T_Args_Types_list = T_Args_Types_Tuple >
		struct I_Args_Expand_Optimization
		{
			using convert_order=T_Args_Expand_Order_List::type;

			using expand_type_select = U_Select<T_Args_Types_list::size - convert_order::value - 1, T_Args_Types_list>;

			template<class T_expand_Numbers = U_index_sequence<S_Parameter<typename convert_order::type>::tuple::size>,
				class T_Expand_Type_Select = expand_type_select>
			struct S_Args_Expand_Optimization;

			template<
				size_t... t_Expand_Number ,
				class ...T_Flont_Args_Types,class T_Args, class ...T_Back_Args_Types>
			struct S_Args_Expand_Optimization<
				tuple_v<t_Expand_Number...>,
				tuple_tp<tuple_t<T_Flont_Args_Types...>, T_Args, tuple_t<T_Back_Args_Types...>> >
			{
				using type = I_Args_Expand_Optimization<
					typename T_Args_Expand_Order_List::remove,
					select_type_expand<expand_type_select> >::type;

				template<size_t t_select_number>
				using select_type = N_Tuple::U_Element_t<t_select_number, expand>;

				//仕様
				//[change_args]の[t_select_number]番目の変数を取得する
				template<size_t t_select_number>
				static constexpr auto get(T_Args change_args)
				{
					return std::get<t_select_number>(change_args);
				}

				//仕様
				//[change_args]の[t_select_number]番目の変数を参照で取得する
				template<size_t t_select_number>
					requires is_reference<select_type<t_select_number>>
				static constexpr auto& get(T_Args change_args)
				{
					return std::get<t_select_number>(change_args);
				}

				//仕様
				//[change_args]の[t_select_number]番目の変数をポインターで取得する
				template<size_t t_select_number>
					requires is_pointer<select_type<t_select_number>>
				static constexpr auto* get(T_Args change_args)
				{
					return &std::get<t_select_number>(change_args);
				}

				static constexpr auto Apply(auto* fn,
					T_Flont_Args_Types&&... front_args,
					T_Args&& args,
					T_Back_Args_Types&&...back_args)
				{
					return type::Apply(fn,
						std::forward<T_Flont_Args_Types>(front_args)...,
						get<t_Expand_Number>(args)...,
						std::forward<T_Back_Args_Types>(back_args)...);
				}


			};

			using type = S_Args_Expand_Optimization<>;

		};

		template<class T_Args_Types_list>
		struct I_Args_Expand_Optimization<tuple_t<>, T_Args_Types_list>
		{

		};

		template<class T_Args_Zip_Order_List = conversion_zip_list,
				 class T_Args_Types_list >
		struct I_Args_Zip
		{
			using zip_order = T_Args_Zip_Order_List::type;

			template<
				size_t t_order_number,
				size_t t_zip_range,
				size_t t_break_point>
			struct S_Zip_Order_Part_Division
			{
				//static constexpr size_t zip_size = zip_order::value;
			};



















		};


	};

	

}