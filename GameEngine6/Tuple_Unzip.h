#pragma once
#include<tuple>
#include"Concept.h"
#include"tuple_Helper.h"

//d—l
//[...T_Tuple]“à‚Ì‘S‚Ä‚ÌTuple‚ğ•ª‰ğ‚µA1‚Â‚ÌTuple‚ÉŠi”[‚·‚é
//
//template
//...T_Tuple::ˆê‚Â‚ÌTuple‚ÉŠi”[‚·‚éŒ^
//
//•â‘«
//[using Type]‚ÅŠi”[‚µ‚½Tuple‚ÌŒ^‚ğæ“¾‚·‚é
//[Type tuple]‚ÅŠi”[‚µ‚½Tuple‚Ì•Ï”‚ğæ“¾‚·‚é
template<class ...T_Tuple>
struct IS_TupleUnzip
{
	template<int t_Number,class T_Flont_Type, class ...T_Tuple>
	struct S_TupleUnzip
	{
		using Type = S_TupleUnzip<t_Number+1,T_Tuple..., T_Flont_Type>::Type;

		//d—l
		//[flont]‚Ì’l‚ğ[set_Tuple]‚ÉŠi”[‚·‚é
		//
		//ˆø”
		//set_Tuple::•ª‰ğŒã‚Ì’l‚ğŠi”[‚·‚éTuple
		//flont::Ši”[‚·‚é’l
		//tuple::“ñ‚Â–ÚˆÈ~‚Ì’l
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
	private:
		//d—l
		//[flont_Tuple]‚Ì’l‚ğ•ª‰ğ‚µA[set_Tuple]‚ÉŠi”[‚·‚é
		//
		//ˆø”
		//set_Tuple::•ª‰ğŒã‚Ì’l‚ğŠi”[‚·‚éTuple
		//flont_Tuple::•ª‰ğ‚·‚étuple‚Ì’l
		//tuple::“ñ‚Â–ÚˆÈ~‚Ì’l
		template<size_t ...N, class MT_FlontType, class ...MT_Tuple>
		static constexpr void TupleUnzip(auto& set_Tuple, std::integer_sequence<size_t, N...>, MT_FlontType& flont_Tuple, MT_Tuple&... tuple)
		{
			S_TupleUnzip<t_Number, T_TupleInside..., T_Tuple...>::TupleUnzip(set_Tuple, std::get<N>(flont_Tuple)..., tuple...);
		}

	public:
		using Type = S_TupleUnzip<t_Number+1,T_TupleInside..., T_Tuple...>::Type;
		
		//d—l
		//[flont_Tuple]‚Ì’l‚ğ•ª‰ğ€”õ‚·‚é
		//
		//ˆø”
		//set_Tuple::•ª‰ğŒã‚Ì’l‚ğŠi”[‚·‚éTuple
		//flont_Tuple::•ª‰ğ‚·‚étuple‚Ì’l
		//tuple::“ñ‚Â–ÚˆÈ~‚Ì’l
		template<class MT_FlontType, class ...MT_Tuple>
		static constexpr void TupleUnzip(auto& set_Tuple, MT_FlontType& flont_Tuple, MT_Tuple&... tuple)
		{
			S_TupleUnzip<t_Number, std::tuple<T_TupleInside...>,T_Tuple...>::TupleUnzip(set_Tuple,std::make_index_sequence<sizeof...(T_TupleInside)>(),flont_Tuple,tuple...);
		}
	};

	template<int t_Number,class ...T_Tuple>
	struct S_TupleUnzip<t_Number, std::nullopt_t, T_Tuple...>
	{
		//d—l
		//[...T_Tuple]“à‚Ì‘S‚Ä‚ÌTuple‚ğ•ª‰ğ‚µA1‚Â‚ÌTuple‚ÉŠi”[‚µ‚½Œ^
		using Type = std::tuple<T_Tuple...>;

		//d—l
		//[set_Tuple]‚Ì’l‚ÌŠi”[‚ğI—¹‚·‚é
		static constexpr void TupleUnzip(auto& set_Tuple){}
	};
public:
	//d—l
	//[...T_Tuple]“à‚Ì‘S‚Ä‚ÌTuple‚ğ•ª‰ğ‚µA1‚Â‚ÌTuple‚ÉŠi”[‚µ‚½Œ^
	using Type = S_TupleUnzip<0,T_Tuple..., std::nullopt_t>::Type;

	//d—l
	//•ª‰ğ‚µAŠi”[‚µ‚½Tuple‚Ì•Ï”‚ğæ“¾‚·‚é
	Type tuple;

private:

	//d—l
	//[set_Tuple...]“à‚ÌTuple‚ğ•ª‰ğ‚µA1‚Â‚ÌTuple‚É‚Ü‚Æ‚ß‚½’l‚ğ•Ô‚·
	//
	//ˆø”
	//set_Tuple::•ª‰ğ‚·‚éTuple
	template<size_t ...N>
	constexpr auto TupleUnzip(std::index_sequence<N...>, T_Tuple&... set_Tuple)
	{
		typename S_EnvelopOptional<Type>::Type optionalTuple;
		S_TupleUnzip<0, T_Tuple..., std::nullopt_t>::TupleUnzip(optionalTuple, set_Tuple...);
		Type tuple(std::get<N>(optionalTuple).value()...);
		return tuple;
	}
public:

	//d—l
	//[...set_Tuple]“à‚Ì‘S‚Ä‚ÌTuple‚ğ•ª‰ğ‚µA1‚Â‚ÌTuple‚ÉŠi”[‚·‚é
	constexpr IS_TupleUnzip(T_Tuple&... set_Tuple)
		:tuple(TupleUnzip(std::make_index_sequence<std::tuple_size_v<Type>>(), set_Tuple...)){}

	constexpr operator Type()
	{
		return tuple;
	}

};


