#pragma once

#include"Tuple_Declare.h"
#include<tuple>

namespace std
{

	template<size_t _Index, class ...T_Head_Types, class T, class ...T_Tail_Types>
	struct std::tuple_element<_Index,
		tuple_tp<tuple_t<T_Head_Types...>,
		T, tuple_t<T_Tail_Types...>>>
	{
		using type = std::tuple_element_t<_Index, std::tuple<T_Head_Types..., T, T_Tail_Types...>>;
	};

	template<size_t _Index, class ...T_Head_Types, class ...T_Tail_Types>
	struct std::tuple_element<_Index,
		tuple_tp<tuple_t<T_Head_Types...>,invalid_t,
		tuple_t<T_Tail_Types...>>>
	{
		using type = std::tuple_element_t<_Index, std::tuple<T_Head_Types..., T_Tail_Types...>>;
	};


	template<size_t _Index,class ...T_Types>
	struct std::tuple_element<_Index,
		tuple_t<T_Types...>>
	{
		using type = std::tuple_element_t<_Index, std::tuple<T_Types...>>;
	};

	template<size_t _Index, class T_Head_v, auto value, class T_Tail_v>
	struct std::tuple_element<_Index, tuple_vp<T_Head_v, value, T_Tail_v>>
	{
		using type = std::tuple_element_t<_Index,typename N_Tuple::Tuple_v_To_t<tuple_vp<T_Head_v, value, T_Tail_v>>::type>;
	};

	template<size_t _Index,auto ...value>
	struct std::tuple_element<_Index, tuple_v<value...>>
	{
		using type = std::tuple_element_t<_Index, typename N_Tuple::Tuple_v_To_t<tuple_v<value...>>::type>;
	};

}

namespace N_Tuple
{
	//仕様
	//[T_Tuple]の[_Index]番目の型を取得する
	template<size_t _Index, class ...T_Types>
	struct I_Element
	{
		template<class ...T_Types>
		struct S_Element
		{
			using type= invalid_t;
		};

		template<class ...T_Types>
			requires requires
		{
			requires sizeof...(T_Types) > _Index;
		}
		struct S_Element<T_Types...>
		{
			using type = std::tuple_element_t<_Index, std::tuple<T_Types...>>;
		};

		template<class ...T_Types>
			requires (sizeof...(T_Types)>_Index)
		struct S_Element<tuple_t<T_Types...>>
		{
			using type = std::tuple_element_t<_Index, std::tuple<T_Types...>>;
		};

		template<class T_Head,class T,class T_Tail>
			requires (tuple_tp<T_Head, T, T_Tail>::size > _Index)
		struct S_Element<tuple_tp<T_Head,T,T_Tail>>
		{
			using type = std::tuple_element_t<_Index, tuple_tp<T_Head, T, T_Tail>>;
		};

		using type =typename S_Element<T_Types...>::type;
	};


	//仕様
	//[T_Tuple]の[_Index]番目の要素を取得する
	template<size_t _Index,class T_Head_v,auto value,class T_Tail_v>
	struct I_Element<_Index,tuple_vp<T_Head_v,value,T_Tail_v>>
	{
	private:
		using T_Tuple = tuple_vp<T_Head_v, value, T_Tail_v>;

	public:

		static constexpr auto value = std::tuple_element_t<_Index, T_Tuple>::value;
	};
	
	
	//仕様
	//[T_Tuple]の[_Index]番目の要素を取得する
	template<size_t _Index, auto ...value>
	struct I_Element<_Index, tuple_v<value...>>
	{
	private:
		using T_Tuple = tuple_v<value...>;

	public:
		static constexpr auto value = std::tuple_element_t<_Index, T_Tuple>::value;
	};

}