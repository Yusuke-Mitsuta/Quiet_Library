#pragma once

#include"Tuple.h"
#include"SwapType.h"
#include"Select_Type.h"

namespace N_Function
{
	template<class ...T_Parts>
	struct Function_Core;
	
	//�d�l
	//�֐��ɑ΂��āA���̊֐��I�u�W�F�N�g���o�Ă���܂ł̊Ԃ̌^�������̌^�ƌ݊��������邩���肷��
	//���\�b�h�ɑ΂��ẮA��L�ɉ����A���\�b�h�̑O�̌^���|�C���^�[�̌^�ƌ݊��������邩���肵�A
	//	���s����΁A�e���v���[�g�̐擪�̌^���|�C���^�[�̌^�ƌ݊��������邩���肷��
	//���̑�����J��Ԃ��A�S�Đ�������΁A[Function_Core]���ɓZ�߂�ꂽ��A[tuple_t]�ɓZ�߂���B
	//
	//�e���v���[�g
	//[T_Fn_Parts...]:
	//	���\�b�h�Ɏg�p���鋤�ʂ̃|�C���^�[�̌^(�ȗ��\)
	//	�֐��I�u�W�F�N�g�̌^
	//	����ɑ΂�������̌^(���т̈�Ԍ��̌^���A�֐��̈����^�̈�Ԍ��Ɣ��肳���)
	//	���̃��\�b�h�ɑ΂����p�̃|�C���^�[�̌^(���Ƀ��\�b�h���g�p����ꍇ)
	//	�֐��I�u�W�F�N�g�̌^
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
		
		using front_t = std::tuple_element_t<0, tuple_t<T_Fn_Parts...>>;

		template<class T_Tuple, class T_method = typename Function_Core<typename T_Tuple::type>::function>
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


		template<class T_Tuple_Method_Bound,class T_Tuple_Access_Number>
		struct S_Result;

		template<class T_Tuple,
			class T_Tuple_Method_Bound = tuple_t<>,
			class T_Tuple_Access_Number = tuple_t<>>
		struct S_Method_Bound
		{


			template<class T_Method_Point = typename S_Method_Search<T_Tuple>::type>
			struct S_Method_Point
			{

				template<class T_Method_Point>
				using chack_Data = typename
					N_Tuple::U_Range<T_Tuple, T_Method_Point::head_size - (T_Method_Point::head_size == T_Method_Point::size)>::reverse;

				template<class T_Method_Point>
				using access_numbers =
					N_Tuple::U_range_index_sequence<T_Method_Point::tail_size, T_Tuple::tail_size+1>;
				
				template<class T_Tuple,class T_Method,class T_access_numbers>
				using Method_Bound =typename S_Method_Bound<typename T_Tuple::next,
					N_Tuple::U_Insert<T_Tuple_Method_Bound,typename T_Method::type>,
					N_Tuple::U_Insert<T_Tuple_Access_Number,T_access_numbers>>::type;

				template<class T_Tuple>
				using Function_Data = 
					typename N_Tuple::I_Expand_Set<Function_Core,T_Tuple>::type;


				//�d�l
				//�w�肳�ꂽ�|�C���^�[�����K�v�����肷��B
				// 
				// �e���v���[�g
				//[T_Function]:������Bind���ꂽ�֐��I�u�W�F�N�g
				//[T_Dedicated_Point_Check]:�w�肳�ꂽ�����̌^�ƁA�֐��̎��ɐݒ肳��Ă���|�C���^�[�𔻒肷��
				//[T_Commond_Point_Check]:�w�肳�ꂽ�����̌^�ƁA���ʂŐݒ肳�ꂽ�|�C���^�[�𔻒肷��
				//[T_Method_Check]:�w�肳�ꂽ�����̌^���󂯎�邩���肷��
				template<class T_Function = Function_Data<chack_Data<T_Method_Point>>,
					class T_Dedicated_Point_Check = Function_Data<chack_Data<typename T_Method_Point::next>>,
					class T_Commond_Point_Check = Function_Data<N_Tuple::U_Insert<typename chack_Data<T_Method_Point>::front, front_t>>>
				struct S_Pointer_Chack
				{
					using type = 
						Method_Bound<T_Method_Point,
						T_Function, access_numbers<T_Method_Point>>;
				};

