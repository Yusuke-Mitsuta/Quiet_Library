#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{
	//仕様
	//[T_Copy_Base_Tuple_name]の名前を[T_Tuple_name_core]にもコピーする
	template<class T_Tuple_name_core,class T_Copy_Base_Tuple_name>
	struct I_Copy_name
	{
		template<N_Constexpr::String t_copy_name
			 >
		struct S_Copy_name
		{
			using type = tuple_name<t_copy_name,T_Tuple_name_core>;
		};

		template< >
		struct S_Copy_name<"">
		{
			using type = T_Tuple_name_core;
		};


		using type = S_Copy_name<
			S_Parameter<T_Copy_Base_Tuple_name>::name>::type;
	};

}