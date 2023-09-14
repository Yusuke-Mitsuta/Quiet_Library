#pragma once

#include"Tuple_Declare.h"
#include"Tuple_Control.h"
#include"Tuple_Head.h"
#include"Tuple_Tail.h"

namespace N_Tuple
{
	template<class ..._Types>
	struct _t;

	template<class T_Flont_Type,class ..._Types>
	struct _t<T_Flont_Type, _Types...> :
		public _Control<_Head<>,T_Flont_Type,_Tail<_Types...>>
	{

	};

	template<class ...T_Head_Types, class T, class ...T_Tail_Types>
	struct _t<_Head<T_Head_Types...>, T, _Tail<T_Tail_Types...>> :
		public _Control<_Head<T_Head_Types...>, T, _Tail<T_Tail_Types...>>
	{

	};

	template<>
	struct _t<_Head<>, _Tail<>> :
		public _Control<_Head<>, _Tail<>>
	{
	};

	template<>
	struct _t<> :
		public _Control<_Head<>, _Tail<>>
	{
	};

}

namespace std
{
	template<class ...T_Type>
	struct tuple_size<N_Tuple::_t<T_Type...>> :
		integral_constant<size_t, N_Tuple::S_Parameter<
		N_Tuple::_t<T_Type...>>::Size> {};
}

