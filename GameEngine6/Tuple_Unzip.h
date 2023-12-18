#pragma once
#include<tuple>
#include"Concept.h"
#include"tuple_Helper.h"

//仕様
//[...T_Tuple]内の全てのTupleを分解し、1つのTupleに格納する
//
//template
//...T_Tuple::一つのTupleに格納する型
//
//補足
//[using type]で格納したTupleの型を取得する
//[type tuple]で格納したTupleの変数を取得する
template<class ...T_Tuple>
struct IS_TupleUnzip
{
	template<int t_Number,class T_Front_Type, class ...T_Tuple>
	struct S_TupleUnzip
	{
		using Type = S_TupleUnzip<t_Number+1,T_Tuple..., T_Front_Type>::Type;

		//仕様
		//[front]の値を[set_Tuple]に格納する
		//
		//引数
		//set_Tuple::分解後の値を格納するTuple
		//front::格納する値
		//tuple::二つ目以降の値
		template<class MT_FrontType,class ...MT_Tuple>
		static constexpr void TupleUnzip(auto& set_Tuple, MT_FrontType& front, MT_Tuple&... tuple)
		{
			std::get<t_Number>(set_Tuple) = front;
			S_TupleUnzip<t_Number+1,T_Tuple..., T_Front_Type>::TupleUnzip(set_Tuple,tuple...);
		}
	};

	template<int t_Number,class ...T_TupleInside, class ...T_Tuple>
	struct S_TupleUnzip<t_Number,std::tuple<T_TupleInside...>, T_Tuple...>
	{
	private:
		//仕様
		//[front_Tuple]の値を分解し、[set_Tuple]に格納する
		//
		//引数
		//set_Tuple::分解後の値を格納するTuple
		//front_Tuple::分解するtupleの値
		//tuple::二つ目以降の値
		template<size_t ...N, class MT_FrontType, class ...MT_Tuple>
		static constexpr void TupleUnzip(auto& set_Tuple, std::integer_sequence<size_t, N...>, MT_FrontType& front_Tuple, MT_Tuple&... tuple)
		{
			S_TupleUnzip<t_Number, T_TupleInside..., T_Tuple...>::TupleUnzip(set_Tuple, std::get<N>(front_Tuple)..., tuple...);
		}

	public:
		using Type = S_TupleUnzip<t_Number+1,T_TupleInside..., T_Tuple...>::Type;
		
		//仕様
		//[front_Tuple]の値を分解準備する
		//
		//引数
		//set_Tuple::分解後の値を格納するTuple
		//front_Tuple::分解するtupleの値
		//tuple::二つ目以降の値
		template<class MT_FrontType, class ...MT_Tuple>
		static constexpr void TupleUnzip(auto& set_Tuple, MT_FrontType& front_Tuple, MT_Tuple&... tuple)
		{
			S_TupleUnzip<t_Number, std::tuple<T_TupleInside...>,T_Tuple...>::TupleUnzip(set_Tuple,std::make_index_sequence<sizeof...(T_TupleInside)>(),front_Tuple,tuple...);
		}
	};

	template<int t_Number,class ...T_Tuple>
	struct S_TupleUnzip<t_Number, invalid_t, T_Tuple...>
	{
		//仕様
		//[...T_Tuple]内の全てのTupleを分解し、1つのTupleに格納した型
		using Type = std::tuple<T_Tuple...>;

		//仕様
		//[set_Tuple]の値の格納を終了する
		static constexpr void TupleUnzip(auto& set_Tuple){}
	};
public:
	//仕様
	//[...T_Tuple]内の全てのTupleを分解し、1つのTupleに格納した型
	using Type = S_TupleUnzip<0,T_Tuple..., invalid_t>::Type;

	//仕様
	//分解し、格納したTupleの変数を取得する
	Type tuple;

private:

	//仕様
	//[set_Tuple...]内のTupleを分解し、1つのTupleにまとめた値を返す
	//
	//引数
	//set_Tuple::分解するTuple
	template<size_t ...N>
	constexpr auto TupleUnzip(std::index_sequence<N...>, T_Tuple&... set_Tuple)
	{
		typename S_EnvelopOptional<Type>::Type optionalTuple;
		S_TupleUnzip<0, T_Tuple..., invalid_t>::TupleUnzip(optionalTuple, set_Tuple...);
		Type tuple(std::get<N>(optionalTuple).value()...);
		return tuple;
	}
public:

	//仕様
	//[...set_Tuple]内の全てのTupleを分解し、1つのTupleに格納する
	constexpr IS_TupleUnzip(T_Tuple&... set_Tuple)
		:tuple(TupleUnzip(std::make_index_sequence<std::tuple_size_v<Type>>(), set_Tuple...)){}

	constexpr operator Type()
	{
		return tuple;
	}

};