				//�d�l
				//��p�Őݒ肳�ꂽ�|�C���^�[�𔻒肷��
				template<class ...T_Parts,class T_Dedicated_Point_Check, class T_Commond_Point_Check>
					requires ((std::is_pointer_v<std::remove_reference_t<typename T_Method_Point::next_t>>) &&
					(not_same_as<typename  Function_Core<T_Parts...>::request_pointer, typename T_Dedicated_Point_Check::request_pointer>))
				struct S_Pointer_Chack<Function_Core<T_Parts...>,T_Dedicated_Point_Check, T_Commond_Point_Check>
				{
					using type =
						Method_Bound<typename T_Method_Point::next,
						T_Dedicated_Point_Check,
						access_numbers<typename T_Method_Point::next>>;

				};

				//�d�l
				//���ʂŐݒ肳�ꂽ�|�C���^�[�𔻒肷��
					template<class ...T_Parts, class T_Dedicated_Point_Check, class T_Commond_Point_Check>
						requires ((std::is_pointer_v<std::remove_reference_t<front_t>>) &&
					((is_invalid<typename T_Dedicated_Point_Check::function>) ||
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
				template<class T_Args_chack =typename Function_Data<chack_Data<T_Method_Point>>::request_args>
				struct S_Callable_Check
				{
					using type = S_Pointer_Chack<>::type;
				};


				//�d�l
				//�֐��ɑ΂��āA�����̂��s��v�ȏꍇ�A���̊֐���T������
				template<>
				struct S_Callable_Check<invalid_t>
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
				using type = S_Result<invalid_t, invalid_t>;
			};

			using type = S_Method_Point<>::type;

		};


		//�d�l
		//�S�Ă̌^�̒T��������ɏI�������ꍇ�A���ʂ��o�͂���
		template<class T_Head,class T_Tail,class T_Fns, class T_Tuple_Access_Number>
		struct S_Method_Bound<tuple_tp<T_Head,invalid_t,T_Tail>,T_Fns, T_Tuple_Access_Number>
		{
			using type = S_Result<T_Fns, T_Tuple_Access_Number>;
		};

		//�d�l
		//���ʂ�Ԃ��N���X
		//
		//�e���v���[�g
		//[T_Tuple_Method_Bound]::[Function_Core]���Z�߂�ꂽ[tuple_t]
		//[T_Tuple_Access_Number]::�Z�߂�ꂽ�֐��I�u�W�F�N�g��ɑ΂��āA�g�p�����^�̔ԍ������Z�߂�ꂽ[tupel_t]
		template<class T_Tuple_Method_Bound, class T_Tuple_Access_Number>
		struct S_Result
		{
			using type = T_Tuple_Method_Bound;

			using access_number = T_Tuple_Access_Number;

		};

		using start_tuple = typename tuple_t<T_Fn_Parts...>::reverse::front;

		using result = S_Method_Bound<start_tuple>::type;

	public:

		//�d�l
		//[Function_Core]���Z�߂�ꂽ[tuple_t]
		using type = result::type;

		//�d�l
		//�Z�߂�ꂽ�֐��I�u�W�F�N�g���ɑΉ������A�g�p�����^�̔ԍ������Z�߂�ꂽ[tupel_t]
		using access_number = result::access_number;

		//�d�l
		//�Z�ߍ�Ƃ���������΁A[T_Fn_Parts...]�̐擪�̌^���A���s����΁A[invalid_t]��Ԃ�
		using judge = U_Judge_t<front_t, not_is_invalid<type>>;
	};


}