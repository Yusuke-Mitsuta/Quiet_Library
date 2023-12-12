#pragma once

#include"Function_Core.h"
#include"Tuple.h"
#include"Concept.h"
#include"Function_Core_Request.h"


template<not_is_invalid T_Fns>
class Function;


namespace N_Function
{
	template<class T_Request_Args, class T_Request_Pointer>
	struct Request_Core;

	template<class T_Fn_Data>
	struct I_Request;

	template<class T_Request_Args, class T_Bind_Args>
	struct S_Request_args;	

	template<class T_Request_pointer, class T_Pointer, bool t_judge >
	struct S_Request_pointer;

	//�d�l
	//�֐��I�u�W�F�N�g�̌^�ɑ΂��āA���������̌^���L�������肷��B
	//
	//�e���v���[�g
	//[T_Fn_Parts...]::
	// �������͑������̌Ăяo���Ɏg�p����N���X�|�C���^�[�̌^�ł���B�N���X�|�C���^�[�̌^�𔻒肵�Ȃ��ꍇ�͎w��s�v�ł���B�ÓI���\�b�h�A�N���X�|�C���^�[�̌^���w��ς݁A�̏ꍇ�͎w��s�ł���B
	// �������͊֐��̌^�A�Ⴕ���́A������bind�����^[Function_Core],[Method_Core]�Ƃ���
	// ��O�����ȍ~�́A�������̊֐��I�u�W�F�N�g�̈����Ɏw�肷��^���X�g
	template<class ...T_Fn_Parts>
	struct I_Function_Single_Data
	{

		//�d�l
		//�֐��I�u�W�F�N�g��[T_Fn_Parts...]���ɑ��݂��Ȃ��ꍇ
		template<class ...T_Fn_Parts>
		struct S_Function_Data
		{
			using function = invalid_t;
			using bind_args = invalid_t;
			using pointer = invalid_t;
			using c_name = invalid_t;
			using request = Request_Core<invalid_t,invalid_t>;
			using r_type = invalid_t;

		};

		//�d�l
		//���ʂŎg�p����|�C���^�[�̌^���Z�b�g����
		template<class T_Dedicated_Point, class ...T_Fn_Parts>
			requires (std::is_class_v<T_Dedicated_Point>)
		struct S_Function_Data<T_Dedicated_Point*, T_Fn_Parts...> :
			S_Function_Data<T_Fn_Parts...>
		{
			using pointer = T_Dedicated_Point;
		};

		//�d�l
		//�����̌^���Z�b�g����
		template<class T_Fn, class ...T_Bind_Args>
		struct S_Function_Data<T_Fn,T_Bind_Args...> :
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
		//�ÓI�֐��̌^����A�e��p�����[�^���Z�b�g����
		template<class T_RType, class ...T_Args>
		struct S_Function_Data<T_RType(*)(T_Args...)> :
			S_Function_Data<>
		{
			using function = T_RType(*)(T_Args...);

			using r_type = T_RType;
		};


		//�d�l
		//�e�ƂȂ�֐��I�u�W�F�N�g�̌^���Z�b�g����
		template<class ...T_Parts>
		struct S_Function_Data<Function<Function_Core<T_Parts...>>> :
			S_Function_Data<Function_Core<T_Parts...>>
		{};

		//�d�l
		//�e�ƂȂ�֐��I�u�W�F�N�g�̌^���Z�b�g����
		template<class ...T_Parts>
		struct S_Function_Data<Function_Core<T_Parts...>> :
			S_Function_Data<>
		{
			using function = Function_Core<T_Parts...>;

		};

		template<class ...T_Fns>
		struct S_Function_Data<tuple_t<T_Fns...>> :
			S_Function_Data<>
		{
			using function = tuple_t<T_Fns...>;

		};

		//�d�l
		//�֐��I�u�W�F�N�g�̌^�łȂ��ꍇ�A�Z�b�g���Ȃ�
		template<class T_Fn>
		struct S_Function_Data<T_Fn> :
			S_Function_Data<>
		{};


		//�d�l
		//[Function_Core<>]��[ T_Fn_Parts...]�̑O�ɑ}����[S_Function_Data]�ɐڑ�����
		template<class ...T_Fn_Parts>
		struct S_Function_Data_Access
		{
			using type = S_Function_Data<T_Fn_Parts...>;
		};


		using type = typename N_Tuple::I_Expand_Set<S_Function_Data_Access, T_Fn_Parts...>::type::type;

		//�d�l
		//�o�C���h�ς݈����������̏ꍇ�A[function]�𖳌��l�ɕύX����
		template<class T_Core, class T_Args_Chack = typename T_Core::request_args>
		struct S_is_Valid_Fn
		{
			using type = T_Core;
		};

		template<class T_Parent>
		struct S_is_Valid_Fn<T_Parent, invalid_t>
		{
			using type = invalid_t;
		};

	public:

		using function = Function_Core<T_Fn_Parts...>;

		//using request = typename S_Request_Access<>::type;

		using bind_args = type::bind_args;




			//typename S_is_Valid_Fn<type>::type;
		
		//using request_args = type::request_args;
		
		//using request_pointer = type::request_pointer;
		
		
		//using c_name = type::c_name;

		//static constexpr size_t fn_count = type::fn_count;

	};

}

