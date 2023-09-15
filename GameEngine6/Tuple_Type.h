#pragma once

#include"Tuple_Declare.h"
#include"Tuple_Control.h"
#include"Tuple_Head.h"
#include"Tuple_Tail.h"

namespace N_Tuple
{

	template<class ..._Types>
	struct Tuple_t
	{

	};

	template<class ..._Types>
	struct Tuple_tp;

	template<class ...T_Head_Types, class T, class ...T_Tail_Types>
	struct Tuple_tp<_Head<T_Head_Types...>, T, _Tail<T_Tail_Types...>> :
		public _Control_t<Tuple_tp<_Head<T_Head_Types...>, T, _Tail<T_Tail_Types...>>>
	{

	};

	template<class ..._Types>
	struct _Create_Tuple_Pointer;

	template<class ..._Types>
	struct _Create_Tuple_Pointer<Tuple_tp<_Types...>>
	{
		using Type = Tuple_tp<_Types...>;
	};

	template<>
	struct _Create_Tuple_Pointer<>
	{
		using Type = Tuple_tp<_Head<>, _Tail<>>;
	};

	template<class T_Flont_Type,class ..._Types>
	struct _Create_Tuple_Pointer<T_Flont_Type, _Types...>
	{
		using Type = Tuple_tp<_Head<>, T_Flont_Type, _Tail<_Types...>>;
	};

}


//template<class ..._Types>
//using Tuple_p = typename N_Tuple::_Create_Tuple_Pointer<_Types...>::Type;

namespace std
{
	template<class ...T_Type>
	struct tuple_size<N_Tuple::Tuple_tp<T_Type...>> :
		integral_constant<size_t, N_Tuple::S_Parameter<
		N_Tuple::Tuple_tp<T_Type...>>::Size> {};
}

