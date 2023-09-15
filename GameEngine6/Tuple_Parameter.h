#pragma once

#include<tuple>
#include<optional>

#include"Tuple_Class_Declare.h"

namespace N_Tuple
{

	//仕様
	//[Tuple_t]の各種Size、及び型を呼び出す
	template<class ...T_Types>
	struct S_Parameter
	{
		using T = std::tuple<T_Types...>;
		static constexpr size_t Size = sizeof...(T_Types);
	};

	template<class ...T_Head_Types, class T, class ...T_Tail_Types>
	struct S_Parameter<Tuple_tp<_Head<T_Head_Types...>,T , _Tail<T_Tail_Types...>>>
	{
		static constexpr size_t Size_Head = sizeof...(T_Head_Types);
		static constexpr size_t Size_Tail = sizeof...(T_Tail_Types);
		static constexpr size_t Size = Size_Head + Size_Tail + not_is_nullopt<T>;
		using Type = T;
	};

	template<auto ...t_Head_Value, auto _Value, auto ...t_Tail_Value>
	struct S_Parameter<Tuple_vp<_Head_v<t_Head_Value...>, _Value, _Tail_v<t_Tail_Value...>>>
	{
		static constexpr size_t Size_Head = sizeof...(t_Head_Value);
		static constexpr size_t Size_Tail = sizeof...(t_Tail_Value);
		static constexpr size_t Size = Size_Head + Size_Tail + not_is_nullopt<decltype(_Value)>;
		static constexpr auto value = _Value;
	};

}
