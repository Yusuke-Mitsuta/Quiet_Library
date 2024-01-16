#pragma once

#include"Tuple.h"
#include"Concept.h"

template<is_invalid_not T_Front_Parts, class ...T_Parts>
class Function;

namespace N_Function
{
	template<class ...T_Parts>
	struct Function_Core;

	template<class ...T_Fn_Parts>
	struct I_Function_Helper;

	//�d�l
	//[T_Fn_Parts...]����A�֐��ɃA�N�Z�X����|�C���^�[�A�֐��I�u�W�F�N�g�A�o�C���h��������𕪕ʂ���
	//
	//�⑫
	//[Function]��[Function_Core]�ɕύX�����
	template<class ...T_Fn_Parts>
	struct I_Function_Base_Data
	{

		//�d�l
		//���݂��Ȃ��p�����[�^�̎Q�Ɛ�
		template<class ...T_Fn_Parts>
		struct S_Function_Data
		{
			using function = invalid_t;
			using bind_args = invalid_t;
			using pointer = invalid_t;
			using c_name = invalid_t;
			using r_type = invalid_t;

		};

		//�d�l
		//���ʂŎg�p����|�C���^�[�̌^���Z�b�g����
		//
		//�⑫
		//[T_Dedicated_Point]��[Function]�̏ꍇ�̓X�L�b�v����
		template<class T_Dedicated_Point, class ...T_Fn_Parts>
			requires requires
		{
			requires std::is_class_v<T_Dedicated_Point>;
			requires !same_as_template_type<T_Dedicated_Point, Function>;
		}
		struct S_Function_Data<T_Dedicated_Point*, T_Fn_Parts...> :
			S_Function_Data<T_Fn_Parts...>
		{
			using pointer = T_Dedicated_Point;
		};

		//�d�l
		//���ʂŎg�p����|�C���^�[�̌^���Z�b�g����
		//
		//�⑫
		//[T_Dedicated_Point]��[Function]�̏ꍇ�̓X�L�b�v����
		template<class T_Dedicated_Point, class ...T_Fn_Parts>
			requires requires
		{
			requires std::is_class_v<T_Dedicated_Point>;
			requires !same_as_template_type<T_Dedicated_Point, Function>;
		}
		struct S_Function_Data<T_Dedicated_Point*&, T_Fn_Parts...> :
			S_Function_Data<T_Fn_Parts...>
		{
			using pointer = T_Dedicated_Point;
		};


		//�d�l
		//�����̌^���Z�b�g����
		template<class T_Fn, class ...T_Bind_Args>
		struct S_Function_Data<T_Fn, T_Bind_Args...> :
			S_Function_Data<T_Fn>
		{
			using bind_args = tuple_t<T_Bind_Args...>;
		};


		//�d�l
		//�N���X���\�b�h�̌^����A�e��p�����[�^���Z�b�g����
		template<class T_CName, class T_RType, class ...T_Args>
		struct S_Function_Data<T_RType(T_CName::*)(T_Args...)> :
			S_Function_Data<>
		{
			using function = T_RType(T_CName::*)(T_Args...);

			using c_name = T_CName;

			using r_type = T_RType;
		};

		//�d�l
		//�֐��̌^����A�e��p�����[�^���Z�b�g����
		template<class T_RType, class ...T_Args>
		struct S_Function_Data<T_RType(*)(T_Args...)> :
			S_Function_Data<>
		{
			using function = T_RType(*)(T_Args...);

			using r_type = T_RType;
		};


		//�d�l
		//[Function]����[Function]��[Function_Core]�ɕύX���A
		// �����̊֐���1����[Function_Core]�ɕ��ʂ�[tuple_t]�œZ�߁A�ēxfunction�̔�����s��
		template<class ...T_Parts>
		struct S_Function_Data<Function<T_Parts...>> :
			S_Function_Data<typename I_Function_Helper<T_Parts...>::type>
		{};


		//�d�l
		//[Function]�̃|�C���^�[���O���A
		// �ēx�Afunction�̔�����s��
		template<class ...T_Parts>
		struct S_Function_Data<Function<T_Parts...>*> :
			S_Function_Data<Function<T_Parts...>>
		{};

		//�d�l
		//[Function]�̎Q�Ƃ��O���A
		// �ēx�Afunction�̔�����s��
		template<class ...T_Parts>
		struct S_Function_Data<Function<T_Parts...>&> :
			S_Function_Data<Function<T_Parts...>>
		{};

		//�d�l
		//�e�ƂȂ�֐��I�u�W�F�N�g�̌^���Z�b�g����
		template<class ...T_Parts>
		struct S_Function_Data<Function_Core<T_Parts...>> :
			S_Function_Data<>
		{
			using function = Function_Core<T_Parts...>;
		};

		//�d�l
		//�e�ƂȂ�֐��I�u�W�F�N�g���������݂���ꍇ�Atuple_t�œZ�߂ăZ�b�g����
		template<class ...T_Fns>
		struct S_Function_Data<tuple_t<T_Fns...>> :
			S_Function_Data<>
		{
			using function = tuple_t<T_Fns...>;
		};

		//�d�l
		//�e�ƂȂ�֐��I�u�W�F�N�g�̌^���Z�b�g����
		template<class T_Fn>
		struct S_Function_Data<tuple_t<T_Fn>> :
			S_Function_Data<>
		{
			using function = T_Fn;
		};

		//�d�l
		//�Q�Ƃ��t���Ă���ꍇ�A�Q�Ƃ��O���Ĕ�������{����
		template<class T_Fn>
		struct S_Function_Data<T_Fn&> :
			S_Function_Data<T_Fn>
		{};

		//�d�l
		//�֐��I�u�W�F�N�g�̌^�łȂ��ꍇ�A�Z�b�g���Ȃ�
		template<class T_Fn>
		struct S_Function_Data<T_Fn> :
			S_Function_Data<>
		{};

	public:

		using type = S_Function_Data<T_Fn_Parts...>;

	protected:

		//�d�l
		//[T_Fn_Parts...]�������������ʂ�[Function_Core]���o�͂���
		struct I_Core_Molding
		{
			template<class T_Core, class T_Add>
			struct S_Add_p
			{
				using type = T_Core;
			};

			template<class ...T_Parts, is_invalid_not T_Add>
			struct S_Add_p<Function_Core<T_Parts...>, T_Add>
			{
				using type = Function_Core<T_Add*, T_Parts...>;
			};

			template<class T_Core, class T_Add>
			struct S_Add_fn
			{
				using type = T_Core;
			};

			template<class ...T_Parts, is_invalid_not T_Add>
			struct S_Add_fn<Function_Core<T_Parts...>, T_Add>
			{
				using type = Function_Core<T_Add, T_Parts...>;
			};

			template<class T_Bind_Args = typename type::bind_args>
			struct S_Add_bind_args
			{
				using type = Function_Core<>;
			};

			template<class ...T_Bind_Args >
			struct S_Add_bind_args<tuple_t<T_Bind_Args...>>
			{
				using type = Function_Core<T_Bind_Args...>;
			};

			using type = S_Add_p<typename S_Add_fn<typename S_Add_bind_args<>::type,
				typename type::function>::type, typename type::pointer>::type;

		};

	public:

		using core = I_Core_Molding::type;

	};

}

