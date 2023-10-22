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
		//using commond_point = std::tuple_element_t<0, tuple_t<T_Fn_Parts...>>;


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
			using type = typename T_Tuple::back;
		};



		template<class T_Tuple, class T_Tuple_Method_Bound = tuple_t<>>
		struct S_Method_Bound
		{
			template<class T_Method_Point>
			struct S_Method_Chack
			{
				using chack_tuple = typename
					N_Tuple::U_Range<T_Tuple, T_Method_Point::head_size>::reverse;

				using type = I_Function_Single_Data<chack_tuple>::method;
			};

			template<class T_Args_Start_Point = T_Tuple>
			struct S_Args_Start_Point
			{


				template<class T_Method_Point = typename S_Method_Search<T_Args_Start_Point>::type,
					class T_Args_Chack =typename S_Method_Chack<T_Method_Point>::type>
				struct S_Method_Args_Chack
				{
					using type4 =// T_Tuple;
						//typename T_Method_Point::next;
						S_Method_Bound<typename T_Method_Point::next,
						N_Tuple::U_Insert<T_Tuple_Method_Bound, typename S_Method_Chack<T_Method_Point>::chack_tuple>>;
				};
				
				using T = T_Tuple;
				using type3 = S_Method_Args_Chack<>;

			};
			using T = T_Tuple;
			using T1 = typename S_Method_Search<T_Tuple>::type;

			using type2 = S_Args_Start_Point<>;

		};

		template<class T_Head,class T_Tail,class T_Tuple_Method_Bound>
		struct S_Method_Bound<tuple_tp<T_Head,invalid_t,T_Tail>,T_Tuple_Method_Bound>
		{
			using type2 = T_Tuple_Method_Bound;


		};


		


	public:

		using type1 = S_Method_Bound<
			typename tuple_t<T_Fn_Parts...>::reverse::front>;

		

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