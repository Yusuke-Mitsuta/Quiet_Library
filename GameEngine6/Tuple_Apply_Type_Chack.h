#pragma once

#include"Tuple_Declare.h"
#include"Tuple_Apply_Type.h"
#include"Tuple_Apply_Fn.h"
#include"Tuple_Apply_Array_Set.h"
#include"Tuple_Apply_Request.h"
#include"Tuple_Apply_Class_Create.h"


namespace N_Tuple::N_Apply
{


	template<class T_Expand, size_t t_point>
	struct S_Conversion_Expand:

		integral_constant<t_point>
	{
		using type = T_Expand;
	};

	template<class T_Zip, size_t t_point>
	struct S_Conversion_Zip:
		integral_constant<t_point>
	{
		using type = T_Zip;
	};

	template<class T_Request_Types_Tuple,
		class T_Set_Types_Tuple>
	struct I_Apply_Type_Chack
	{


		//仕様
		//型の判定が終了する際に呼び出される
		template<class T_Request_Types_Tuple = invalid_t,
			class T_Conversion_Expand_List = tuple_t<>,
			class T_Conversion_Zip_List = tuple_t<>>
		struct S_Result
		{
			using request = T_Request_Types_Tuple;

			using conversion_expand_list = T_Conversion_Expand_List;

			using conversion_zip_list = T_Conversion_Zip_List;

		};


		template<class T_Request_Types_Tuple,
			class T_Set_Types_Tuple,
			//class T_Set_Types_Convert = tuple_t<>,
			class T_Conversion_Expand_List = tuple_t<>,
			class T_Conversion_Zip_List=tuple_t<>
		>
			struct S_Apply_Type_Chack
		{
			using type = S_Result<T_Request_Types_Tuple, T_Conversion_Expand_List, T_Conversion_Zip_List>;
		};

		template<class T_Request_Types_Tuple,
			class T_Set_Types_Tuple,
			class ...T_Conversion_Expand,
			class ...T_Conversion_Zip>
			requires requires
		{
			requires is_invalid_not<typename T_Request_Types_Tuple::type>;
			requires is_invalid_not<typename T_Set_Types_Tuple::type>;
		}
		struct S_Apply_Type_Chack< T_Request_Types_Tuple, T_Set_Types_Tuple, 
			tuple_t<T_Conversion_Expand...>,
			tuple_t<T_Conversion_Zip...>>
		{
			using request_t = T_Request_Types_Tuple::type;

			using set_t = T_Set_Types_Tuple::type;

			template<class ...T_Add>
			using expand_list = tuple_t<T_Conversion_Expand...,T_Add...>;

			template<class ...T_Add>
			using zip_list = tuple_t<T_Conversion_Zip..., T_Add...>;

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

			template<bool t_constructible_from=convertible_to<set_t,request_t>,
				bool t_Request_Types_Expand = is_invalid_not<expand<request_t>>,
				bool t_Set_Types_Expand= is_invalid_not<expand<set_t>> >
			struct S_Apply_Control
			{
				using type = S_Result<T_Request_Types_Tuple, expand_list<>, zip_list<>>;
			};


			template<bool t_Request_Types_Expand, bool t_Set_Types_Expand>
			struct S_Apply_Control<true,t_Request_Types_Expand,t_Set_Types_Expand>
			{
				using type = S_Apply_Type_Chack<
					typename T_Request_Types_Tuple::next,
					typename T_Set_Types_Tuple::next,
					expand_list<>,zip_list<>>::type;

				using type5 = S_Apply_Type_Chack<
					typename T_Request_Types_Tuple::next,
					typename T_Set_Types_Tuple::next,
					expand_list<>, zip_list<>>;
			};


			template<bool t_Request_Types_Expand>
			struct S_Apply_Control<false, t_Request_Types_Expand, true>
			{

				using type = S_Apply_Type_Chack<
					T_Request_Types_Tuple,
					select_type_expand<T_Set_Types_Tuple>,
					expand_list<S_Conversion_Expand<set_t,T_Set_Types_Tuple::head_size>>,
					zip_list<>
					>::type;

				using type3 = S_Apply_Type_Chack<
					T_Request_Types_Tuple,
					select_type_expand<T_Set_Types_Tuple>, 
					expand_list<S_Conversion_Expand<set_t, T_Set_Types_Tuple::head_size>>,
					zip_list<>
					>;


			};


			template<>
			struct S_Apply_Control<false, true, false>
			{
				using type =
					S_Apply_Type_Chack <
					select_type_expand<T_Request_Types_Tuple>,
					T_Set_Types_Tuple,
					expand_list<>,
					zip_list<S_Conversion_Zip<request_t, T_Request_Types_Tuple::head_size>>
					>::type;

				using type4 =
					S_Apply_Type_Chack<
					select_type_expand<T_Request_Types_Tuple>,
					T_Set_Types_Tuple,
					expand_list<>,
					zip_list<S_Conversion_Zip<request_t, T_Request_Types_Tuple::head_size>>
					>;
			};

			using type = S_Apply_Control<>::type;

			using type2 = S_Apply_Control<>;

		};


		using type = S_Apply_Type_Chack<
			typename T_Request_Types_Tuple::reverse,
			typename T_Set_Types_Tuple::reverse::create_p>::type;


		using type1 = S_Apply_Type_Chack<
			typename T_Request_Types_Tuple::reverse,
			typename T_Set_Types_Tuple::reverse::create_p>;

		using conversion = type;

	};


}
