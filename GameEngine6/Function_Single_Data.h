#pragma once

#include"Function_Core.h"
#include"Tuple.h"
#include"Concept.h"

#include"Function_Args_Chack.h"

template<class TP_Fns>
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

			template<class ...T_Fns,class ...T_Bind_Args>
			struct Method_Point_Chack<Method_Core<tuple_t<T_Fns...>,T_Bind_Args...>>
			{
				template<class T_Fns>
				struct method_change_function
				{
					using type = Method_Core<T_Fns, T_Bind_Args...>;
				};				
				
				template<same_as_template_type<Function_Core> ...T_Fns>
				struct method_change_function<tuple_t<T_Fns...>>
				{
					using type = Function_Core<tuple_t<T_Fns...>, T_Bind_Args...>;
				};

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
		template<template<class...>class T_Outer_Core,  class ...T_Fns, class ...T_before_Bind_Args, class ...T_Bind_Args>
		struct S_Function_Data<T_Outer_Core<tuple_t<T_Fns...>, T_before_Bind_Args...>, T_Bind_Args...>
		{
			using function = T_Outer_Core<T_Outer_Core<tuple_t<T_Fns...>, T_before_Bind_Args...>, T_Bind_Args... >;

			static constexpr size_t fn_count = (S_Function_Data<T_Fns>::fn_count + ...);
			using c_name = invalid_t;
			using request_args = tuple_t<typename S_Function_Data<Function_Core<T_Fns, T_before_Bind_Args...>, T_Bind_Args...>::request_args...>;
			using bind_args = tuple_t<T_Bind_Args...>;

		};


		template<class ...T_Fns,class T_type_numbers ,class ...T_Bind_Args>
		struct S_Function_Data<Function<tuple_t<tuple_t<T_Fns...>,T_type_numbers>>, T_Bind_Args...> :
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

		static constexpr size_t fn_count = type::fn_count;

	};

}

