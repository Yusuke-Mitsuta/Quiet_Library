#pragma once

#include"Tuple.h"
#include"SwapType.h"
#include"Select_Type.h"
#include"Function_Single_Data.h"


namespace N_Function
{

	//�d�l
	//�֐��|�C���^�[�ɑ΂��āA�����̒l�����������A�����v�Ŕ��肷��
	//
	//�e���v���[�g
	//TP_Fns::�֐��|�C���^�[�A�w�肷������A��Tuple
	//
	//�⑫
	//T_Fn_Args�͊֐��|�C���^�[�A����Ɏw�肷������A���̊֐��|�C���^�[�A�ƂȂ�悤�ɂ��鎖
	// //SetJudge::�֐��ɑ΂��āA�u���ɑ��������̌^�A�֐��Ƀo�C���h�ς݂̈����̌^�v���֐��ɑ΂�������̌^�̌�������ƌ݊��������邩���肷��
	//Fns::�֐��|�C���^�[or[Function_Single]�ƁA���ɑ��������̌^��[Function_Single]�Ƃ��Ă܂Ƃ߁A���̓����[TP_Fns...]���Ȃ��Ȃ�܂ŌJ��Ԃ�
	template<class ...T_Fn_Parts>
	struct IS_Function_Multiple_Helper
	{
	private:

	public:

		using commond_point = std::tuple_element_t<0, tuple_t<T_Fn_Parts...>>;


		template<class T_Tuple, class T_method = typename I_Function_Single_Data<typename T_Tuple::type>::method>
		struct S_Method_Search
		{
			using type = T_Tuple;
		};

		template<class T_Tuple>
		struct S_Method_Search<T_Tuple, invalid_t>
		{
			using type = S_Method_Search<typename T_Tuple::next>::type;
		};

		template<class T_Tuple>
			requires is_invalid<typename T_Tuple::type>
		struct S_Method_Search<T_Tuple, invalid_t>
		{
			using type = T_Tuple;
		};


		template<class T_Tuple, class T_Tuple_Method_Bound = tuple_t<>>
		struct S_Method_Bound
		{

			template<class T_Method_Point>
			using chack_tuple = typename
				N_Tuple::U_Range<T_Tuple, T_Method_Point::head_size-(T_Method_Point::head_size== T_Method_Point::size)>::reverse;


			template<class T_Method_Point = typename S_Method_Search<T_Tuple>::type>
			struct S_Method_Point
			{

				template<class T_Tuple,class T_Method_Group>
				using Method_Bound =typename S_Method_Bound<typename T_Tuple::next,
					N_Tuple::U_Insert<T_Tuple_Method_Bound,typename T_Method_Group::remove_p>>::type;

				//�d�l
				//�֐��y�сA�����̌^�ɑ΂��āA�K�؂Ƀ|�C���^�[���Z�b�g����
				// 
				// �e���v���[�g
				//[T_Function_Check]:�擾�����֐��A�y�ш������A���Ɏg�p�o������
				//[T_Dedicated_Point_Check]:�擾�����֐��A�y�ш������A�֐��̎��ɐݒ肳��Ă���|�C���^�[�Ŏg�p�o������
				//[T_Commond_Point_Check]:�擾�����֐��A�y�ш������A���ʂŐݒ肳�ꂽ�|�C���^�[�Ŏg�p�o������
				template<class T_Function_Check = typename I_Function_Single_Data<chack_tuple<T_Method_Point>>::function,
						 class T_Dedicated_Point_Check = typename I_Function_Single_Data<chack_tuple<typename T_Method_Point::next>>::function,
						 class T_Commond_Point_Check = typename I_Function_Single_Data<N_Tuple::U_Insert<chack_tuple<T_Method_Point>,commond_point,0>>::function>
				struct S_Function_Check
				{
					using type = Method_Bound<T_Method_Point, chack_tuple<T_Method_Point>>;
				};

				//�d�l
				//�擾�����֐��A�y�ш������A�֐��̎��ɐݒ肳��Ă���|�C���^�[�Ŏg�p�o������
				template<class T_Dedicated_Point_Check, class T_Commond_Point_Check>
				struct S_Function_Check<invalid_t, T_Dedicated_Point_Check, T_Commond_Point_Check>
				{
					using type = Method_Bound<typename T_Method_Point::next, chack_tuple<typename T_Method_Point::next>>;
				};

				//�d�l
				//�擾�����֐��A�y�ш������A���ʂŐݒ肳�ꂽ�|�C���^�[�Ŏg�p�o������
				template<class T_Commond_Point_Check>
				struct S_Function_Check<invalid_t, invalid_t, T_Commond_Point_Check>
				{
					using type = Method_Bound<T_Method_Point, N_Tuple::U_Insert<chack_tuple<T_Method_Point>, commond_point, 0>>;

				};

				//�d�l
				//�֐��ɑ΂��āA�����̕����s��v�ȏꍇ�A���̊֐���T������
				template<>
				struct S_Function_Check<invalid_t, invalid_t, invalid_t>
				{

					using type = S_Method_Point<typename S_Method_Search<typename T_Method_Point::next>::type>::type;
				};

				using type = S_Function_Check<>::type;

			};

			//�d�l
			//�֐��ɑ΂��āA�����̕����s��v�ł���A�S�Ă̒T�����I������ꍇ
			template<class T_Head>
			struct S_Method_Point<tuple_tp<T_Head,invalid_t,tuple_t<>>>
			{
				using type = invalid_t;
			};

			using type = S_Method_Point<>::type;

		};

		//�d�l
		//�S�Ă̌^�̒T��������ɏI�������ꍇ�A���ʂ��o�͂���
		template<class T_Head,class T_Tail,class T_Tuple_Method_Bound>
		struct S_Method_Bound<tuple_tp<T_Head,invalid_t,T_Tail>,T_Tuple_Method_Bound>
		{
			using type = T_Tuple_Method_Bound;

		};

	public:

		using type = S_Method_Bound<
			typename tuple_t<T_Fn_Parts...>::reverse::front>::type;

		

		//�d�l
		//�S�Ă̊֐��I�u�W�F�N�g�ɂ����ēK�؂ȃN���X�|�C���^�[���Z�b�g����Ă��邩���肷��
		//using Pointer_Judge = S_CorrectType<>::type;


		//using type1_1 = S_CorrectType<>;

		//using type1 = S_CorrectType<0>;

		//�d�l
		//����̍��ڂ���N���X�|�C���^�[���Z�b�g����Ă��邩�����O����
		//using Not_Pointer_Judge = S_CorrectType<0>::type;

		//using Fns = Type::Fns;

	};

}