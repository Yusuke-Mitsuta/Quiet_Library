#pragma once

#include"Function_Core.h"
#include"Tuple.h"
#include"Concept.h"

#include"Function_Args_Chack.h"

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
	private:

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

			static constexpr int lelve = -1;
		};

		//�d�l
		//tuple_t�ł܂Ƃ߂��Ă���ꍇ�A�W�J����
		template<class ...T_Fn_Parts>
		struct S_Function_Data<tuple_t<T_Fn_Parts...>> :
			S_Function_Data<T_Fn_Parts...>
		{};

		template<class ...T_Head,class T,class ...T_Tail>
		struct S_Function_Data<tuple_tp<tuple_t<T_Head...>,T,tuple_t<T_Tail...>>> :
			U_if_t1< S_Function_Data<T_Head...,T,T_Tail...>, S_Function_Data<T_Head..., T_Tail...>,not_is_invalid<T>>
		{};

		template<class ...TP_Method_Inner>
		struct S_Parent;

		//�d�l
		//[using request_args],[using bind_args]���`����
		//�v����������̌^�ɁA�w�肷������̌^�������������肷��
		// 
		//�e���v���[�g
		//[T_Parent]::���݂̊֐��I�u�W�F�N�g�̈�e�̌^
		//[T_Bind_Args...]::�w�肷������̌^
		template<class T_Parent, class ...T_Bind_Args>
		struct S_Args :
			S_Args<typename T_Parent::request_args,T_Bind_Args...>
		{};

		//�d�l
		//[using request_args],[using bind_args]���`����
		//�v����������̌^�ɁA�w�肷������̌^�������������肷��
		// 
		//�e���v���[�g
		//[tuple_tp<T_Head,T,T_Tail>]::�v����������̌^�A�y�сA���̌^�̖�����̈����̈ʒu������
		//[T_Bind_Args...]::�w�肷������̌^
		template<class T_Head,class T,class T_Tail, class ...T_Bind_Args>
		struct S_Args<tuple_tp<T_Head,T,T_Tail>,T_Bind_Args...>
		{
		private:
			using args_chack = I_Function_Args_Chack<
				tuple_tp<T_Head, T, T_Tail>, tuple_t<T_Bind_Args...>>;

		public:
			using request_args = args_chack::request_args;

			using bind_args = args_chack::bind_args;

		};


		//�d�l
		//[using method]���`����
		//[method]�͎g�p����N���X�|�C���^�̌^�𖢎w��̃I�u�W�F�N�g������
		//�e���v���[�g
		//[T_Parent]::���ɂ���֐��I�u�W�F�N�g
		//[T_Bind_Args...]::�w�肷������̌^
		template<class T_Parent, class ...T_Bind_Args>
		struct S_Method
		{
			using function = invalid_t;
			using method = Method_Core<T_Parent, T_Bind_Args...>;
		};

		//�d�l
		//��������[Function_Core< ... >]�̏ꍇ�A[Method_Core< ... >]�̃C���i�[�e���v���[�g��[Function_Core]�����݂����Ȃ��ׂ�[Function_Core]��[Method_Core]�ɕϊ�����
		//
		//�e���v���[�g
		//[T_Dedicated_Point*]::[T_Fn]�Ŏg�p����N���X�|�C���^�̌^
		//[T_Fn]::�֐��I�u�W�F�N�g�̌^
		//[T_Bind_Args...]::�w�肷������̌^
		template<class ...TP_Function_Inner, class ...T_Bind_Args>
		struct S_Method<Function_Core<TP_Function_Inner...>, T_Bind_Args...>
		{
			using method = Method_Core<typename S_Method<TP_Function_Inner...>::method, T_Bind_Args...>;
		};

		//�d�l
		//[using function]���`����
		//[function]�͌Ăяo�����ԂɂȂ��Ă���֐��I�u�W�F�N�g������
		//
		//�e���v���[�g
		//[T_Fn]::�֐��I�u�W�F�N�g�̌^
		//[T_Bind_Args...]::�w�肷������̌^
		//
		//�⑫
		//[function]�̓N���X�|�C���^�[���w��ς݁A�Ⴕ���́A�ÓI���\�b�h�̏ꍇ�Ɍ���
		template<class T_Fn, class ...T_Bind_Args>
		struct S_Function :
			S_Method<T_Fn, T_Bind_Args...>
		{
			using function = Function_Core< T_Fn, T_Bind_Args...>;
		};

		//�d�l
		//�N���X�|�C���^�̌^�������������肵�A���Ȃ�[using function]���`����
		//
		//�e���v���[�g
		//[T_Dedicated_Point*]::[T_Fn]�Ŏg�p����N���X�|�C���^�̌^
		//[T_Fn]::�֐��I�u�W�F�N�g�̌^
		//[T_Bind_Args...]::�w�肷������̌^
		template<class T_Dedicated_Point,class T_Fn, class ...T_Bind_Args>
		struct S_Function<T_Dedicated_Point*, T_Fn, T_Bind_Args...> :
			S_Method<T_Fn, T_Bind_Args...>
		{
			using function = U_if_t1<Function_Core< T_Fn, T_Bind_Args...>,invalid_t, convertible_to<T_Dedicated_Point, typename S_Function_Data<T_Fn>::c_name>>;
		};

		//�d�l
		//�֐��I�u�W�F�N�g�������ݍ��񂾂����肷��
		//
		//�e���v���[�g
		//[TP_Method_Inner...]::����ݍ��񂾒��g
		//
		//�⑫
		//
		//����ݍ��񂾒��g�Ƃ�
		//[Method_Core<TP_Method_Inner...>]or[Function_Core<TP_Method_Inner...>]�̃C���i�[�e���v���[�g���w��
		template<class ...TP_Method_Inner>
		struct S_Parent
		{
			using parent = typename S_Function_Data<TP_Method_Inner...>;

			using c_name = parent::c_name;
			using r_type = parent::r_type;

			static constexpr int lelve = parent::lelve + 1;

		};
		
		//�d�l
		//�֐��I�u�W�F�N�g���ÓI���\�b�h�̏ꍇ
		template<class T_RType, class ...T_Args, class ...T_Bind_Args>
		struct S_Function_Data<T_RType(*)(T_Args...), T_Bind_Args...> :
			S_Function<T_RType(*)(T_Args...), T_Bind_Args...>,
			S_Args<typename tuple_t<T_Args...>::back,T_Bind_Args...>
		{
			using c_name = invalid_t;
			using r_type = T_RType;

			static constexpr int lelve = 0;
		};
		//�d�l
		//�֐��I�u�W�F�N�g���N���X���\�b�h�̏ꍇ�A���N���X�|�C���^�̌^�𔻒肵�Ȃ��ꍇ
		template<class T_CName, class T_RType, class ...T_Args, class ...T_Bind_Args>
		struct S_Function_Data<T_RType(T_CName::*)(T_Args...), T_Bind_Args...> :
			S_Method<T_RType(T_CName::*)(T_Args...), T_Bind_Args...>,
			S_Args<typename tuple_t<T_Args...>::back, T_Bind_Args...>
		{
			using c_name = T_CName;
			using r_type=T_RType;

			static constexpr int lelve = 0;
		};	

		//�d�l
		//�֐��I�u�W�F�N�g���N���X���\�b�h�̏ꍇ�A���N���X�|�C���^�̌^�𔻒肷��ꍇ
		template<class T_Dedicated_Point, class T_CName, class T_RType, class ...T_Args, class ...T_Bind_Args>
		struct S_Function_Data<T_Dedicated_Point*, T_RType(T_CName::*)(T_Args...), T_Bind_Args...> :
			S_Function<T_Dedicated_Point*,T_RType(T_CName::*)(T_Args...), T_Bind_Args...>,
			S_Args<typename tuple_t<T_Args...>::back, T_Bind_Args...>
		{
			using c_name = T_CName;
			using r_type = T_RType;

			static constexpr int lelve = 0;
		};

		//�d�l
		//�������o�C���h�ς݁A���N���X�|�C���^�̌^�𔻒肵�Ȃ��ꍇ
		template<class ...TP_Method_Inner, class ...T_Bind_Args>
		struct S_Function_Data<Method_Core<TP_Method_Inner...>, T_Bind_Args...> :
			S_Method<Method_Core<TP_Method_Inner...>, T_Bind_Args...>,
			S_Args<S_Function_Data<TP_Method_Inner...>, T_Bind_Args...>,
			S_Parent<TP_Method_Inner...>
		{};

		//�d�l
		//�������o�C���h�ς݁A���N���X�|�C���^�̌^�𔻒肷��ꍇ
		template<class T_Dedicated_Point, class ...TP_Method_Inner, class ...T_Bind_Args>
		struct S_Function_Data<T_Dedicated_Point*, Method_Core<TP_Method_Inner...>, T_Bind_Args...> :
			S_Function<T_Dedicated_Point*, Method_Core<TP_Method_Inner...>, T_Bind_Args...>,
			S_Args<S_Function_Data<TP_Method_Inner...>, T_Bind_Args...>,
			S_Parent<TP_Method_Inner...>
		{};

		//�d�l
		//�����o�C���h�ς݁A�y�сA�N���X�|�C���^�̌^���w��ς݁A���͐ÓI���\�b�h�̏ꍇ
		template<class ...TP_Function_Inner, class ...T_Bind_Args>
		struct S_Function_Data<Function_Core<TP_Function_Inner...>, T_Bind_Args...> :
			S_Function<Function_Core<TP_Function_Inner...>, T_Bind_Args...>,
			S_Args<S_Function_Data<TP_Function_Inner...>, T_Bind_Args...>,
			S_Parent<TP_Function_Inner...>
		{};


		//�d�l
		//�o�C���h�ς݈����������̏ꍇ�A[function],[method]�𖳌��l�ɕύX����
		template<class T_Parent, class T_Args_Chack = typename T_Parent::bind_args>
		struct S_is_Valid_Method_Data
		{
			using function = T_Parent::function;
			using method = T_Parent::method;
		};

		template<class T_Parent>
		struct S_is_Valid_Method_Data<T_Parent, invalid_t>
		{
			using function = invalid_t;
			using method = invalid_t;
		};


	public:
		using type = S_Function_Data<T_Fn_Parts...>;

		using function = typename S_is_Valid_Method_Data<type>::function;
		using method = typename S_is_Valid_Method_Data<type>::method;
		using request_args = type::request_args;
		using bind_args = type::bind_args;
		using c_name = type::c_name;
		using r_type = type::r_type;

		static constexpr int lelve = type::lelve;

	};


	template<class ...T_Fn_Parts>
	struct S_Function_Single_Data
	{
		using Function = invalid_t;
		using Method = invalid_t;
		using Request_Args = invalid_t;
		using Bind_Args = invalid_t;
		using Bind_Args_Expand = invalid_t;
		using Bound_Args = invalid_t;
		using CName = invalid_t;
		using RType = invalid_t;

		static constexpr int Lelve = -1;
	};





	template<class T_RType, class ...T_Args, class ...T_Bind_Args>
		requires not_is_invalid
	<typename I_Function_Args_Chack<tuple_t<T_Args...>,
	tuple_t<T_Bind_Args...>>::Request_Args>
	struct S_Function_Single_Data<T_RType(*)(T_Args...), T_Bind_Args...>
	{
	private:
		using Args_Set = I_Function_Args_Chack<tuple_t<T_Args...>,
			tuple_t<T_Bind_Args...>>;
	public:
		using Method = Method_Core<T_RType(*)(T_Args...)>;
		using Function = Function_Core<Method>;


		using RequestArgs = Args_Set::Request_Args;
		using BindArgs = tuple_t<T_Bind_Args...>;

		using BindArgs_Expand = Args_Set::Bind_Args;

		using BoundArgs = BindArgs;

		using CName = invalid_t;
		using RType = T_RType;

		static constexpr int Lelve = 0;

	};

	template<class T_CName, class T_RType, class ...T_Args, class ...T_Bind_Args>
		requires not_is_invalid<typename I_Function_Args_Chack<tuple_t<T_Args...>,
	tuple_t<T_Bind_Args...>>::Request_Args>
	struct S_Function_Single_Data<T_RType(T_CName::*)(T_Args...), T_Bind_Args...> :
		public S_Function_Single_Data<T_RType(*)(T_Args...), T_Bind_Args...>
	{
		using Method = Method_Core<T_RType(T_CName::*)(T_Args...)>;
		using Function = invalid_t;
		using CName = T_CName;

	};


	template<class T_Dedicated_Point, class T_CName, class T_RType, class ...T_Args, class ...T_Bind_Args>
		requires not_is_invalid<typename I_Function_Args_Chack<tuple_t<T_Args...>,
		tuple_t<T_Bind_Args...>>::Request_Args>
			&& convertible_to<T_Dedicated_Point, T_CName>
	struct S_Function_Single_Data<T_Dedicated_Point*, T_RType(T_CName::*)(T_Args...), T_Bind_Args...> :
		public S_Function_Single_Data<T_RType(T_CName::*)(T_Args...), T_Bind_Args...>
	{
		using Parent = S_Function_Single_Data<T_RType(T_CName::*)(T_Args...), T_Bind_Args...>;

		using Function = Function_Core<typename Parent::Method>;
	};


	template<class ...TP_Method_Inner, class ...T_Bind_Args>
		requires not_is_invalid<typename I_Function_Args_Chack<typename S_Function_Single_Data<TP_Method_Inner...>::RequestArgs,
			tuple_t<T_Bind_Args...>>::Request_Args>
	struct S_Function_Single_Data<Method_Core<TP_Method_Inner...>, T_Bind_Args...> :
		public S_Function_Single_Data<TP_Method_Inner...>
	{
	private:
		using Parent = S_Function_Single_Data<TP_Method_Inner...>;
		using Args_Set = I_Function_Args_Chack<typename Parent::RequestArgs,
			tuple_t<T_Bind_Args...>>;
	public:

		using Method = Method_Core<Method_Core<TP_Method_Inner...>>;
		using BindArgs = tuple_t<T_Bind_Args...>;
		using BindArgs_Expand = Args_Set::Bind_Args;
		using RequestArgs = Args_Set::Request_Args;
		using BoundArgs = U_Merge_Element_t<T_Bind_Args..., typename Parent::BoundArgs>;

		static constexpr int Lelve = Parent::Lelve + 1;
	};

	template<class T_Dedicated_Point, class ...TP_Method_Inner, class ...T_Bind_Args>
		requires not_is_invalid<typename S_Function_Single_Data<Method_Core<TP_Method_Inner...>, T_Bind_Args...>::RequestArgs> &&
	convertible_to<T_Dedicated_Point,typename  S_Function_Single_Data<Method_Core<TP_Method_Inner...>, T_Bind_Args...>::CName>
	struct S_Function_Single_Data<T_Dedicated_Point*, Method_Core<TP_Method_Inner...>, T_Bind_Args...> :
		public S_Function_Single_Data<Method_Core<TP_Method_Inner...>, T_Bind_Args...>
	{
		using Parent = S_Function_Single_Data<Method_Core<TP_Method_Inner...>, T_Bind_Args...>;
		using Function = Function_Core<typename Parent::Method>;
	};

	template<class ...TP_Function_Inner, class ...T_Bind_Args>
		requires not_is_invalid<typename I_Function_Args_Chack<
			typename S_Function_Single_Data<Function_Core<TP_Function_Inner...>>::RequestArgs,
			tuple_t<T_Bind_Args...>>::Request_Args>
	struct S_Function_Single_Data<Function_Core<TP_Function_Inner...>, T_Bind_Args...> :
		public S_Function_Single_Data<TP_Function_Inner...>
	{
	private:
		using Parent = S_Function_Single_Data<TP_Function_Inner...>;
		using Args_Set = I_Function_Args_Chack<typename Parent::RequestArgs,
			tuple_t<T_Bind_Args...>>;
	public:

		using Method = Method_Core<Method_Core<TP_Function_Inner...>>;
		using Function = Function_Core<Function_Core<TP_Function_Inner...>>;
		using BindArgs = tuple_t<T_Bind_Args...>;
		using BindArgs_Expand = Args_Set::Bind_Args;
		using RequestArgs = Args_Set::Request_Args;
		using BoundArgs = U_Merge_Element_t<T_Bind_Args...,typename Parent::BoundArgs>;

		static constexpr int Lelve = Parent::Lelve + 1;
	};


}
