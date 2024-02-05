#pragma once

#include"Tuple_Declare.h"
#include"Tuple_Apply_Type.h"
#include"Tuple_Apply_Fn.h"
#include"Tuple_Apply_Array_Set.h"
#include"Tuple_Apply_Request.h"
#include"Tuple_Apply_Class_Create.h"
#include"Tuple_Infinite.h"

namespace N_Tuple::N_Apply
{


	template<class T_Expand, size_t t_point>
	struct S_Conversion_Expand;

	template<class T_Zip, size_t t_point>
	struct S_Conversion_Zip;


	//�d�l
	//��������^�̃��X�g����A�v������^�̃��X�g�ɁA�^�̓W�J�𔺂��ϊ����o���邩���肷��B
	//
	//�⑫
	// �^�̔���͌�납����{����B
	template<class T_Request_Types_Tuple,
		class T_Set_Types_Tuple>
	struct I_Apply_Type_Chack
	{

		//�d�l
		//�^�̔��肪�I������ۂɌĂяo�����
		template<class T_Request_Types_Tuple = invalid_t,
			class T_Conversion_Expand_List = tuple_t<>,
			class T_Conversion_Zip_List = tuple_t<>>
		struct S_Result
		{
			
			using request = T_Request_Types_Tuple;

			using conversion_expand_list = T_Conversion_Expand_List;

			using conversion_zip_list = T_Conversion_Zip_List;

		};


		template<class T_Request_Types_Tuple,
			class T_Set_Types_Tuple,
			class T_Conversion_Expand_List = tuple_t<>,
			class T_Conversion_Zip_List=tuple_t<>
		>
		struct S_Apply_Type_Chack
		{
			using type = S_Result<typename T_Request_Types_Tuple::reverse, T_Conversion_Expand_List, T_Conversion_Zip_List>;
		};


		template<class T_Request_Types_Tuple,
			class T_Set_Types_Tuple,
			class ...T_Conversion_Expand,
			class ...T_Conversion_Zip>
			requires requires
		{
			requires is_invalid_not<typename T_Request_Types_Tuple::type>;
			requires is_invalid_not<typename T_Set_Types_Tuple::type>;
		}
		struct S_Apply_Type_Chack<T_Request_Types_Tuple, T_Set_Types_Tuple, 
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
				U_Reverse<expand<typename T_Types_Tuple::type>>>;


			//�d�l
			// �v������^���X�g�Ƌ�������^���X�g�̐擪�̌^�ɑ΂��āA�ȉ��̔�������{����B
			// ����P�F��������^����A�v������^�ɕϊ��o���邩���肷��
			// ����Q�F����P�����s�����ꍇ�A������������̌^��W�J�o���邩���肷��
			// ����R�F����Q�����s�����ꍇ�A�v����������̌^��W�J�o���邩���肷��
			// ����R�����s�����ꍇ�A�G���[�Ƃ��Ė����l��Ԃ�
			template<bool t_constructible_from=convertible_to<set_t,request_t>,
				bool t_Request_Types_Expand = is_invalid_not<expand<request_t>>,
				bool t_Set_Types_Expand= is_invalid_not<expand<set_t>> >
			struct S_Apply_Control
			{
				//�G���[�̏ꍇ�͖����l��Ԃ�
				using type = S_Result<>;

			};

			//�d�l
			//��������^����A�v������^�ɕϊ��ł���ꍇ
			template<bool t_Request_Types_Expand, bool t_Set_Types_Expand>
			struct S_Apply_Control<true,t_Request_Types_Expand,t_Set_Types_Expand>
			{
				//�v������^�A��������^�̃��X�g�����ɐi�߁A���̌^�̔���Ɉڂ�B
				using type = S_Apply_Type_Chack<
					typename T_Request_Types_Tuple::remove,
					typename T_Set_Types_Tuple::remove,
					tuple_t<T_Conversion_Expand...>,
					tuple_t<T_Conversion_Zip...>
				>::type;

			};

			//�d�l
			//������������̌^��W�J�o����ꍇ
			template<bool t_Request_Types_Expand>
			struct S_Apply_Control<false, t_Request_Types_Expand, true>
			{

				//��������^��W�J���A
				// �W�J�����^�̏���ʓr�ۑ�����
				using type = S_Apply_Type_Chack<
					T_Request_Types_Tuple,
					select_type_expand<T_Set_Types_Tuple>,
					tuple_t<T_Conversion_Expand...,
						S_Conversion_Expand<set_t,T_Set_Types_Tuple::head_size>>,
					tuple_t<T_Conversion_Zip...>
					>::type;

			};

			//�d�l
			//�v����������̌^��W�J�o����ꍇ
			template<>
			struct S_Apply_Control<false, true, false>
			{
				//�v������^��W�J���A
				// �W�J�����^�̏���ʓr�ۑ�����
				using type =
					S_Apply_Type_Chack<
					select_type_expand<T_Request_Types_Tuple>,
					T_Set_Types_Tuple,
					tuple_t<T_Conversion_Expand...>,
					tuple_t<T_Conversion_Zip...,S_Conversion_Zip<request_t, T_Request_Types_Tuple::head_size>>
					>::type;
			};

			using type = S_Apply_Control<>::type;

		};

		//�^�̔���͌�납����{����ׁA
		//�^���X�g�̕��т𔽓]����
		using type = S_Apply_Type_Chack<
			typename T_Request_Types_Tuple::reverse,
			typename T_Set_Types_Tuple::reverse::create_p>::type;

		using conversion = type;

	};


}
