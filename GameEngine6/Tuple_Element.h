#pragma once

#include"Tuple_Declare.h"

namespace std
{
	template<size_t _Index, class ...T_Head_Types, class T, class ...T_Tail_Types>
	struct std::tuple_element<_Index,
		N_Tuple::Tuple_tp<N_Tuple::_Head<T_Head_Types...>,
		T, N_Tuple::_Tail<T_Tail_Types...>>>
	{
		using type = std::tuple_element_t<_Index, std::tuple<T_Head_Types..., T, T_Tail_Types...>>;
	};

	template<size_t _Index, class ...T_Head_Types, class ...T_Tail_Types>
	struct std::tuple_element<_Index,
		N_Tuple::Tuple_tp<N_Tuple::_Head<T_Head_Types...>,std::nullopt_t,
		N_Tuple::_Tail<T_Tail_Types...>>>
	{
		using type = std::tuple_element_t<_Index, std::tuple<T_Head_Types..., T_Tail_Types...>>;
	};

	template<size_t _Index, class T_Head_v, auto value, class T_Tail_v>
	struct std::tuple_element<_Index, N_Tuple::Tuple_vp<T_Head_v, value, T_Tail_v>>
	{
		using type = std::tuple_element_t<_Index, typename N_Tuple::Tuple_v_To_t<N_Tuple::Tuple_vp<T_Head_v, value, T_Tail_v>>::Type>;
	};

	template<size_t _Index,auto ...value>
	struct std::tuple_element<_Index, N_Tuple::Tuple_v<value...>>
	{
		using type = std::tuple_element_t<_Index, typename N_Tuple::Tuple_v_To_t< N_Tuple::Tuple_v<value...>>::Type>;
	};

}

namespace N_Tuple
{
	//仕様
	//[T_Tuple]の[_Index]番目の型を取得する
	template<size_t _Index, class T_Tuple>
	struct I_Element
	{
		using Type = std::tuple_element_t<_Index, T_Tuple>;
	};

	//仕様
	//[T_Tuple]の[_Index]番目の要素を取得する
	template<size_t _Index,class T_Head_v,auto value,class T_Tail_v>
	struct I_Element<_Index,Tuple_vp<T_Head_v,value,T_Tail_v>>
	{
	private:
		using T_Tuple = Tuple_vp<T_Head_v, value, T_Tail_v>;

	public:

		static constexpr auto value = std::tuple_element_t<_Index, T_Tuple>::value;
	};
	
	
	//仕様
	//[T_Tuple]の[_Index]番目の要素を取得する
	template<size_t _Index, auto ...value>
	struct I_Element<_Index, Tuple_v<value...>>
	{
	private:
		using T_Tuple = Tuple_v<value...>;

	public:
		static constexpr auto value = std::tuple_element_t<_Index, T_Tuple>::value;
	};

}