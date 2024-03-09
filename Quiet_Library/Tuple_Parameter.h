/*!
 * Tuple_Parameter.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include<tuple>

#include"Tuple_Class_Declare.h"

#include"Tuple_Size.h"
#include"Tuple_ID_Select.h"

namespace quiet::N_Tuple
{

	//�d�l
	//[tuple_t]�̊e��Size�A�y�ь^���Ăяo��
	//
	//�⑫
	// [tuple_t,tp,v,vp]���́A[T_Leftover_Types::tuple]�̏ꍇ([S_Parameter]�������l��Ԃ��Ȃ��ꍇ)��
	//	[std::tuple_element,std::tuple_size,std::get<t_array_size>(t)]�����ꉻ�����B
	template<class T_Types>
	struct S_Parameter :
		S_ID_Select<T_Types>,
		S_Size<T_Types>
	{
		using tuple =invalid_t;
		using type = invalid_t;
		static constexpr invalid_t value = invalid;
		using head = tuple_t<>;
		using tail = tuple_t<>;
	};

	//�d�l
	//[tuple_t]�̊e��Size�A�y�ь^���Ăяo��
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


	//�d�l
	//[tuple_v]�̊e��Size�A�y�ь^���Ăяo��
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


	//�d�l
	//[tuple_tp]�̊e��Size�A�y�ь^���Ăяo��
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


	//�d�l
	//[tuple_vp]�̊e��Size�A�y�ь^���Ăяo��
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


	//�d�l
	//�����o�[��[::tuple=tuple_t< _Ty1 , _Ty2 ...>]�����ꍇ�A���̃^�v���̃p�����[�^���Ăяo��
	template<class T>
		requires requires
	{
		requires (E_Tuple_ID::NONE == S_ID_Select<T>::ID);
		typename T::tuple;
		requires is_invalid_not<typename S_Parameter<typename T::tuple>::tuple>;
		requires std::is_class_v<typename T::tuple>;
	}
	struct S_Parameter<T> :
		S_Parameter<typename T::tuple> {};

	template<class T>
		requires requires
	{
		requires (E_Tuple_ID::NONE == S_ID_Select<T>::ID);
		//typename T_Request_Order::tuple;
		//requires is_invalid_not<typename S_Parameter<typename T_Request_Order::tuple>::tuple>;
		//requires std::is_class_v<typename T_Request_Order::tuple>;
	}
	struct S_Parameter<T&> :
		S_Parameter<T>
	{
		//using tuple = N_Tuple::U_Elements_Action<std::add_lvalue_reference, typename T_Request_Order::tuple>;
	};

	template<class T>
		requires requires
	{
		requires (E_Tuple_ID::NONE == S_ID_Select<T>::ID);
		//typename T_Request_Order::tuple;
		//requires is_invalid_not<typename S_Parameter<typename T_Request_Order::tuple>::tuple>;
		//requires std::is_class_v<typename T_Request_Order::tuple>;
	}
	struct S_Parameter<T*> :
		S_Parameter<T>
	{
		//using tuple = N_Tuple::U_Elements_Action<std::add_pointer, typename T_Request_Order::tuple>;
	};


}
