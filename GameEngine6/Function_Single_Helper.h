#pragma once

#include"SwapType.h"
#include"Tuple.h"

namespace quiet::N_Function
{
	template<class ...T_Parts>
	struct I_Function_Valid_Data;
	

	//�d�l
	//[T_Parts...]��[Function]���g�p�o���邩���肵�A���������[Function_Core]�ɓZ�߂���
	// 
	//�e���v���[�g
	//[T_Parts...]:
	//	���\�b�h�Ɏg�p���鋤�ʂ̃|�C���^�[�̌^(�ȗ��\)
	//	�֐��I�u�W�F�N�g�̌^
	//	����ɑ΂�������̌^(���т̈�Ԍ��̌^���A�֐��̈����^�̈�Ԍ��Ɣ��肳���)
	template<class ...T_Parts>
	struct I_Function_Single_Helper
	{
	private:
		using Lapping_Fn = I_Function_Valid_Data<T_Parts...>;

		template<class T_True>
		using Fn_Judge = U_Judge_t<T_True,is_invalid_not<typename Lapping_Fn::request_args>>;

	public:

		//�d�l
		//�Z�߂�ꂽ[Function_Core]
		using type = typename I_Function_Valid_Data<T_Parts...>::type;

		//�d�l
		//�Z�߂�ꂽ�֐��I�u�W�F�N�g�ɑΉ������A�g�p�����^�̔ԍ���[tupel_t<tuple_v<>>]�ɓ����
		using access_number = tuple_t<Fn_Judge<
			N_Tuple::U_Select<
			same_as<typename Lapping_Fn::function,
			typename I_Function_Valid_Data<N_Tuple::U_Element_t<1,tuple_t<T_Parts...>>>::function>,
			typename N_Tuple::U_index_sequence<sizeof...(T_Parts)>>>>;
		
		//�d�l
		//�Z�ߍ�Ƃ���������΁A[T_Parts...]�̐擪�̌^���A���s����΁A[invalid_t]��Ԃ�
		using judge = Fn_Judge<typename tuple_t<T_Parts...>::front_t>;


	};

};

