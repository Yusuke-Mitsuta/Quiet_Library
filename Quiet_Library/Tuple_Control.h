/*!
 * Tuple_Control.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include<tuple>
#include<optional>

#include"Tuple_Parameter.h"
#include"Tuple_Declare.h"

namespace quiet::N_Tuple
{
	//�d�l
	//[T_Tuple]�̑I���ʒu�̑���A�폜�̎��{
	template<class T_Tuple>
	struct Control_p
	{

		//�I�𒆂̗v�f���O�ɂ���v�f��
		static constexpr size_t head_size = S_Parameter<T_Tuple>::head_size;

		//�I�𒆂̗v�f�����ɂ���v�f��
		static constexpr size_t tail_size = S_Parameter<T_Tuple>::tail_size;

		//�v�f��
		static constexpr size_t size = S_Parameter<T_Tuple>::size;

		//���ݑI�����Ă���ԍ�
		//static constexpr int select = S_Parameter<T_Tuple>::select;

		//���ݑI�����Ă���^���A�O�̌^���X�g
		// [tuple_t,v]�̏ꍇ�A�擪�̒l���I������Ă��镨�ƌ��Ȃ�
		using head = S_Parameter<T_Tuple>::head;

		//���ݑI�����Ă���^���A�O�̌^���X�g
		// [tuple_t,v]�̏ꍇ�A�擪�̒l���I������Ă��镨�ƌ��Ȃ�
		using tail = S_Parameter<T_Tuple>::tail;

		//���̗v�f��I������
		using next = U_Next<T_Tuple>;

		//�O�̗v�f��I������
		using prev = U_Prev<T_Tuple>;

		//�I�����Ă���v�f���폜����
		using remove = U_Remove<T_Tuple>;

		//�擪�̗v�f��I������
		using front = U_Front<T_Tuple>;

		//�Ō�̗v�f��I������
		using back = U_Back<T_Tuple>;

		//���я��𔽓]������
		using reverse = U_Reverse<T_Tuple>;

		//[tuple_tp,vp]��[tuple_t,v]�ɕύX����
		//	[tuple_t,v]�̏ꍇ�͂��̂܂܂ƂȂ�
		using remove_p = U_Remove_p<T_Tuple>;

		//[tuple_t,v]��[tuple_tp,vp]�ɕύX����
		//	[tuple_tp,vp]�̏ꍇ�͂��̂܂܂ƂȂ�
		using create_p = U_Create_p<T_Tuple>;

	};

	template<class T_Tuple_t>
	struct Control_t :
		Control_p<T_Tuple_t>
	{
	private:

		using Tuple_t = T_Tuple_t;

		template<class T_Select_Tuple_t>
		using Select_Tuple_t = typename S_Parameter<T_Select_Tuple_t>::type;

	public:

		//�I�����Ă���v�f�̌^��Ԃ�
		using type = Select_Tuple_t<Tuple_t>;

		using next_t = Select_Tuple_t<U_Next<Tuple_t>>;
		using prev_t = Select_Tuple_t<U_Prev<Tuple_t>>;
		using front_t = Select_Tuple_t<U_Front<Tuple_t>>;
		using back_t = Select_Tuple_t<U_Back<Tuple_t>>;

	};

	template<class T_Tuple_v>
	struct Control_v :
		Control_p<T_Tuple_v>
	{
		using Tuple_v = T_Tuple_v;
	private:
		template<class T_Select_Tuple_v>
		static constexpr auto Select_Tuple_v = S_Parameter<T_Select_Tuple_v>::value;
	public:

		//�I�����Ă���v�f��Ԃ�
		static constexpr auto value = Select_Tuple_v<Tuple_v>;

		static constexpr auto next_v = Select_Tuple_v<U_Next<Tuple_v>>;
		static constexpr auto prev_v = Select_Tuple_v<U_Prev<Tuple_v>>;
		static constexpr auto front_v = Select_Tuple_v<U_Front<Tuple_v>>;
		static constexpr auto back_v = Select_Tuple_v<U_Back<Tuple_v>>;

	};



}