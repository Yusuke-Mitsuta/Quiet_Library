#pragma once

#include<tuple>
#include<optional>

#include"Tuple_Class_Declare.h"

namespace N_Tuple
{

	//仕様
	//[tuple_t]の各種Size、及び型を呼び出す
	template<class ...T_Types>
	struct S_Parameter
	{
		static constexpr size_t head_size = 0;
		static constexpr size_t tail_size = 0;
		static constexpr size_t size = sizeof...(T_Types);
		static constexpr int select = -1;

		using type = invalid_t;

		static constexpr invalid_t value = invalid;

		using head = tuple_t<>;
		using tail = tuple_t<>;

		static constexpr E_Tuple_ID ID = E_Tuple_ID::NONE;
	};

	template<class ...T>
	struct S_Parameter<tuple_t<T...>>
	{
		static constexpr size_t head_size = 0;
		static constexpr size_t tail_size = 0;
		static constexpr size_t size = sizeof...(T);
		static constexpr int select = 0;

		template<class ...T>
		struct S_Parameter_tuple_t
		{
			using type = invalid_t;
			using tail = tuple_t<>;
		};

		template<class T_Front, class ...T>
		struct S_Parameter_tuple_t<T_Front,T...>
		{
			using type = T_Front;
			using tail = tuple_t<T...>;
		};

		using type = S_Parameter_tuple_t<T...>::type;

		using head = tuple_t<>;
		using tail = S_Parameter_tuple_t<T...>::tail;

		static constexpr E_Tuple_ID ID = E_Tuple_ID::TUPLE_T;

	};


	template<auto ...t_value>
	struct S_Parameter<tuple_v<t_value...>>
	{

		static constexpr size_t head_size = 0;
		static constexpr size_t tail_size = 0;
		static constexpr size_t size = sizeof...(t_value);
		static constexpr int select = 0;

		template<auto ...t_value>
		struct S_Parameter_tuple_v
		{
			static constexpr auto value = invalid;
			using tail = tuple_v<>;
		};

		template<auto t_front_value,auto ...t_value>
		struct S_Parameter_tuple_v<t_front_value,t_value...>
		{
			static constexpr auto value = t_front_value;
			using tail = tuple_v<t_value...>;
		};

		static constexpr auto value = S_Parameter_tuple_v<t_value...>::value;

		using head = tuple_v<>;
		using tail = S_Parameter_tuple_v<t_value...>::tail;

		static constexpr E_Tuple_ID ID = E_Tuple_ID::TUPLE_V;
	};



	template<class ...T_Head_Types, class T, class ...T_Tail_Types>
	struct S_Parameter<tuple_tp<tuple_t<T_Head_Types...>, T, tuple_t<T_Tail_Types...>>>
	{
		static constexpr size_t head_size = sizeof...(T_Head_Types);
		static constexpr size_t tail_size = sizeof...(T_Tail_Types);
		static constexpr size_t size = head_size + tail_size + not_is_invalid<T>;

		//static constexpr int select = head_size - static_cast<bool>(tail_size == size);

		using type = T;

		using head = tuple_t<T_Head_Types...>;
		using tail = tuple_t<T_Tail_Types...>;

		static constexpr E_Tuple_ID ID = E_Tuple_ID::TUPLE_TP;
	};



	template<auto ...t_Head_Value, auto t_value, auto ...t_Tail_Value>
	struct S_Parameter<tuple_vp<tuple_v<t_Head_Value...>, t_value, tuple_v<t_Tail_Value...>>>
	{

		static constexpr size_t head_size = sizeof...(t_Head_Value);
		static constexpr size_t tail_size = sizeof...(t_Tail_Value);
		static constexpr size_t size = head_size + tail_size + not_is_invalid<decltype(t_value)>;

		//static constexpr int select = head_size - static_cast<bool>(tail_size == size);

		static constexpr auto value = t_value;

		using head = tuple_v<t_Head_Value...>;
		using tail = tuple_v<t_Tail_Value...>;


		static constexpr E_Tuple_ID ID = E_Tuple_ID::TUPLE_VP;
	};



}
