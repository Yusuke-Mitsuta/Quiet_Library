#pragma once

#include"Tuple_Class_Declare.h"

namespace N_Tuple
{
	//�擪�̗v�f��I������
	template<class T_Tuple>
	using U_Flnot = typename I_Select<0, T_Tuple>::Type;

	//�Ō�̗v�f��I������
	template<class T_Tuple>
	using U_Back = typename I_Select<S_Parameter<T_Tuple>::Size - 1, T_Tuple>::Type;

	//���̗v�f��I������
	template<class T_Tuple>
	using U_Next = typename I_Next<T_Tuple>::Type;

	//�O�̗v�f��I������
	template<class T_Tuple>
	using U_Prev = typename I_Prev<T_Tuple>::Type;

	//�w�肵���ԍ��̗v�f��I������
	template<int t_Select_Point,class T_Tuple>
	using U_Select = typename I_Select<t_Select_Point, T_Tuple>::Type;

	//[T_Tuple_t]�̕��я��𔽓]������
	template<class T_Tuple>
	using U_Reverse = typename I_Reverse<T_Tuple>::Type;

	//�d�l
	//[T_Tuple]��[_Index]�Ԗڂ̌^���擾����
	template<int _Index, class T_Tuple_t>
	using U_Element_t = typename I_Element<_Index, T_Tuple_t>::Type;


	template< class T_Tuple_t, int _Index>
	using U_Element_tau = typename I_Element<_Index, T_Tuple_t>::Type;

	//�d�l
	//[T_Tuple]��[_Index]�Ԗڂ̗v�f���擾����
	template<int _Index, class T_Tuple_v>
	static constexpr auto U_Element_v = I_Element<_Index, T_Tuple_v>::value;

}