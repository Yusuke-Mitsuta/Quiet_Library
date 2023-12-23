#pragma once

#include<tuple>
#include<optional>

#include"Tuple_Parameter.h"
#include"Tuple_Declare.h"

namespace N_Tuple
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

		static constexpr N_Constexpr::String name = {""};

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

	};

	template<class T_Return_type>
	struct Control_p_invalid
	{
	private:
		using r_type = T_Return_type;
	public:

		static constexpr size_t head_size = 0;
		static constexpr size_t tail_size = 0;
		static constexpr size_t size = 0;
		static constexpr int select = -1;

		static constexpr N_Constexpr::String name = { "" };

		using head = r_type;
		using tail = r_type;

		using next = r_type;
		using prev = r_type;
		using remove = r_type;
		using front = r_type;
		using back = r_type;
		using reverse = r_type;
	};

	template<class ...T_Type>
	struct Control_t :
		Control_p<tuple_t<T_Type...>>
	{
	private:

		using Tuple_t = tuple_t<T_Type...>;

		template<class T_Select_Tuple_t>
		using Select_Tuple_t = typename S_Parameter<T_Select_Tuple_t>::type;

	public:

		//�I�����Ă���v�f�̌^��Ԃ�
		using type = Select_Tuple_t<Tuple_t>;

		using next_t = Select_Tuple_t<U_Next<Tuple_t>>;
		using prev_t = invalid_t;
		using front_t = Select_Tuple_t<U_Front<Tuple_t>>;
		using back_t = Select_Tuple_t<U_Back<Tuple_t>>;

	};

	struct Control_t_invalid
	{
		using type = invalid_t;
		using next_t = invalid_t;
		using prev_t = invalid_t;
		using front_t = invalid_t;
		using back_t = invalid_t;
	};

	template<>
	struct Control_t<> :
		Control_t_invalid,
		Control_p_invalid<tuple_t<>>
	{};

	template<class T_Head, class T, class T_Tail>
	struct Control_tp :
		Control_p<tuple_tp<T_Head, T, T_Tail>>
	{
	private:
		using Tuple_tp = tuple_tp<T_Head, T, T_Tail>;

		template<class T_Select_Tuple_t>
		using Select_Tuple_t = typename S_Parameter<T_Select_Tuple_t>::type;

	public:

		//�I�����Ă���v�f�̌^��Ԃ�
		using type = Select_Tuple_t<Tuple_tp>;

		using next_t = Select_Tuple_t<U_Next<Tuple_tp>>;
		using prev_t = Select_Tuple_t<U_Prev<Tuple_tp>>;
		using front_t = Select_Tuple_t<U_Front<Tuple_tp>>;
		using back_t = Select_Tuple_t<U_Back<Tuple_tp>>;

	};

	template<class T>
	struct Control_tp<tuple_t<>, T, tuple_t<>> :
		Control_p<tuple_tp<tuple_t<>, T, tuple_t<>>>
	{
	private:
		using Tuple_tp = tuple_tp<tuple_t<>, T, tuple_t<>>;

		template<class T_Select_Tuple_t>
		using Select_Tuple_t = typename S_Parameter<T_Select_Tuple_t>::type;

	public:

		//�I�����Ă���v�f�̌^��Ԃ�
		using type = Select_Tuple_t<Tuple_tp>;

		using next_t = invalid_t;
		using prev_t = invalid_t;
		using front_t = T;
		using back_t = T;

	};

	template<>
	struct Control_tp<tuple_t<>, invalid_t, tuple_t<>> :
		Control_t_invalid,
		Control_p_invalid<tuple_tp<tuple_t<>, invalid_t, tuple_t<>>>
	{};

	struct Control_v_invalid
	{
		static constexpr auto value = invalid;
		static constexpr auto next_v = invalid;
		static constexpr auto prev_v = invalid;
		static constexpr auto front_v = invalid;
		static constexpr auto back_v = invalid;
	};

	template<auto ...t_value>
	struct Control_v :
		Control_p<tuple_v<t_value...>>
	{
		using Tuple_v = tuple_v<t_value...>;
	private:
		template<class T_Select_Tuple_v>
		static constexpr auto Select_Tuple_v = S_Parameter<T_Select_Tuple_v>::value;
	public:

		//�I�����Ă���v�f��Ԃ�
		static constexpr auto value = Select_Tuple_v<Tuple_v>;

		static constexpr auto next_v = Select_Tuple_v<U_Next<Tuple_v>>;
		static constexpr auto prev_v = invalid;
		static constexpr auto front_v = Select_Tuple_v<U_Front<Tuple_v>>;
		static constexpr auto back_v = Select_Tuple_v<U_Back<Tuple_v>>;

	};

	template<>
	struct Control_v<> :
		Control_v_invalid,
		Control_p_invalid<tuple_v<>>
	{};

	template<class T_Head, auto t_value, class T_Tail>
	struct Control_vp :
		Control_p<tuple_vp<T_Head, t_value, T_Tail>>
	{
		using Tuple_vp = tuple_vp<T_Head, t_value, T_Tail>;
	private:
		template<class T_Select_Tuple_v>
		static constexpr auto Select_Tuple_v = S_Parameter<T_Select_Tuple_v>::value;
	public:

		//�I�����Ă���v�f��Ԃ�
		static constexpr auto value = Select_Tuple_v<Tuple_vp>;

		static constexpr auto next_v = Select_Tuple_v<U_Next<Tuple_vp>>;
		static constexpr auto prev_v = Select_Tuple_v<U_Prev<Tuple_vp>>;
		static constexpr auto front_v = Select_Tuple_v<U_Front<Tuple_vp>>;
		static constexpr auto back_v = Select_Tuple_v<U_Back<Tuple_vp>>;

	};


	template<>
	struct Control_vp<tuple_v<>, invalid, tuple_v<>> :
		Control_v_invalid,
		Control_p_invalid<tuple_vp<tuple_v<>, invalid, tuple_v<>>>
	{};



}