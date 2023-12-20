#pragma once

#include<tuple>
#include<optional>

#include"Tuple_Class_Declare.h"

namespace N_Tuple
{

	//�d�l
	//[tuple_t]�̊e��size�A�y�ь^���Ăяo��
	template<class ...T_Types>
	struct S_Parameter
	{
		using T = std::tuple<T_Types...>;
		static constexpr size_t head_size = 0;
		static constexpr size_t tail_size = 0;
		static constexpr size_t size = sizeof...(T_Types);

	};

	template<class ...T_Types>
	struct S_Parameter<tuple_t<T_Types...>>
	{
		static constexpr size_t head_size = 0;
		static constexpr size_t tail_size = 0;
		static constexpr size_t size = sizeof...(T_Types);

		static constexpr E_Tuple_ID ID = E_Tuple_ID::TUPLE_T;
	};

	template<auto ...t_Value>
	struct S_Parameter<tuple_v<t_Value...>>
	{
		static constexpr size_t head_size = 0;
		static constexpr size_t tail_size = 0;
		static constexpr size_t size = sizeof...(t_Value);

		static constexpr E_Tuple_ID ID = E_Tuple_ID::TUPLE_V;
	};

	template<class ...T_Head_Types, class T, class ...T_Tail_Types>
	struct S_Parameter<tuple_tp<tuple_t<T_Head_Types...>,T , tuple_t<T_Tail_Types...>>>
	{
		static constexpr size_t head_size = sizeof...(T_Head_Types);
		static constexpr size_t tail_size = sizeof...(T_Tail_Types);
		static constexpr size_t size = head_size + tail_size + not_is_invalid<T>;

		using type = T;

		static constexpr E_Tuple_ID ID = E_Tuple_ID::TUPLE_TP;
	};

	template<auto ...t_Head_Value, auto _Value, auto ...t_Tail_Value>
	struct S_Parameter<tuple_vp<tuple_v<t_Head_Value...>, _Value, tuple_v<t_Tail_Value...>>>
	{
		static constexpr size_t head_size = sizeof...(t_Head_Value);
		static constexpr size_t tail_size = sizeof...(t_Tail_Value);
		static constexpr size_t size = head_size + tail_size + not_is_invalid<decltype(_Value)>;
		static constexpr auto value = _Value;

		static constexpr E_Tuple_ID ID = E_Tuple_ID::TUPLE_VP;
	};



}
