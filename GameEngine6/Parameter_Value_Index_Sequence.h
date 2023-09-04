#pragma once

template<auto ...t_Parameters>
struct S_Parameter_Value;

template<size_t _Index>
struct IS_Index_Sequence
{
	template<class T_Index_Sequence>
	struct S_Index_Sequence;
	

	template<int ..._Index>
	struct S_Index_Sequence<std::index_sequence<_Index...>>
	{
		using Type = S_Parameter_Value<_Index...>;
	};

	using Type = typename S_Index_Sequence<std::make_index_sequence<_Index>>::Type;

};