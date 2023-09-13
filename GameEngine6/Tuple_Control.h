#pragma once

#include<tuple>
#include<optional>

#include"Tuple_Declare.h"

namespace N_Tuple
{

	template<class ..._Types>
	struct _Control
	{
	private:

		using tuple = std::tuple<_Types...>;

	public:

		static constexpr size_t Size = sizeof...(_Types);

		using Flnot = std::tuple_element_t<0, tuple>;

		using Back = std::tuple_element_t<Size - 1, tuple>;
	
	};

	template<class ...T_Head_Types, class T, class ...T_Tail_Types>
	struct _Control<_Head<T_Head_Types...>, T, _Tail<T_Tail_Types...>> :
		public _Control<T_Head_Types..., T,T_Tail_Types...>
	{
	private:
		using Change_Tuple = _t< _Head<T_Head_Types...>, T, _Tail<T_Tail_Types...>>;
	public:

		static constexpr size_t Size_Head = sizeof...(T_Head_Types);

		static constexpr size_t Size_Tail = sizeof...(T_Tail_Types);
		
		using Next = typename _Next<Change_Tuple>::Type;

		using Prev = typename _Prev<Change_Tuple>::Type;

		using Remove = typename _Remove<Change_Tuple>::Type;

		using This = T;

		using Type = Change_Tuple;
	};

	template<>
	struct _Control<_Head<>,_Tail<>>
	{
		static constexpr size_t Size = 0;
		static constexpr size_t Size_Head = 0;
		static constexpr size_t Size_Tail = 0;
		using Flnot= std::nullopt_t;
		using Back = std::nullopt_t;
		using Next = std::nullopt_t;
		using Prev = std::nullopt_t;
		using Remove = std::nullopt_t;
		using This= std::nullopt_t;
		using Type = _t<>;
	};

}