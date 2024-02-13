#pragma once

#include"Tuple_Declare.h"
#include"Tuple_Apply_Type.h"
#include"Tuple_Apply_Fn.h"
#include"Tuple_Apply_Array_Set.h"
#include"Tuple_Apply_Request.h"
#include"Tuple_Apply_Class_Create.h"
#include"Tuple_Infinite.h"
#include"If_Type.h"

namespace N_Tuple::N_Apply
{

	template<class T_Expand, size_t t_point>
	struct S_Conversion_Expand;

	template<class T_Zip, size_t t_point>
	struct S_Conversion_Zip;


	//�d�l
	//��������^�̃��X�g����A�v������^�̃��X�g�ɁA�^�̓W�J�𔺂��ϊ����o���邩���肵�A
	// ���̉ߒ��A���ʂ�Ԃ�
	// 
	// using 
	//[type::request]::��������^���X�g�Ƃ̏ƍ��̌��ʁA�g�p���Ȃ������v������^���X�g
	//[type::set]::�v������^���X�g�Ƃ̏ƍ��̌��ʁA�g�p���Ȃ�������������^���X�g
	//[type::conversion_expand_list]::��������^���X�g�̓W�J����
	//[type::conversion_zip_list]::��������^���X�g�̈��k����
	// 
	//�⑫
	// �^�̔���͌�납����{����B
	template<class T_Request_Types_Tuple,
		class T_Set_Types_Tuple>
	struct I_Convert_Order
	{

		//�d�l
		//�^�̔��肪�I������ۂɌĂяo�����
		template<class T_Request_Types_Tuple = invalid_t,
			class T_Set_Types_Tuple = invalid_t,
			class T_Conversion_Expand_List = tuple_t<>,
			class T_Conversion_Zip_List = tuple_t<>>
		struct S_Result
		{
			using type = S_Result;

			//��������^���X�g�Ƃ̏ƍ��̌��ʁA�g�p���Ȃ������v������^���X�g
			using request = T_Request_Types_Tuple;

			//�v������^���X�g�Ƃ̏ƍ��̌��ʁA�g�p���Ȃ�������������^���X�g
			using set = T_Set_Types_Tuple;

			//��������^���X�g�̓W�J����
			using conversion_expand_list = T_Conversion_Expand_List;

			//��������^���X�g�̈��k����
			using conversion_zip_list = T_Conversion_Zip_List;

		};


		template<class T_Request_Types_Tuple,
			class T_Set_Types_Tuple,
			class T_Conversion_Expand_List = tuple_t<>,
			class T_Conversion_Zip_List = tuple_t<>
		>
		struct S_Convert_Order
		{
			using type = S_Result<T_Request_Types_Tuple, T_Set_Types_Tuple, T_Conversion_Expand_List, T_Conversion_Zip_List>::type;
		};

		template<class T_Request_Types_Tuple,
			class T_Set_Types_Tuple,
			class ...T_Conversion_Expand,
			class ...T_Conversion_Zip>
			requires requires
		{
			requires same_as_not<tuple_t<>, T_Request_Types_Tuple>;
			requires same_as_not<tuple_t<>, T_Set_Types_Tuple>;
		}
		struct S_Convert_Order<T_Request_Types_Tuple, T_Set_Types_Tuple,
			tuple_t<T_Conversion_Expand...>,
			tuple_t<T_Conversion_Zip...>>
		{

			//�d�l
			//�v������^���X�g���I�����Ă���^
			using request_t = T_Request_Types_Tuple::type;

			//�d�l
			//��������^���X�g���I�����Ă���^
			using set_t = T_Set_Types_Tuple::type;

			//�d�l
			//�݊����̂���^�ɓW�J����
			// [using tuple}�ɂĒ�`�����^
			template<class T_Tuple>
			using expand = N_Tuple::S_Parameter<T_Tuple>::tuple;


			//�d�l
			//�I�𒆂̃^�C�v��W�J����
			template<class T_Types_Tuple>
			using select_type_expand = N_Tuple::U_Insert_tuple_expand<
				typename T_Types_Tuple::remove,
				expand<typename T_Types_Tuple::type>>;


			//�d�l
			// �v������^���X�g�Ƌ�������^���X�g�̐擪�̌^�ɑ΂��āA�ȉ��̔�������{����B
			// ����P�F��������^����A�v������^�ɕϊ��o���邩���肷��
			// ����Q�F����P�����s�����ꍇ�A������������̌^��W�J�o���邩���肷��
			// ����R�F����Q�����s�����ꍇ�A�v����������̌^��W�J�o���邩���肷��
			// ����R�����s�����ꍇ�A�G���[�Ƃ��Ė����l��Ԃ�
			template<
				class T_Request=typename T_Request_Types_Tuple::type,
				class T_Set = typename T_Set_Types_Tuple::type>
			struct S_Apply_Control
			{
				//�G���[�̏ꍇ�͖����l��Ԃ�
				using type = S_Result<T_Request_Types_Tuple, T_Set_Types_Tuple, tuple_t<T_Conversion_Expand...>, tuple_t<T_Conversion_Zip...>>::type;

			};

			//�d�l
			//��������^����A�v������^�ɕϊ��ł���ꍇ
			template<class T_Request,class T_Set>
				requires requires
			{
				requires convertible_to<T_Set, T_Request>;
			}
			struct S_Apply_Control< T_Request, T_Set>
			{
				//�v������^�A��������^�̃��X�g�����ɐi�߁A���̌^�̔���Ɉڂ�B
				using type = S_Convert_Order<
					typename T_Request_Types_Tuple::remove,
					typename T_Set_Types_Tuple::remove,
					tuple_t<T_Conversion_Expand...>,
					tuple_t<T_Conversion_Zip...>
				>::type;

			};

			//�d�l
			//������������̌^��W�J�o����ꍇ
			template<class T_Request, class T_Set>
				requires requires
			{
				requires !convertible_to<T_Set, T_Request>;
				requires is_invalid_not<expand<T_Set>>;
			}
			struct S_Apply_Control< T_Request, T_Set>
			{

				//��������^��W�J���A
				// �W�J�����^�̏���ʓr�ۑ�����
				using type = S_Convert_Order<
					T_Request_Types_Tuple,
					select_type_expand<T_Set_Types_Tuple>,
					tuple_t<T_Conversion_Expand..., S_Conversion_Expand<set_t, T_Set_Types_Tuple::size>>,
					tuple_t<T_Conversion_Zip...>
				>::type;

			};

			//�d�l
			//�v����������̌^��W�J�o����ꍇ
			template<class T_Request, class T_Set>
				requires requires
			{
				requires !convertible_to<T_Set, T_Request>;
				requires is_invalid_not<expand<T_Request>>;
				requires !is_invalid_not<expand<T_Set>>;
			}
			struct S_Apply_Control< T_Request, T_Set>
			{
				//�v������^��W�J���A
				// �W�J�����^�̏���ʓr�ۑ�����
				using type =
					S_Convert_Order<
					select_type_expand<T_Request_Types_Tuple>,
					T_Set_Types_Tuple,
					tuple_t<T_Conversion_Expand...>,
					tuple_t<S_Conversion_Zip<request_t, T_Request_Types_Tuple::size>, T_Conversion_Zip...>
					>::type;
			};


			using type = S_Apply_Control<>::type;

		};




		//�^�̔����O������{����
		using type = S_Convert_Order<
			T_Request_Types_Tuple,
			T_Set_Types_Tuple>::type;

	};



}
