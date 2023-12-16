#pragma once

#include"Tuple.h"
#include"SwapType.h"
#include"Select_Type.h"
#include"Function_Single_Data.h"


namespace N_Function
{
	template<class ...T_Fn_Parts>
	struct I_Function_Single_Helper;
	
	//�d�l
	//�֐��ɑ΂��āA���̊֐����̓��\�b�h���o�Ă���܂ł̊Ԃ̌^�������̌^�ƌ݊��������邩���肷��
	//���\�b�h�ɑ΂��ẮA��L�ɉ����A���\�b�h�̑O�̌^���|�C���^�[�̌^�ƌ݊��������邩���肵�A
	//	���s����΁A�e���v���[�g�̐擪�̌^���|�C���^�[�̌^�ƌ݊��������邩���肷��
	//���̑�����J��Ԃ��A�S�Đ�������΁A�֐��A���\�b�h�I�u�W�F�N�g���ɓZ�߂�ꂽ��A[tuple_t]�ɓZ�߂���B
	//
	//�e���v���[�g
	//[T_Fn_Parts...]:
	//	���\�b�h�Ɏg�p���鋤�ʂ̃|�C���^�[�̌^(�ȗ��\)
	//	�֐��A���̓��\�b�h�̌^
	//	����ɑ΂�������̌^(���т̈�Ԍ��̌^���A�֐��̈����^�̈�Ԍ��Ɣ��肳���)
	//	���̃��\�b�h�ɑ΂����p�̃|�C���^�[�̌^(���Ƀ��\�b�h���g�p����ꍇ)
	//	�֐��A���̓��\�b�h�̌^
	// �Ƒ���
	// 
	//�⑫
	//�֐��ɑ΂�������̌^�Ƃ��Ċ֐��̌^�����ꍇ
	//���̊Ԃ̌^�ƈ����̌^�Ɍ݊���������΁A�����Ƃ��Ď�낤�Ƃ��Ă�֐��̌^�����̊֐��Ƃ��Č��Ȃ����ׁA
	//	�P�̂̊֐��Ƃ��ď��������鎖
	template<class ...T_Fn_Parts>
	struct I_Function_Multiple_Helper
	{
	private:
		

		using commond_point = std::tuple_element_t<0, tuple_t<T_Fn_Parts...>>;


		template<class T_Tuple, class T_method = typename I_Function_Single_Data<typename T_Tuple::type>::function>
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


		template<class T_Tuple,
			class T_Tuple_Method_Bound = tuple_t<>>
		struct S_Method_Bound
		{


			template<class T_Method_Point = typename S_Method_Search<T_Tuple>::type>
			struct S_Method_Point
			{


				template<class T_Method_Point>
				using chack_tuple = typename
					N_Tuple::U_Range<T_Tuple, T_Method_Point::head_size - (T_Method_Point::head_size == T_Method_Point::size)>::reverse;

				template<class T_Method_Point>
				using access_numbers =
					N_Tuple::U_range_index_sequence<T_Method_Point::tail_size, T_Tuple::tail_size+1>;
				
				template<class T_Tuple,class T_Method,class T_access_numbers>
				using Method_Bound =typename S_Method_Bound<typename T_Tuple::next,
					N_Tuple::U_Insert<T_Tuple_Method_Bound,T_Method>>::type;

				//�d�l
				//�w�肳�ꂽ�|�C���^�[�����K�v�����肷��B
				// 
				// �e���v���[�g
				//[T_Function]:������Bind���ꂽ�֐��I�u�W�F�N�g
				//[T_Dedicated_Point_Check]:�w�肳�ꂽ�����̌^�ƁA�֐��̎��ɐݒ肳��Ă���|�C���^�[�𔻒肷��
				//[T_Commond_Point_Check]:�w�肳�ꂽ�����̌^�ƁA���ʂŐݒ肳�ꂽ�|�C���^�[�𔻒肷��
				//[T_Method_Check]:�w�肳�ꂽ�����̌^���󂯎�邩���肷��
				template<class T_Function,
					class T_Dedicated_Point_Check = typename I_Function_Single_Data<chack_tuple<typename T_Method_Point::next>>::type,
					class T_Commond_Point_Check = typename I_Function_Single_Data<N_Tuple::U_Insert<chack_tuple<T_Method_Point>, commond_point, 0>>::type
				>
				struct S_Pointer_Chack
				{
					using type = 
						Method_Bound<T_Method_Point,
						T_Function, access_numbers<T_Method_Point>>;
				};

