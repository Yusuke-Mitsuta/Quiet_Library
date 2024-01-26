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
	struct S_Conversion_Expand
	{

	};

	template<class T_Zip, size_t t_point>
	struct S_Conversion_Zip
	{

	};

	template<class T_Request_Types_Tuple,
		class T_Set_Types_Tuple>
	struct I_Apply_Type_Chack
	{


		//仕様
		//型の判定が終了する際に呼び出される
		template<class T_Request_Types_Tuple = invalid_t,
			class T_Conversion_List = invalid_t>
		struct S_Result
		{
			using request = T_Request_Types_Tuple;

			using conversion = T_Conversion_List;

		};


		template<class T_Request_Types_Tuple,
			class T_Set_Types_Tuple,
			//class T_Set_Types_Convert = tuple_t<>,
			class T_Conversion_List = tuple_t<>>
			struct S_Apply_Type_Chack
		{
			using type = S_Result<T_Request_Types_Tuple, T_Conversion_List>;
		};

		template<class T_Request_Types_Tuple,
			class T_Set_Types_Tuple,
			class ...T_Conversion>
			requires requires
		{
			requires is_invalid_not<typename T_Request_Types_Tuple::type>;
			requires is_invalid_not<typename T_Set_Types_Tuple::type>;
		}
		struct S_Apply_Type_Chack< T_Request_Types_Tuple, T_Set_Types_Tuple, tuple_t<T_Conversion...>>
		{
			using request_t = T_Request_Types_Tuple::type;

			using set_t = T_Set_Types_Tuple::type;

			template<class T_Add_cnversion>
			using add_cnversion_list = tuple_t<T_Conversion..., T_Add_cnversion>;

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
				using type = S_Result<T_Request_Types_Tuple, tuple_t<T_Conversion...>>;
			};


			template<bool t_Request_Types_Expand, bool t_Set_Types_Expand>
			struct S_Apply_Control<true,t_Request_Types_Expand,t_Set_Types_Expand>
			{
				using type = S_Apply_Type_Chack<
					typename T_Request_Types_Tuple::next,
					typename T_Set_Types_Tuple::next,
					tuple_t<T_Conversion...>>::type;

				using type5 = S_Apply_Type_Chack<
					typename T_Request_Types_Tuple::next,
					typename T_Set_Types_Tuple::next,
					tuple_t<T_Conversion...>>;
			};


			template<bool t_Request_Types_Expand>
			struct S_Apply_Control<false, t_Request_Types_Expand, true>
			{

				using type = S_Apply_Type_Chack<
					T_Request_Types_Tuple,
					select_type_expand<T_Set_Types_Tuple>,
					add_cnversion_list<S_Conversion_Expand<set_t,T_Set_Types_Tuple::head_size>>
					>::type;

				using type3 = S_Apply_Type_Chack<
					T_Request_Types_Tuple,
					select_type_expand<T_Set_Types_Tuple>,
					add_cnversion_list<S_Conversion_Expand<set_t, T_Set_Types_Tuple::head_size>>
				>;
				/*

				template<class T_Unconverted = typename T_Set_Types_Tuple::tail::reverse,
					class T_Converting = set_t>
				struct S_Convert
				{
					using convert = next::convert;

				};

				template<class ...T_Unconverted, class T_Converting>
				struct S_Convert<tuple_t<T_Unconverted...>, T_Converting>
				{
					using convert = S_Convert;


					template<class ...T_Convert>
					static constexpr auto Apply(auto* fn,
						T_Unconverted&&... unconverted_args,
						T_Converting&& converting_args,
						T_Convert&&... convert_args)
					{
						next::

					}

				};
				*/

			};


			template<>
			struct S_Apply_Control<false, true, false>
			{
				using type =
					S_Apply_Type_Chack <
					select_type_expand<T_Request_Types_Tuple>,
					T_Set_Types_Tuple,
					add_cnversion_list<S_Conversion_Zip<request_t, T_Request_Types_Tuple::head_size>>
					>::type;

				using type4 =

					S_Apply_Type_Chack<
					select_type_expand<T_Request_Types_Tuple>,
					T_Set_Types_Tuple,
					add_cnversion_list<S_Conversion_Zip<request_t, T_Set_Types_Tuple::head_size>>
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

		using conversion = type::conversion;

	};


}
