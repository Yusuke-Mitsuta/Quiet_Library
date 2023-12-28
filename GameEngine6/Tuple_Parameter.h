#pragma once

#include<tuple>
#include<optional>

#include"Tuple_Class_Declare.h"

#include"Tuple_Size.h"
#include"Tuple_ID_Select.h"

namespace N_Tuple
{

	//仕様
	//[tuple_t]の各種Size、及び型を呼び出す
	template<class T_Types>
	struct S_Parameter
	{
		using tuple =invalid_t;
		using type = invalid_t;
		static constexpr invalid_t value = invalid;
		using head = tuple_t<>;
		using tail = tuple_t<>;
	};

	//仕様
	//[tuple_t]の各種Size、及び型を呼び出す
	template<class T_Tuple_t>
	requires requires
	{
		requires S_ID_Select<T_Tuple_t>::ID == E_Tuple_ID::TUPLE_T;
	}
	struct S_Parameter<T_Tuple_t> : 
		S_ID_Select<T_Tuple_t>,
		S_Size<T_Tuple_t>
		
	{
	private:
		using tuple_p_Parameter = S_Parameter<U_Create_p<T_Tuple_t>>;
	public:
		using tuple = T_Tuple_t;
		using type = tuple_p_Parameter::type;
		using head = tuple_p_Parameter::head;
		using tail = tuple_p_Parameter::tail;
	};

	template<class T_Tuple_v>
		requires requires
	{
		requires S_ID_Select<T_Tuple_v>::ID == E_Tuple_ID::TUPLE_V;
	}
	struct S_Parameter<T_Tuple_v> :
		S_ID_Select<T_Tuple_v>,
		S_Size<T_Tuple_v>
	{
	private:
		using tuple_p_Parameter = S_Parameter<U_Create_p<T_Tuple_v>>;
	public:

		using tuple = T_Tuple_v;
		static constexpr auto value = tuple_p_Parameter::value;
		using head = tuple_p_Parameter::head;
		using tail = tuple_p_Parameter::tail;
	};

	template<class T_Head, class T, class T_Tail>
	struct S_Parameter<tuple_tp<T_Head, T, T_Tail>> :
		S_ID_Select<tuple_tp<T_Head, T, T_Tail>>,
		S_Size<tuple_tp<T_Head, T, T_Tail>>
	{

		using tuple = tuple_tp<T_Head, T, T_Tail>;
		using type = T;
		using head = T_Head;
		using tail = T_Tail;
	};


	template<class T_Head, auto t_value, class T_Tail>
	struct S_Parameter<tuple_vp<T_Head, t_value, T_Tail>>:
		S_ID_Select<tuple_vp<T_Head, t_value, T_Tail>>,
		S_Size<tuple_vp<T_Head, t_value, T_Tail>>
	{

		using tuple = tuple_vp<T_Head, t_value, T_Tail>;
		static constexpr auto value = t_value;

		using head = T_Head;
		using tail = T_Tail;
	};


	//static constexpr int select = head_size - static_cast<bool>(tail_size == size);


}