				//�d�l
				//��p�Őݒ肳�ꂽ�|�C���^�[�𔻒肷��
				template<class ...T_Parts,class T_Dedicated_Point_Check, class T_Commond_Point_Check>
					requires ((std::is_pointer_v<typename T_Method_Point::next_t>) &&
					(not_same_as<typename  Function_Core<T_Parts...>::request_pointer, typename T_Dedicated_Point_Check::request_pointer>))
				struct S_Pointer_Chack<Function_Core<T_Parts...>, T_Dedicated_Point_Check, T_Commond_Point_Check>
				{
					using type =
						Method_Bound<typename T_Method_Point::next,
						T_Dedicated_Point_Check,
						access_numbers<typename T_Method_Point::next>>;

				};

				//�d�l
				//���ʂŐݒ肳�ꂽ�|�C���^�[�𔻒肷��
					template<class ...T_Parts, class T_Dedicated_Point_Check, class T_Commond_Point_Check>
						requires ((std::is_pointer_v<commond_point>) &&
					((same_as<T_Dedicated_Point_Check,Function_Core<>>) ||
					 (same_as<typename  Function_Core<T_Parts...>::request_pointer, typename T_Dedicated_Point_Check::request_pointer>)) &&
				 (not_same_as<typename Function_Core<T_Parts...>::request_pointer, typename T_Commond_Point_Check::request_pointer>))
				struct S_Pointer_Chack<Function_Core<T_Parts...>, T_Dedicated_Point_Check ,T_Commond_Point_Check>
				{
					using type = Method_Bound<T_Method_Point,
						T_Commond_Point_Check, 
						access_numbers<T_Method_Point>>;
				};

				//�d�l
				//�֐��ɑ΂��ẮA�w�肳�ꂽ�����̌^���󂯎�邩���肷��
				// 
				// �e���v���[�g
				//[T_Function_Check]:�w�肳�ꂽ�����̌^���󂯎�邩���肷��
				template<class T_Fn = typename I_Function_Single_Data<chack_tuple<T_Method_Point>>::type,
					class T_Args_chack =typename T_Fn::request_args>
				struct S_Callable_Check
				{
					using type = S_Pointer_Chack<T_Fn>::type;
				};


				//�d�l
				//�֐��ɑ΂��āA�����̂��s��v�ȏꍇ�A���̊֐���T������
				template<class T_Fn>
				struct S_Callable_Check<T_Fn,invalid_t>
				{
					using type = S_Method_Point<typename S_Method_Search<typename T_Method_Point::next>::type>::type;
				};


				using type = S_Callable_Check<>::type;

			};

			//�d�l
			//�֐��ɑ΂��āA�����̌^���s��v�ł���A�S�Ă̒T�����I������ꍇ
			template<class T_Head>
			struct S_Method_Point<tuple_tp<T_Head,invalid_t,tuple_t<>>>
			{
				using type = invalid_t;
			};

			using type = S_Method_Point<>::type;

		};

		//�d�l
		//�S�Ă̌^�̒T��������ɏI�������ꍇ�A���ʂ��o�͂���
		template<class T_Head,class T_Tail,class T_Fns>
		struct S_Method_Bound<tuple_tp<T_Head,invalid_t,T_Tail>,T_Fns>
		{
			using type = T_Fns;
		};


		using start_tuple = typename tuple_t<T_Fn_Parts...>::reverse::front;

	public:

		//�d�l
		//�t�@���N�V�����Ƃ��Ĕ��肵�A���s����΁A���\�b�h�Ƃ��Ĕ��肷��
		using type = S_Method_Bound<start_tuple>::type;
		

	};


}