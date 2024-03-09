/*!
 * Tuple_Apply_Type_Chack.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Tuple_Declare.h"
#include"Tuple_Apply_Type.h"
#include"Tuple_Apply_Fn.h"
#include"Tuple_Apply_Array_Set.h"
#include"Tuple_Apply_Request.h"
#include"Tuple_Apply_Class_Create.h"
#include"Tuple_Infinite.h"
#include"SwapType.h"

namespace quiet::N_Tuple::N_Apply
{

	template<class T_Expand, size_t t_point>
	struct S_Conversion_Expand;

	template<class T_Zip, size_t t_point>
	struct S_Conversion_Zip;

	//�d�l
	//��������^�̃��X�g����A�v������^�̃��X�g�ɁA�^�̓W�J�𔺂��ϊ����o���邩���肷��B
	//
	//�e���v���[�g
	//[T_Result_Request_Types_Tuple]::[tuple_t<...>]�Œ�`���ꂽ�v������^���X�g
	//[T_Result_Set_Types_Tuple]::[tuple_t<...>]�Œ�`���ꂽ��������^���X�g
	// 
	//�ϐ�
	//[value]::����̌���
	//	[ value < 0 ] -> �ϊ����s
	//	[ value == 0 ] -> �ϊ�����
	//	[ value >= 0 ] -> �ϊ������̏�A�ϒ������̐���Ԃ�
	// 
	//�⑫
	//��������^���X�g�ɉϒ��������`�����
	// [N_Tuple::N_Apply::S_Infinite_Args< T_Request_Order >]�����X�g�̍Ō�ɒ�`���鎖�B
	template<class T_Request_Types_Tuple,
		class T_Set_Types_Tuple>
	struct I_Type_Chack
	{
	private:
		using request_expand = U_Expand_All<T_Request_Types_Tuple>;

		using set_expand = U_Expand_All<T_Set_Types_Tuple>;

		//�d�l
		//[T_Result_Request_Types_Tuple,T_Result_Set_Types_Tuple]���X�g����[tuple]�ƌ݊���������^��S�ēW�J���A
		// �^�̌݊��������邩���肷��
		// 
		//�e���v���[�g
		//[T_Expand_Number]::[T_Result_Request_Types_Tuple]��W�J�����ۂ̗v�f�ɑΉ�����
		// �ԍ��̃��X�g
		// ��std::index_sequence< �v�f�� >�̒��g��[tuple_v]�Œ�`�����^
		// 
		//�⑫
		//��������^���X�g�ɉϒ��������`����Ă���ꍇ�A
		// �ϒ��������������^�𔻒肵�A�ϒ������̔���Ɉڍs����
		template<class T_Expand_Number =
			U_index_sequence<request_expand::size - is_Infinite_Args<typename T_Request_Types_Tuple::back_t>>>
		struct S_Type_Chack
		{
			using type = S_Type_Chack;
			static constexpr int value = -1;
		};
		
		//�d�l
		//�ϒ���������`����Ė����A�^���X�g���m�̔��肪�����̏ꍇ
		template<size_t ...t_Expand_Number>
			requires ((convertible_to<
				U_Element_t<t_Expand_Number, set_expand>,
				U_Element_t<t_Expand_Number, request_expand>> && ...) &&
				(request_expand::size == sizeof...(t_Expand_Number)) &&
				(set_expand::size== sizeof...(t_Expand_Number)))
		struct S_Type_Chack<tuple_v<t_Expand_Number...>>
		{
			using type = S_Type_Chack;
			static constexpr int value = 0;
		};
		
		//�d�l
		//�ϒ���������`����Ă邩�A�ϒ������̒�`���������^���X�g���m�̔��肪�����̏ꍇ
		template<size_t ...t_Expand_Number>
			requires ((convertible_to<
				U_Element_t<t_Expand_Number, set_expand>,
				U_Element_t<t_Expand_Number, request_expand>> && ...) &&
				(request_expand::size != sizeof...(t_Expand_Number)) &&
				(set_expand::size >= sizeof...(t_Expand_Number)))
		struct S_Type_Chack<tuple_v<t_Expand_Number...>>
		{
			//�ϒ���������`����Ă���^�ɑ΂��āA[tuple]�ƌ݊���������^��S�ēW�J�����^
			using infinite_args_expand = U_Expand_All<typename T_Request_Types_Tuple::back_t::constructor_args>;

			//�ϒ������������Ĕ�������{�����^�����O
			using set_expand_rest = U_Range<set_expand, sizeof...(t_Expand_Number), set_expand::size>;

			//[infinite_args_expand]�̗v�f���ɑΉ�����^�̔ԍ����X�g
			using infinite_args_expand_number = U_index_sequence<infinite_args_expand::size>;

			
			//�d�l
			//[infinite_args_expand]��
			// [set_expand_rest]��
			// �@[t_infinite_args_Num * infinite_args_expand::size ]�Ԗڂ����
			//	 [infinite_args_expand::size]�������肷��
			// 
			//�⑫
			// ���肪���������[t_infinite_args_Num]����i�߁A�ēx��������{����
			// �Ō�܂Ŕ��肪��������΁A�K�v�ȉϒ������̐��Ƃ��āA[t_infinite_args_Num]���o�͂���B
			template<class T_Infinite_Args_Expand_Number, size_t t_infinite_args_Num = 0>
			struct S_Infinite_Args_Chack
			{
				using type = S_Infinite_Args_Chack;
				static constexpr int value = -1;
			};

			template<size_t ...t_Infinite_Args_Expand_Number, size_t t_infinite_args_Num>
				requires (convertible_to<
					U_Element_t<t_Infinite_Args_Expand_Number + (infinite_args_expand::size *t_infinite_args_Num), set_expand_rest>,
					U_Element_t<t_Infinite_Args_Expand_Number, infinite_args_expand>> && ...)
			struct S_Infinite_Args_Chack<tuple_v<t_Infinite_Args_Expand_Number...>, t_infinite_args_Num>
			{

				using type = S_Infinite_Args_Chack<
					tuple_v<t_Infinite_Args_Expand_Number...>, t_infinite_args_Num + 1>::type;
			};

			template<class T_Infinite_Args_Expand_Number,size_t t_infinite_args_Num>
				requires (infinite_args_expand_number::size* t_infinite_args_Num == set_expand_rest::size)
			struct S_Infinite_Args_Chack<T_Infinite_Args_Expand_Number, t_infinite_args_Num>
			{
				using type = S_Infinite_Args_Chack;
				static constexpr int value = t_infinite_args_Num;

			};

			//�d�l
			//�c���Ă���^�̌^[set_expand_rest::size]��
			// �ϒ��������v������^�̐�[infinite_args_expand::size]�Ŋ���؂邩���肷��
			//
			//�⑫
			// ����؂��ꍇ�A�^�̔���Ɉڍs����
			// ����؂�Ȃ��ꍇ�́A���莸�s�ɂȂ�
			template<bool t_size_chack
				= !static_cast<bool>(set_expand_rest::size % infinite_args_expand::size)>
			struct S_Infinite_Args_Size_Chack
			{
				using type =S_Infinite_Args_Size_Chack;
				static constexpr int value = -1;
			};

			template<>
			struct S_Infinite_Args_Size_Chack<true>
			{
				using type = S_Infinite_Args_Chack<infinite_args_expand_number>::type;
			};

			using type = S_Infinite_Args_Size_Chack<>::type;

		};
	public:

		using type = S_Type_Chack<>::type;

		static constexpr int value = type::value;

	};

	//�d�l
	//��������^���X�g����A�v������^���X�g�ɒ�`����Ă���ϒ������̗v�f��������o���A
	//�ϒ������Ɠ����̌^�ɒu��������B
	//
	// �⑫
	// �ϒ�������[N_Tuple::N_Apply::S_Infinite_Args< T_Request_Order >]�^�ł���A
	// ���X�g�̍Ō�ɒ�`�����B
	template<class T_Request_Types_Tuple,
		class T_Set_Types_Tuple>
	struct S_Infinite_Args_Conversion
	{
		using type = T_Request_Types_Tuple;
	};


	template<class T_Request_Types_Tuple,
		class T_Set_Types_Tuple>
		requires requires
	{
		requires is_Infinite_Args<typename T_Request_Types_Tuple::back_t>;
		requires I_Type_Chack<T_Request_Types_Tuple, T_Set_Types_Tuple>::value >= 0;
	}
	struct S_Infinite_Args_Conversion< T_Request_Types_Tuple, T_Set_Types_Tuple>
	{
		using type =
			U_Merge_tuple_expand<
			typename T_Request_Types_Tuple::back::remove,
			U_Repeat_Multiple<
				typename T_Request_Types_Tuple::back_t::type,
				I_Type_Chack<T_Request_Types_Tuple, T_Set_Types_Tuple>::value>
			>::remove_p;

	};


}