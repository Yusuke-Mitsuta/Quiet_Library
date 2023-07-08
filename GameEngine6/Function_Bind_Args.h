#pragma once
#include"Function_Address.h"
#include<optional>

namespace N_Function
{
	//�d�l
	//�֐��|�C���^�[�ɑ΂��āA�����̒l�����������A�����v�Ŕ��肷��
	//
	//�e���v���[�g
	//T_Fn_Args::�֐��|�C���^�[�A�w�肷������A�̃p�����[�^�p�b�N
	//
	//�⑫
	//T_Fn_Args�͊֐��|�C���^�[�A����Ɏw�肷������A���̊֐��|�C���^�[�A�ƂȂ�悤�ɂ��鎖
	template<class ...T_Fn_Args>
	struct IS_BindArgs
	{
	private:

		template<class ...T_Fn_Args>
		struct S_BindArgs {};

		template<class C_Name, class R_Type, class ...T_Args, class ...T_Fn_Args>
		struct S_BindArgs<R_Type(C_Name::*)(T_Args...), T_Fn_Args...>
		{
			using Type = S_BindArgs<S_Address
				<R_Type(C_Name::*)(T_Args...), std::tuple<>>, T_Fn_Args...>::Type;
		};

		template<class ...T_Zip_Fn_Args, class ...T_Fn_Args>
		struct S_BindArgs<std::tuple<T_Zip_Fn_Args...>, T_Fn_Args...>
		{
			using Type = S_BindArgs<T_Zip_Fn_Args..., T_Fn_Args...>::Type;
		};

		//�d�l
		//�֐��|�C���^�[���w�肵�A�����𐸍�����
		template< class C_Name, class R_Type, class ...T_Args, class ...T_DefaultSetArgs, class ...T_Fn_Args>
		struct S_BindArgs<S_Address<R_Type(C_Name::*)(T_Args...), std::tuple<T_DefaultSetArgs...>>, T_Fn_Args...>
		{
			using T_Method = R_Type(C_Name::*)(T_Args...);

			template<class Args, class ...T_Fn_Args>
			struct S_BindArgsExecution {};

			//�d�l
			//�w�肵���֐��ɑ΂��āA�����̌^���W�߂�
			template<class ...T_NewDefaultSetArgs, class ...T_Fn_Args>
			struct S_BindArgsExecution<std::tuple<T_NewDefaultSetArgs...>, std::nullopt_t, T_Fn_Args...>
			{
				using Type = S_BindArgsExecution;
				using Judge = std::bool_constant<tuple_back_part_convertible_to<std::tuple<T_NewDefaultSetArgs..., T_DefaultSetArgs...>, std::tuple<T_Args...>>>;
				using Tuple = std::tuple<T_Fn_Args..., S_Address<T_Method, std::tuple<T_NewDefaultSetArgs..., T_DefaultSetArgs...>>>;
			};

			//�d�l
			//�w�肵���֐��ɑ΂��āA�����̌^���W�߂�
			template<class ...T_NewDefaultSetArgs, class T_SetArgs, class ...T_Fn_Args>
			struct S_BindArgsExecution<std::tuple<T_NewDefaultSetArgs...>, T_SetArgs, T_Fn_Args...>
			{
				using Type = S_BindArgsExecution<std::tuple<T_NewDefaultSetArgs..., T_SetArgs>, T_Fn_Args...>::Type;
			};

			//�d�l
			//�q�b�g�����֐��|�C���^�[��S_Address�^�ɕϊ����A�������W�߂�̂��I������B
			template<class ...T_NewDefaultSetArgs, class C_Name, class R_Type, class ...T_Args, class ...T_Fn_Args>
			struct S_BindArgsExecution<std::tuple<T_NewDefaultSetArgs...>, R_Type(C_Name::*)(T_Args...), T_Fn_Args...>
			{
				using Type = S_BindArgsExecution<std::tuple<T_NewDefaultSetArgs...>,
					S_Address<R_Type(C_Name::*)(T_Args...), std::tuple<>>, T_Fn_Args...>::Type;
			};

			//�d�l
			//���̊֐��|�C���^�[���q�b�g�����ہA�w�肵���֐��ɑ΂��Ă̈������W�߂�̂��I�����A���ꂪ�������^�̈��������肷��
			//���̌�q�b�g�����֐��|�C���^�[�ɑ΂��ẮA�������W�߂��J�n����
			template<class ...T_NewDefaultSetArgs, class ...T_Flont_Fn, class ...T_Fn_Args>
				requires tuple_back_part_convertible_to<std::tuple<T_NewDefaultSetArgs..., T_DefaultSetArgs...>, std::tuple<T_Args...>>
			struct S_BindArgsExecution<std::tuple<T_NewDefaultSetArgs...>, S_Address<T_Flont_Fn...>, T_Fn_Args...>
			{
				using Type = S_BindArgs<S_Address<T_Flont_Fn...>, T_Fn_Args...,
					S_Address<T_Method, std::tuple<T_NewDefaultSetArgs..., T_DefaultSetArgs...>>>::Type;
			};

			//�d�l
			//�w�肵���֐��ɑ΂��Ă̈������W�߂�̂��I�����A���ꂪ�������Ȃ��ꍇ�A�������I������
			template<class ...T_NewDefaultSetArgs, class ...T_Flont_Fn, class ...T_Fn_Args>
			struct S_BindArgsExecution<std::tuple<T_NewDefaultSetArgs...>, S_Address<T_Flont_Fn...>, T_Fn_Args...>
			{
				using Type = S_BindArgsExecution<std::tuple<T_NewDefaultSetArgs...>, std::nullopt_t>::Type;
			};

			using Type = S_BindArgsExecution<std::tuple<>, T_Fn_Args...>::Type;
		};

		using Type = S_BindArgs<T_Fn_Args..., std::nullopt_t>::Type;

	public:
		//�d�l
		//�֐��|�C���^�[�A�����̌^��tuple��S_Address�^�ɂ܂Ƃ߂��^���Ԃ�
		using TupleType = Type::Tuple;

		//�d�l
		//�֐��|�C���^�[�A�����̌^��tuple��S_Address�^�ɂ܂Ƃ߂����ʁA�����ǂ����Ԃ�
		using Judge = Type::Judge;

	};

}
