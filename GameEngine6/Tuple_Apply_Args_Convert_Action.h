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

		template<class T_Args_Convert_Order_List, class T_Args_Types_list = T_Args_Types_Tuple>
		struct I_Args_Conversion_Expand_Optimization
		{
			template<class T_Args_Convert_Order=typename T_Args_Convert_Order_List::type, 
				class T_Expand_Number=U_index_sequence<T_Args_Convert_Order
				class T_Args_Types_list = U_Select<T_Args_Types_list::size-T_Args_Convert_Order::value-1,T_Args_Types_list>>
			struct S_Args_Conversion_Expand_Optimization
			{

			};

			template<class T_Expand, size_t t_Expand_Numeber,
				class ...T_Flont_Args_Types,class T_Args, class ...T_Back_Args_Types>
			struct S_Args_Conversion_Expand_Optimization<
				S_Conversion_Expand<T_Expand, t_Expand_Numeber>,
				tuple_tp<tuple_t<T_Flont_Args_Types...>,T_Args,tuple_t<T_Back_Args_Types...>> >
			{


				static constexpr auto Apply(auto* fn,
					T_Flont_Args_Types&&... front_args,
					T_Args&& args,
					T_Back_Args_Types&&...back_args)
				{
					return type::Apply(fn,
						std::forward<T_Flont_Args_Types>(front_args)...,
						
						)
				}
			};


		};

		template<>
		struct I_Args_Conversion_Expand_Optimization<tuple_t<>>
		{
		};



		template<class T_Expand, size_t t_Expand_Numeber, class... T_Args_Convert_Orders>
		struct I_Args_Conversion_Expand_Optimization<tuple_t<S_Conversion_Expand<T_Expand, t_Expand_Numeber>, T_Args_Convert_Orders...>>
		{




			static constexpr auto Apply(auto* fn,)


		};



	};

	

}