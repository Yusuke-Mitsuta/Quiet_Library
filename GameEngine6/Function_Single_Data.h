#pragma once

#include"Function_Core.h"
#include"Tuple.h"
#include"Concept.h"

#include"Function_Args_Chack.h"

template<class TP_Fns, class TP_Args_type>
class Function;

namespace N_Function
{

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




		//private:

			//�d�l
			//�֐��I�u�W�F�N�g�̌^�ɑ΂��āA���������̌^���L�������肪�����̏ꍇ
		template<class ...T_Fn_Parts>
		struct S_Function_Data
		{
			using function = invalid_t;
			using method = invalid_t;
			using request_args = invalid_t;
			using bind_args = invalid_t;
			using c_name = invalid_t;
			using r_type = invalid_t;

			static constexpr size_t fn_count = 0;
		};




		//�d�l
		//�擪�̌^���N���X�^���A�|�C���^�[�^�ł���A���\�b�h���w�肳��Ă���Ȃ�A
		//�N���X�̃|�C���^�[�^�̔�����s��
		template<class T_Dedicated_Point, class ...T_Fn_Parts>
			requires (std::is_class_v<T_Dedicated_Point>)
		struct S_Function_Data<T_Dedicated_Point*, T_Fn_Parts...> :
			S_Function_Data<T_Fn_Parts...>
		{

			template<class T_Fns, class ...T_Bind_Args>
			struct method_change_function
			{
				using type = Method_Core<T_Fns, T_Bind_Args...>;
			};


			template<same_as_template_type<Function_Core> ...T_Fns, class ...T_Bind_Args>
			struct method_change_function<tuple_t<T_Fns...>, T_Bind_Args... >
			{
				using type = Function_Core<tuple_t<T_Fns...>, T_Bind_Args...>;
			};


			template<class ...T_Fn_parts, class ...T_Bind_Args>
			struct method_change_function<Function_Core<T_Fn_parts...>, T_Bind_Args... >
			{
				using type = Function_Core<Function_Core<T_Fn_parts...>, T_Bind_Args...>;
			};


			template<class T_Fns>
			struct Method_Point_Chack
			{
				using type = T_Fns;
			};

			template<class T_Fn, class ...T_Bind_Args>
				requires (convertible_to<T_Dedicated_Point, typename S_Function_Data<T_Fn>::c_name>)
			struct Method_Point_Chack<Method_Core<T_Fn, T_Bind_Args...>>
			{
				using type = Function_Core<T_Fn, T_Bind_Args...>;
			};

			template<class T_Fn, class ...T_Bind_Args>
				requires (S_Function_Data<T_Fn>::fn_count != 1)
			struct Method_Point_Chack<Method_Core<T_Fn, T_Bind_Args...>>
			{

				using type = method_change_function<
					typename Method_Point_Chack< T_Fn>::type, T_Bind_Args...>::type;
			};

			template<class ...T_Fns, class ...T_Bind_Args>
			struct Method_Point_Chack<Method_Core<tuple_t<T_Fns...>, T_Bind_Args...>>
			{

				using type = typename method_change_function<tuple_t<typename Method_Point_Chack<T_Fns>::type...>>::type;

			};

			using base = typename S_Function_Data<T_Fn_Parts...>;


			using function = typename Method_Point_Chack<typename base::function>::type;


		};


		template<class T_Fns, class ...T_Bind_Args>
		struct S_Args;


		//�d�l
		//[using request_args],[using bind_args]���`����
		//�v����������̌^�ɁA�w�肷������̌^�������������肷��
		//
		//�e���v���[�g
		//[T_Parent]::���݂̊֐��I�u�W�F�N�g�̈�e�̌^
		//[T_Bind_Args...]::�w�肷������̌^
		template<class T_Fns, class ...T_Bind_Args>
		struct S_Args
		{
			using request_args = invalid_t;


			using bind_args = invalid_t;
		};

		template<class ...T_Fns, class ...T_Bind_Args>
		struct S_Args<tuple_t<T_Fns...>, T_Bind_Args...>
		{

			using request_args = tuple_t<typename S_Args<T_Fns, T_Bind_Args...>::request_args...>;

			using bind_args = tuple_t<T_Bind_Args...>;

		};

		//�d�l
		//[using request_args],[using bind_args]���`����
		//�v����������̌^�ɁA�w�肷������̌^�������������肷��
		// 
		//�e���v���[�g
		//[tuple_tp<T_Head,T,T_Tail>]::�v����������̌^�A�y�сA���̌^�̖�����̈����̈ʒu������
		//[T_Bind_Args...]::�w�肷������̌^
		template<class T_Head, class T, class T_Tail, class ...T_Bind_Args>
		struct S_Args<tuple_tp<T_Head, T, T_Tail>, T_Bind_Args...>
		{
		private:
			using args_chack = I_Function_Args_Chack<
				tuple_tp<T_Head, T, T_Tail>, tuple_t<T_Bind_Args...>>;

