#pragma once

#include"Tuple.h"
#include"SwapType.h"
#include"Select_Type.h"
#include"Function_Single_Data.h"


namespace N_Function
{

	
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


		template<class T_Tuple, bool t_function_check_fg, bool t_method_check_fg, 
			class T_Tuple_Method_Bound = tuple_t<>,
			class T_Tuple_Access_Number = tuple_t<>>
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
				

				template<class T_Tuple,class T_Method,class T_Access_Number>
				using Method_Bound =typename S_Method_Bound<typename T_Tuple::next,t_function_check_fg,t_method_check_fg,
					N_Tuple::U_Insert<T_Tuple_Method_Bound,T_Method>,
					N_Tuple::U_Insert<T_Tuple_Access_Number, T_Access_Number>
				>::type;

				//�d�l
				//�֐��ɑ΂��ẮA�w�肳�ꂽ�����̌^���󂯎�邩���肷��A
				//���\�b�h�ɑ΂��ẮA�w�肳�ꂽ�����̌^�ƁA�N���X�|�C���^�[���󂯎�邩���肷��A
				// 
				// �e���v���[�g
				//[T_Function_Check]:�w�肳�ꂽ�����̌^���󂯎�邩���肷��
				//[T_Dedicated_Point_Check]:�w�肳�ꂽ�����̌^�ƁA�֐��̎��ɐݒ肳��Ă���|�C���^�[�𔻒肷��
				//[T_Commond_Point_Check]:�w�肳�ꂽ�����̌^�ƁA���ʂŐݒ肳�ꂽ�|�C���^�[�𔻒肷��
				//[T_Method_Check]:�w�肳�ꂽ�����̌^���󂯎�邩���肷��
				template<class T_Function_Check = typename I_Function_Single_Data<chack_tuple<T_Method_Point>>::function,
						 class T_Dedicated_Point_Check = typename I_Function_Single_Data<chack_tuple<typename T_Method_Point::next>>::function,
						 class T_Commond_Point_Check = typename I_Function_Single_Data<N_Tuple::U_Insert<chack_tuple<T_Method_Point>,commond_point,0>>::function
				
				>
				struct S_Callable_Check
				{

					using type = Method_Bound<T_Method_Point,T_Function_Check
						,access_numbers<T_Method_Point>>;
				};	

				//�d�l
				//�w�肳�ꂽ�����̌^���󂯎�邩���肷��
				template<class ...T_Function_Check,class ...T_Dedicated_Point_Check, class T_Commond_Point_Check>
				struct S_Callable_Check<Method_Core<T_Function_Check...>,Function_Core<T_Dedicated_Point_Check...>, T_Commond_Point_Check>
				{
					using type = 
						Method_Bound<typename T_Method_Point::next, Function_Core<T_Dedicated_Point_Check...>,
						access_numbers<typename T_Method_Point::next>>;
				};

				//�d�l
				//�w�肳�ꂽ�����̌^�ƁA���ʂŐݒ肳�ꂽ�|�C���^�[�𔻒肷��
				template<class ...T_Function_Check, class ...T_Dedicated_Point_Check, class ...T_Commond_Point_Check>
				struct S_Callable_Check<Method_Core<T_Function_Check...>, Method_Core<T_Dedicated_Point_Check...>,Function_Core<T_Commond_Point_Check...>>
				{
					using type = Method_Bound<T_Method_Point, Function_Core<

						T_Commond_Point_Check...>,access_numbers<T_Method_Point>>;
				};


				//�d�l
				//�֐��ɑ΂��āA�����̂��s��v�ȏꍇ�A���̊֐���T������
				template<>
				struct S_Callable_Check<invalid_t, invalid_t, invalid_t>
				{
					using type = S_Method_Point<typename S_Method_Search<typename T_Method_Point::next>::type>::type;
				};


				using type = U_if_t1<S_Callable_Check<>, S_Callable_Check<invalid_t,invalid_t,invalid_t>,t_function_check_fg>::type;

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
		template<class T_Head,class T_Tail, bool t_function_check_fg, bool t_method_check_fg,class T_Tuple_Method_Bound, class T_Tuple_Access_Number>
		struct S_Method_Bound<tuple_tp<T_Head,invalid_t,T_Tail>, t_function_check_fg,t_method_check_fg, T_Tuple_Method_Bound,T_Tuple_Access_Number>
		{
			using type = tuple_t<T_Tuple_Method_Bound, T_Tuple_Access_Number>;


		};

		using start_tuple = typename tuple_t<T_Fn_Parts...>::reverse::front;

	public:

		//�d�l
		//�t�@���N�V�����Ƃ��Ĕ��肵�A���s����΁A���\�b�h�Ƃ��Ĕ��肷��
		using type = S_Method_Bound<start_tuple,true,true>::type;
		
		//�d�l
		//�t�@���N�V�����Ƃ��Ĕ��肷��
		using function_check= S_Method_Bound<start_tuple, true, false>::type;

		//�d�l
		//���\�b�h�Ƃ��Ĕ��肷��
		using method_check = S_Method_Bound<start_tuple, false, true>::type;

	};

}