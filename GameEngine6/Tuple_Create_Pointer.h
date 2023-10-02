#pragma once

#include"Tuple_Class_Declare.h"

namespace N_Tuple
{

	template<class T_Tuple_p>
	struct I_Create_Pointer
	{
	private:

		template<class T_Tuple>
		struct S_Create_Pointer
		{
			using type = T_Tuple;
		};

		template<class T_Flont_Type,class ...T_Types>
		struct S_Create_Pointer<tuple_t<T_Flont_Type,T_Types...>>
		{
			using type= tuple_tp<tuple_t<>,T_Flont_Type, tuple_t<T_Types...>>;
		};

		template<>
		struct S_Create_Pointer<tuple_t<>>
		{
			using type = tuple_tp<tuple_t<>, invalid_t, tuple_t<>>;
		};

		template<auto t_Flont_value, auto ...t_value>
		struct S_Create_Pointer<tuple_v<t_Flont_value,t_value...>>
		{
			using type = tuple_vp<tuple_v<>,t_Flont_value, tuple_v<t_value...>>;
		};

		template<>
		struct S_Create_Pointer<tuple_v<>>
		{
			using type = tuple_vp<tuple_v<>,invalid, tuple_v<>>;
		};


	public:

		using type = S_Create_Pointer<T_Tuple_p>::type;

	};

}
