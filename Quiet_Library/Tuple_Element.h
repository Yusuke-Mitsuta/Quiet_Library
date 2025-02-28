/*!
 * Tuple_Element.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Tuple_Declare.h"
#include"Invalid.h"
#include<tuple>

namespace std
{

	template <size_t I, class T>
		requires requires
	{
		requires quiet::is_invalid_not<typename quiet::N_Tuple::S_Parameter<T>::tuple>;
	}
	struct tuple_element<I, T> 
	{
		using type = quiet::N_Tuple::U_Element_t<I, T>;
	};


}

namespace quiet::N_Tuple
{
	//仕様
	//[T_Tuple_Data]の[_Index]番目の型を取得する
	template<size_t _Index, class T_Tuple_Data>
	struct I_Element
	{
		template<class T_Tuple>
		struct S_Element
		{
			using type= invalid_t;
		};

		template<class T>
			requires requires
		{
			requires is_invalid_not<typename N_Tuple::S_Parameter<T>::tuple>;
			requires !is_Tuple<T>;
		}
		struct S_Element<T>
		{
			using type = S_Element<typename N_Tuple::S_Parameter<T>::tuple>::type;
		};

		template<class ...T_Types>
			requires (sizeof...(T_Types)>_Index)
		struct S_Element<tuple_t<T_Types...>>
		{
			using type = std::tuple_element_t<_Index, std::tuple<T_Types...>>;
		};

		template<class ...T_Head,class T,class ...T_Tail>
			requires (tuple_tp<tuple_t<T_Head...>, T, tuple_t<T_Tail...>>::size > _Index)
		struct S_Element<tuple_tp<tuple_t<T_Head...>, T, tuple_t<T_Tail...>>>
		{
			using type = std::tuple_element_t<_Index, std::tuple<T_Head..., T, T_Tail...>>;
		};

		template<class ...T_Head, class ...T_Tail>
			requires (tuple_tp<tuple_t<T_Head...>, invalid_t, tuple_t<T_Tail...>>::size > _Index)
		struct S_Element<tuple_tp<tuple_t<T_Head...>, invalid_t, tuple_t<T_Tail...>>>
		{
			using type = std::tuple_element_t<_Index, std::tuple<T_Head..., T_Tail...>>;
		};

		using type =typename S_Element<T_Tuple_Data>::type;
	};


	//仕様
	//[T_Tuple_Data]の[_Index]番目の要素を取得する
	template<size_t _Index,class T_Head_v,auto t_value,class T_Tail_v>
	struct I_Element<_Index,tuple_vp<T_Head_v,t_value,T_Tail_v>>
	{
	private:
		using T_Tuple = tuple_vp<T_Head_v, t_value, T_Tail_v>;

	public:

		static constexpr auto value = std::tuple_element_t<_Index, T_Tuple>::value;
	};
	
	
	//仕様
	//[T_Tuple_Data]の[_Index]番目の要素を取得する
	template<size_t _Index, auto ...t_values>
	struct I_Element<_Index, tuple_v<t_values...>>
	{
	private:
		using T_Tuple = tuple_v<t_values...>;

	public:
		static constexpr auto value = std::tuple_element_t<_Index, T_Tuple>::value;
	};

}