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
	/*
	
	template<
		class T_Request_Types_Tuple,
		class T_Args_Types_Tuple,
		class T_Args_Convert_Order_List =
		typename I_Apply_Type_Chack<T_Request_Types_Tuple, T_Args_Types_Tuple>::conversion>
	struct I_Args_Convert_Action
	{
		
		template<class T_Args_Convert_Order_List,>
		struct S_Args_Convert_Optimization
		{

		};


		template<class T_Expand, size_t t_Expand_Numeber, class... T_Args_Convert_Orders>
		struct S_Args_Convert_Optimization<tuple_t<S_Conversion_Expand<T_Expand, t_Expand_Numeber>, T_Args_Convert_Orders...>>
		{

		};

		template<class T_Expand,size_t t_Expand_Numeber,convertible_from<T_Expand> T_Zip,class... T_Args_Convert_Orders>
		struct S_Args_Convert_Optimization<tuple_t<S_Conversion_Expand<T_Expand ,t_Expand_Numeber>,S_Conversion_Zip<T_Zip,t_Expand_Numeber>, T_Args_Convert_Orders...>>
		{
			using type = S_Args_Convert_Optimization<tuple_t<T_Args_Convert_Orders...>>::type;
		};


		template<class T_Zip, size_t t_Zip_Numeber, class... T_Args_Convert_Orders>
		struct S_Args_Convert_Optimization<tuple_t<S_Conversion_Zip<T_Zip, t_Zip_Numeber>, T_Args_Convert_Orders...>>
		{
			template<class T_Result, class... T_Args_Convert_Orders>
			struct S_Conversion_Zip_Sort
			{
				
			};

			template<class T_Result, class... T_Args_Convert_Orders>
			struct S_Conversion_Zip_Sort
			{

			};



			using type = S_Args_Convert_Optimization<tuple_t<T_Args_Convert_Orders...>>::type;
		};


		//// size_t ...t_Unconverted_Args_Nunmber, c
		//using next = S_Args_Convert_Action
		//
		//	template<class ...T_Converted>
		//static constexpr auto Apply(auto* fn, U_Element_t<t_Unconverted_Args_Nunmber, T_Request_Types_Tuple>&&... unconverted_Args,
		//	T_Expand&& conevrting_args, T_Converted&&... converted_args > )
		//{
		//
		//
		//
		//}
		//
	};

	*/

}