		public:

			using request_args = args_chack::request_args;

			using bind_args = tuple_t<T_Bind_Args...>;
			//args_chack::bind_args;

		};




		//�d�l
		//�֐��I�u�W�F�N�g���ÓI���\�b�h�̏ꍇ
		template<class T_RType, class ...T_Args, class ...T_Bind_Args>
		struct S_Function_Data<T_RType(*)(T_Args...), T_Bind_Args...> :
			S_Args<typename tuple_t<T_Args...>::back, T_Bind_Args...>
		{

			using function = Function_Core<T_RType(*)(T_Args...), T_Bind_Args...>;
			using c_name = invalid_t;

			using r_type = T_RType;

			static constexpr size_t fn_count = 1;
		};


		//�d�l
		//�֐��I�u�W�F�N�g���N���X���\�b�h�̏ꍇ�A���N���X�|�C���^�̌^�𔻒肷��ꍇ
		template<class T_CName, class T_RType, class ...T_Args, class ...T_Bind_Args>
		struct S_Function_Data<T_RType(T_CName::*)(T_Args...), T_Bind_Args...> :
			S_Args<typename tuple_t<T_Args...>::back, T_Bind_Args...>
		{

			using function = Method_Core<T_RType(T_CName::*)(T_Args...), T_Bind_Args...>;
			using c_name = T_CName;
			using r_type = T_RType;

			static constexpr size_t fn_count = 1;
		};


		//�d�l
		//���Ɉ�����ݒ�ς݂̊֐��I�u�W�F�N�g�ɐV���Ɉ�����ݒ肷��ꍇ
		template<template<class...>class T_Outer_Core, class T_Fn, class ...T_before_Bind_Args, class ...T_Bind_Args>
		struct S_Function_Data<T_Outer_Core<T_Fn, T_before_Bind_Args...>, T_Bind_Args...> :
			S_Args<typename S_Function_Data<T_Fn, T_before_Bind_Args...>::request_args, T_Bind_Args...>
		{
			using function = T_Outer_Core<T_Outer_Core<T_Fn, T_before_Bind_Args...>, T_Bind_Args...>;

			using c_name = S_Function_Data<T_Fn>::c_name;
			static constexpr size_t fn_count = S_Function_Data<T_Fn>::fn_count;
		};


		//�d�l
		//�����ɓZ�߂��Ă���֐���W�J����
		template<template<class...>class T_Outer_Core, class ...T_Fns, class ...T_before_Bind_Args, class ...T_Bind_Args>
		struct S_Function_Data<T_Outer_Core<tuple_t<T_Fns...>, T_before_Bind_Args...>, T_Bind_Args...>
		{
			using function = T_Outer_Core<T_Outer_Core<tuple_t<T_Fns...>, T_before_Bind_Args...>, T_Bind_Args... >;

			static constexpr size_t fn_count = (S_Function_Data<T_Fns>::fn_count + ...);
			using c_name = invalid_t;
			using request_args = tuple_t<typename S_Function_Data<Function_Core<T_Fns, T_before_Bind_Args...>, T_Bind_Args...>::request_args...>;
			using bind_args = tuple_t<T_Bind_Args...>;

		};


		template<class ...T_Fns, class T_type_numbers, class T_Tuple_Args_types, class ...T_Bind_Args>
		struct S_Function_Data<Function<tuple_t<tuple_t<T_Fns...>, T_type_numbers>, T_Tuple_Args_types>, T_Bind_Args...> :
			S_Function_Data<Function_Core<tuple_t<T_Fns...>, T_Bind_Args...>>
		{
		};

		//template<class ...T_Fns, class T_type_numbers, class ...T_Bind_Args>
		//struct S_Function_Data<Function<tuple_t<tuple_t<T_Fns...>, T_type_numbers>>, T_Bind_Args...> :
		//	S_Function_Data<Method_Core<tuple_t<T_Fns...>, T_Bind_Args...>>
		//{
		//};




		//�d�l
		//�o�C���h�ς݈����������̏ꍇ�A[function],[method]�𖳌��l�ɕύX����
		template<class T_Parent, class T_Args_Chack = typename T_Parent::bind_args>
		struct S_is_Valid_Method_Data
		{
			using function = T_Parent::function;
		};

		template<class T_Parent>
		struct S_is_Valid_Method_Data<T_Parent, invalid_t>
		{
			using function = invalid_t;
		};



		//�d�l
		//tuple_t�ł܂Ƃ߂��Ă���ꍇ�A�W�J����
		template<class ...T_Fn_Parts>
		struct S_Function_Data<tuple_t<T_Fn_Parts...>> :
			S_Function_Data<T_Fn_Parts...>
		{};

