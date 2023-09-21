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
		struct S_Create_Pointer<Tuple_t<T_Flont_Type,T_Types...>>
		{
			using type= Tuple_tp<Head_t<>,T_Flont_Type, Tail_t<T_Types...>>;
		};

		template<>
		struct S_Create_Pointer<Tuple_t<>>
		{
			using type = Tuple_tp<Head_t<>, std::nullopt_t, Tail_t<>>;
		};

		template<auto t_Flont_value, auto ...t_value>
		struct S_Create_Pointer<Tuple_v<t_Flont_value,t_value...>>
		{
			using type = Tuple_vp<Head_v<>,t_Flont_value, Tail_v<t_value...>>;
		};

		template<>
		struct S_Create_Pointer<Tuple_v<>>
		{
			using type = Tuple_vp<Head_v<>,std::nullopt, Tail_v<>>;
		};


	public:

		using Type = S_Create_Pointer<T_Tuple_p>::type;

	};

}
