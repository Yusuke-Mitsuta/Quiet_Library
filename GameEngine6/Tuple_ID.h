#pragma once

namespace N_Tuple
{

	enum class E_Tuple_ID
	{
		NONE,
		TUPLE,
		TUPLE_T,
		TUPLE_TP,
		TUPLE_V,
		TUPLE_VP,
		TUPLE_P,
		TUPLE_NOT_P,
	};
	
	struct ID
	{
	private:
		template<E_Tuple_ID id>
		struct tuple {};

	public:

		using tuple_tp = tuple<E_Tuple_ID::TUPLE_TP>;

		using tuple_t = tuple<E_Tuple_ID::TUPLE_T>;

		using tuple_vp = tuple<E_Tuple_ID::TUPLE_VP>;

		using tuple_v = tuple<E_Tuple_ID::TUPLE_V>;

	};




}