		template<class ...T_Head, class T, class ...T_Tail>
		struct S_Function_Data<tuple_tp<tuple_t<T_Head...>, T, tuple_t<T_Tail...>>> :
			S_Function_Data<T_Head..., T, T_Tail...> {};

		template<class ...T_Head, class ...T_Tail>
		struct S_Function_Data<tuple_tp<tuple_t<T_Head...>, invalid_t, tuple_t<T_Tail...>>> :
			S_Function_Data<T_Head..., T_Tail...> {};


	public:



		using type = N_Tuple::I_Expand_Set<S_Function_Data, T_Fn_Parts...>::type;
		using function =
			//type::function;
			typename S_is_Valid_Method_Data<type>::function;
		using request_args = type::request_args;
		using bind_args = type::bind_args;

		using c_name = type::c_name;

		static constexpr size_t fn_count = type::fn_count;

	};

}









namespace N_Function
{

	//�d�l
	//�֐��I�u�W�F�N�g�̌^�ɑ΂��āA���������̌^���L�������肷��B
	//
	//�e���v���[�g
	//[T_Fn_Parts...]::
	// �������͑������̌Ăяo���Ɏg�p����N���X�|�C���^�[�̌^�ł���B�N���X�|�C���^�[�̌^�𔻒肵�Ȃ��ꍇ�͎w��s�v�ł���B�ÓI���\�b�h�A�N���X�|�C���^�[�̌^���w��ς݁A�̏ꍇ�͎w��s�ł���B
	// �������͊֐��̌^�A�Ⴕ���́A������bind�����^[Function_Core],[Method_Core]�Ƃ���
	// ��O�����ȍ~�́A�������̊֐��I�u�W�F�N�g�̈����Ɏw�肷��^���X�g
	template<class ...T_Fn_Parts>
	struct I_Function_Single_Data_2
	{

		//�d�l
		//�֐��I�u�W�F�N�g��[T_Fn_Parts...]���ɑ��݂��Ȃ��ꍇ
		template<class ...T_Fn_Parts>
		struct S_Function_Data
		{
			using type = Function_Core<>;
		};

		//�d�l
		//���ʂŎg�p����|�C���^�[�̌^���Z�b�g����
		template<class ...T_Result, class T_Dedicated_Point, class ...T_Fn_Parts>
			requires (std::is_class_v<T_Dedicated_Point>)
		struct S_Function_Data<Function_Core<T_Result...>, T_Dedicated_Point*, T_Fn_Parts...>
		{
			using type = S_Function_Data<Function_Core<T_Result...,
				Parts<"pointer", T_Dedicated_Point>>, T_Fn_Parts...>::type;
		};

		//�d�l
		//�����̌^���Z�b�g����
		template<class ...T_Result, class T_Fn, class ...T_Bind_Args>
		struct S_Function_Data<Function_Core<T_Result...>, T_Fn, T_Bind_Args...>
		{
			using type = S_Function_Data<
				Function_Core<T_Result...,
				Parts<"bind_args", tuple_t<T_Bind_Args...>>>,
				T_Fn>::type;
		};

		//�d�l
		//�N���X���\�b�h�̌^����A�e��p�����[�^���Z�b�g����
		template<class ...T_Result, class T_CName, class T_RType, class ...T_Args>
		struct S_Function_Data<Function_Core<T_Result...>, T_RType(T_CName::*)(T_Args...)>
		{
			using fn = T_RType(T_CName::*)(T_Args...);

			using type = S_Function_Data<
				Function_Core<T_Result...,
				Parts<"function",
				Function_Core<Parts<"function", fn>,
				Parts<"request_args", typename tuple_t<T_Args...>::back>,
				Parts<"c_name", T_CName>,
				Parts<"request_pointer", T_CName>,
				Parts<"r_type", T_RType>>>
				>>::type;
		};

		//�d�l
		//�ÓI�֐��̌^����A�e��p�����[�^���Z�b�g����
		template<class ...T_Result, class T_RType, class ...T_Args>
		struct S_Function_Data<Function_Core<T_Result...>, T_RType(*)(T_Args...)>
		{
			using fn = T_RType(*)(T_Args...);

			using type = S_Function_Data<
				Function_Core<T_Result...,
				Parts<"function",
				Function_Core<Parts<"function", fn>,
				Parts<"request_args", typename tuple_t<T_Args...>::back>,
				Parts<"r_type", T_RType>>>
				>>::type;
		};

		//�d�l
		//�e�ƂȂ�֐��I�u�W�F�N�g�̌^���Z�b�g����
		template<class ...T_Result, class ...T_Parts>
		struct S_Function_Data<Function_Core<T_Result...>,Function_Core<T_Parts...>>
		{
			using type = S_Function_Data<
				Function_Core<T_Result...,
				Parts<"function", Function_Core<T_Parts...>>
				>>::type;
		};

