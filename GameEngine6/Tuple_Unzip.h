#pragma once
#include<tuple>
#include"Concept.h"

template<class ...T_Tuple>
struct IS_TupleUnzip
{
	template<int t_Number,class T_Flont_Type, class ...T_Tuple>
	struct S_TupleUnzip
	{
		using Type = S_TupleUnzip<t_Number+1,T_Tuple..., T_Flont_Type>::Type;

		template<class MT_FlontType,class ...MT_Tuple>
		static constexpr void TupleUnzip(auto& set_Tuple, MT_FlontType& flont, MT_Tuple&... tuple)
		{
			std::get<t_Number>(set_Tuple) = flont;
			S_TupleUnzip<t_Number+1,T_Tuple..., T_Flont_Type>::TupleUnzip(set_Tuple,tuple...);
		}
	};

	template<int t_Number,class ...T_TupleInside, class ...T_Tuple>
	struct S_TupleUnzip<t_Number,std::tuple<T_TupleInside...>, T_Tuple...>
	{
		using Type = S_TupleUnzip<t_Number+1,T_TupleInside..., T_Tuple...>::Type;

		template<size_t ...N, class MT_FlontType, class ...MT_Tuple>
		static constexpr void TupleUnzip(auto& set_Tuple,std::integer_sequence<size_t,N...> , MT_FlontType& flont_Tuple, MT_Tuple&... tuple)
		{
			S_TupleUnzip<t_Number,T_TupleInside..., T_Tuple...>::TupleUnzip(set_Tuple, std::get<N>(flont_Tuple)..., tuple...);
		}
		
		template<class MT_FlontType, class ...MT_Tuple>
		static constexpr void TupleUnzip(auto& set_Tuple, MT_FlontType& flont_Tuple, MT_Tuple&... tuple)
		{
			S_TupleUnzip<t_Number, std::tuple<T_TupleInside...>,T_Tuple...>::TupleUnzip(set_Tuple,std::make_index_sequence<sizeof...(T_TupleInside)>(),flont_Tuple,tuple...);
		}
	};

	template<int t_Number,class ...T_Tuple>
	struct S_TupleUnzip<t_Number, std::nullopt_t, T_Tuple...>
	{
		using Type = std::tuple<T_Tuple...>;

		static constexpr void TupleUnzip(auto& set_Tuple){}
	};

	using Type = S_TupleUnzip<0,T_Tuple..., std::nullopt_t>::Type;

	Type tuple;

	constexpr IS_TupleUnzip(T_Tuple&... set_Tuple)
	{
		S_TupleUnzip<0, T_Tuple..., std::nullopt_t>::TupleUnzip(tuple, set_Tuple...);
	}

	constexpr operator Type()
	{
		return tuple;
	}

};