		//�d�l
		//�֐��I�u�W�F�N�g�̌^�łȂ��ꍇ�A�Z�b�g���Ȃ�
		template<class ...T_Result, class T_Fn>
		struct S_Function_Data<Function_Core<T_Result...>, T_Fn>
		{
			using type = S_Function_Data<
				Function_Core<T_Result...>>::type;
		};

		//�d�l
		//[TT_Action][t_parts_name]�ŗv������v�f��T_Core���璊�o����
		//
		//�e���v���[�g
		//[TT_Action]:�������ɃR�A�A�������ɑ΂��āA�R�A�̒l�ŏ���������l
		//[t_parts_name]:�v������R�A�̗v�f��
		//
		//�⑫
		//[TT_Action]�̑�������[T_Core]�ɕ����̊֐����Z�߂��Ă���ꍇ�A�������������
		template<template<class...>class TT_Action, N_Constexpr::String t_parts_name, class T_Core>
		struct I_Request
		{

			template<class T_Fn = typename T_Core::function,
				class T_request = typename U_Parts_Search_InnerType<t_parts_name, T_Fn>::type>
			struct S_Request
			{
				using type = TT_Action<T_Core, T_request>::type;
			};

			template<class T_Fn, class ...T_request>
			struct S_Request<T_Fn, tuple_t<T_request...>>
			{
				using type = tuple_t<typename S_Request<T_Fn, T_request>::type...>;
			};

			template<class ...T_Fns, class T_request>
			struct S_Request<Function_Core<tuple_t<T_Fns...>>, T_request>
			{
				using type = tuple_t<typename S_Request<T_Fns>::type...>;
			};

			using type = S_Request<>::type;

		};

		//�d�l
		//�v������������R�A����擾����
		//
		//�⑫
		//�֐����Z�߂��Ă���ꍇ�A[tuple_t]�œZ�߂�
		template<class T_Core>
		struct I_Request_args
		{
			template<class T_Core, class T_Request_Args>
			struct S_Request_args
			{
				using type = T_Request_Args;
			};

			template<class ...T_Parts, N_Tuple::is_Tuple T_Request_Args>
				requires(not_is_invalid<typename U_Parts_Search_InnerType<"bind_args", Function_Core<T_Parts...>>::type>)
			struct S_Request_args<Function_Core<T_Parts...>, T_Request_Args>
			{
				using type = I_Function_Args_Chack<T_Request_Args, typename Function_Core<T_Parts...>::bind_args>::request_args;
			};

			using type = I_Request<S_Request_args, "request_args", T_Core>::type;
		};

		//�d�l
		//�v������|�C���^�[�̌^���R�A����擾���A
		// �݊����̂���|�C���^�[���Z�b�g����ē���Ηv����������
		//
		//�⑫
		//�֐����Z�߂��Ă���ꍇ�A[tuple_t]�œZ�߂�
		//�K�v�łȂ��ꍇ�A[invalid_t]���Ԃ�
		template<class T_Core>
		struct I_Request_pointer
		{
			template<class T_Core, class T_Request_pointer>
			struct S_Request_pointer
			{
				using type = T_Request_pointer;
			};

			template< class ...T_Parts, class T_Request_pointer>
				requires(convertible_to<typename U_Parts_Search_InnerType<"pointer", Function_Core<T_Parts...>>::type, T_Request_pointer>)
			struct S_Request_pointer<Function_Core<T_Parts...>, T_Request_pointer>
			{
				using type = invalid_t;
			};

			using type = I_Request<S_Request_pointer, "request_pointer", T_Core>::type;
		};


		//�d�l
		//�v������|�C���^�[�̌^�ƈ����̌^���Z�b�g����
		template<class ...T_Result>
		struct S_Function_Data<Function_Core<T_Result...>>
		{
			using core = Function_Core<T_Result...>;

			using type =
				Function_Core<T_Result...,
				Parts<"request_args", typename I_Request_args<core>::type>,
				Parts<"request_pointer", typename I_Request_pointer<core>::type>
				>;
		};



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

		//�d�l
		//[Function_Core<>]��[ T_Fn_Parts...]�̑O�ɑ}����[S_Function_Data]�ɐڑ�����
		template<class ...T_Fn_Parts>
		struct S_Function_Data_Access
		{
			using type = S_Function_Data< Function_Core<>, T_Fn_Parts...>::type;
		};

	public:

		using type = N_Tuple::I_Expand_Set<S_Function_Data_Access, T_Fn_Parts...>::type::type;
			
		using function =typename S_is_Valid_Fn<type>::type;

		using request_args = type::request_args;

		using bind_args = type::bind_args;

		using c_name = type::c_name;

	//static constexpr size_t fn_count = type::fn_count;

	};

}

