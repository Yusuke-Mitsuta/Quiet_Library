#pragma once

#include"Tuple.h"
#include"Expand.h"

namespace N_Function
{


	template<class T_Request_Args,class T_Bind_Args>
	struct I_Function_Args_Chack
	{
	//private:

		//�d�l
		//T_Request_Args,T_Bind_Args�̒��g��K���ɓW�J�������ʂ�Ԃ�
		template<class T_Result_Request_Args, class T_Result_Bind_Args>
		struct S_Result
		{
			using Request_Args = T_Result_Request_Args;
			using Bind_Args = T_Result_Bind_Args;
		};


		//�d�l
		//[T == invalid_t]�Ȃ�[T_Next_Type::type]
		//[T != invalid_t]�Ȃ�[T]��Ԃ�
		template<class T,class T_Next_Type>
		struct S_Next
		{
			using type = T;
		};

		template<class T_Next_Type>
		struct S_Next<invalid_t,T_Next_Type>
		{
			using type = T_Next_Type::type;
		};

		//�d�l
		//[T_Request_Args]�v����������̌���,[T_Bind_Args]�̌�납������̌^�𐸍�����
		//[T_Request_Args]�y�сA[T_Bind_Args]�̈����̌^���������Ȃ��ꍇ[S_Expand]�ɂ��W�J���ēx�A�^�̐������s��
		//
		//�e���v���[�g
		//T_Request_Args::�v����������̕��т𔽓]�������^
		//T_Bind_Args::�w�肷������̕��т𔽓]�������^
		//t_End_fg::T_Bind_Args���Ō�܂Ő����������̃t���O
		template<class T_Request_Args =typename T_Request_Args::reverse, class T_Bind_Args =typename T_Bind_Args::reverse::front,
			bool t_End_fg = is_invalid<typename T_Bind_Args::type>>
		struct S_Args_Chack
		{
			using type = invalid_t;
		};

		//�d�l
		//[T_Tuple_t::type]��[S_Expand]�ɂ��W�J�A���]�����A[T_Tuple_t::type]�Ɠ���ւ���
		template<class T_Tuple_t>
		struct S_Expand_Change
		{
			using type = N_Tuple::U_Change_tuple_expand<T_Tuple_t,
				typename S_Expand<typename T_Tuple_t::type>::type::reverse>;
		};

		//�d�l
		//[check_concept]�̏����ɏ]���ēW�J����[T_Args]��[T_Args_List]��
		//���肵�A��v���Ȃ���΁A[T_Args_List]�̑I���ʒu��i�߂čēx���肷��A
		// ��v�����[S_Args_Chack]�����s���A��������Ό��ʂ��A
		// ���s�����[T_Args_List]�̑I���ʒu��i�߂čēx���肷��
		//���̌��ʁA[T_Args_List]���S�Ă�[T_Args]�ƈ�v���Ȃ���΁A[invalid_t]��Ԃ�
		template<template<class,class>class check_concept,class T_Args,class T_Args_List,
			bool t_Next_Fg= check_concept<typename T_Args::type,typename T_Args_List::type::type>::value>
		struct S_Expand_Args_Check
		{
			using type = S_Expand_Args_Check<check_concept, T_Args,typename T_Args_List::next>::type;
		};

		//�d�l
		//[T_Args]=[Bind_Args],[T_Args_List::type]=[Request_Args]
		//�Ƃ�[S_Args_Chack]�����s����
		//��������Βl���A���s�����[T_Args_List]��i�߂�
		template<class T_Args, class T_Args_List>
		struct S_Expand_Args_Check<std::is_constructible,T_Args, T_Args_List,true>
		{
			using n = T_Args_List;
			using result_type= S_Args_Chack<typename T_Args_List::type, T_Args>::type;
			using type = S_Next<result_type, S_Expand_Args_Check<std::is_constructible, T_Args,typename T_Args_List::next>>::type;
		};


		//�d�l
		//[T_Args]=[Request_Args],[T_Args_List::type]=[Bind_Args]
		//�Ƃ�[S_Args_Chack]�����s����
		//��������Βl���A���s�����[T_Args_List]��i�߂�
		template< class T_Args, class T_Args_List>
		struct S_Expand_Args_Check<is_convertible_from, T_Args, T_Args_List, true>
		{
			using result_type = S_Args_Chack<T_Args,typename T_Args_List::type>::type;
			using type = S_Next<result_type, S_Expand_Args_Check<is_convertible_from, T_Args, typename T_Args_List::next>>::type;

		};

		//�d�l
		//[T_Args_List]�̍Ō�܂Ő���������������Ȃ���΁A[ invalid_t]�Ƃ���
		template<template<class, class>class check_concept, class T_Args, class T_Head>
		struct S_Expand_Args_Check<check_concept,T_Args, tuple_tp<T_Head,invalid_t,tuple_t<>>>
		{
			using type = invalid_t;
		};

		//�d�l
		//[T_Request_Args::type],[T_Bind_Args::type]�œW�J�o���邩���肵�A�\�ł���ΓW�J��
		//�W�J��̃��X�g�ƁA�W�J���ĂȂ�����[T_Request_Args_List]or[T_Bind_Args_List]�̑S�Ă̌^�Ɣ��肷��B
		//���肪���s����΁A�W�J�������̌^��list�ɓW�J��̌^��ǉ����A�W�J��̌^���X�ɓW�J�o���邩���肷��B
		//�W�J�ł��Ȃ��A�^�̔���Ɏ��s�����[std:;nullopt_t]��Ԃ�
		template<class T_Request_Args, class T_Bind_Args, class T_Request_Args_List = tuple_t<T_Request_Args>, class T_Bind_Args_List = tuple_t<T_Bind_Args>, bool t_Loop_fg =(!is_expand<typename T_Request_Args::type>)|| (!is_expand<typename T_Bind_Args::type>)>
		struct S_Expand_Args
		{
			using type = invalid_t;
		};


		//�d�l
		//[T_Request_Args::type]�W�J���A�W�J��̃��X�g�ƁA[T_Bind_Args_List]�̑S�Ă̌^�Ɣ��肷��B
		//���肪���s����΁A[T_Request_Args_List]�ɓW�J��̌^��ǉ����A�W�J��̌^���X�ɓW�J�o���邩���肷��B
		template<class T_Request_Args, class T_Bind_Args, class T_Request_Args_List, class T_Bind_Args_List>
			requires (is_expand<typename T_Request_Args::type>)
		struct S_Expand_Args<T_Request_Args,T_Bind_Args, T_Request_Args_List, T_Bind_Args_List,true>
		{
			using Expand_Request_Args = typename S_Expand_Change<T_Request_Args>::type;

			using type = S_Next<typename S_Expand_Args_Check<
				is_convertible_from,Expand_Request_Args,
				T_Bind_Args_List>::type,
				S_Expand_Args<Expand_Request_Args, T_Bind_Args, N_Tuple::U_Merge< T_Request_Args_List, Expand_Request_Args>, T_Bind_Args_List>>::type;

		};

		//�d�l
		//[T_Bind_Args::type]�W�J���A�W�J��̃��X�g�ƁA[T_Request_Args_List]�̑S�Ă̌^�Ɣ��肷��B
		//���肪���s����΁A[T_Bind_Args_List]�ɓW�J��̌^��ǉ����A�W�J��̌^���X�ɓW�J�o���邩���肷��B
		template<class T_Request_Args, class T_Bind_Args, class T_Request_Args_List, class T_Bind_Args_List>
			requires (is_expand<typename T_Bind_Args::type>)
		struct S_Expand_Args<T_Request_Args, T_Bind_Args, T_Request_Args_List, T_Bind_Args_List, true>
		{
			using Expand_Bind_Args = typename S_Expand_Change<T_Bind_Args>::type;
			using Expand_Bind_Args1 = typename S_Expand_Change<T_Bind_Args>;

			//using type = invalid_t;


			using type1 = typename S_Expand_Args_Check<
				std::is_constructible,
				Expand_Bind_Args
				, T_Request_Args_List>;

			using type = S_Next<typename S_Expand_Args_Check<
				std::is_constructible,
				Expand_Bind_Args
				, T_Request_Args_List>::type,
				S_Expand_Args<T_Request_Args,Expand_Bind_Args, T_Request_Args_List,N_Tuple::U_Merge<T_Bind_Args_List, Expand_Bind_Args>>>::type;

		};

		//�d�l
		//[T_Request_Args::type]�W�J���A�W�J��̃��X�g�ƁA[T_Bind_Args_List]�̑S�Ă̌^�Ɣ��肷��B
		//���肪���s����΁A[T_Request_Args_List]�ɓW�J��̌^��ǉ����A
		// [T_Bind_Args::type]�W�J���A�W�J��̃��X�g�ƁA[T_Request_Args_List]�̑S�Ă̌^�Ɣ��肷��B
		//���肪���s����΁A[T_Bind_Args_List]�ɓW�J��̌^��ǉ����A[T_Request_Args::type],[T_Bind_Args::type]�̓W�J��̌^���X�ɓW�J�o���邩���肷��B
		template<class T_Request_Args, class T_Bind_Args, class T_Request_Args_List, class T_Bind_Args_List>
			requires (is_expand<typename T_Request_Args::type>) && (is_expand<typename T_Bind_Args::type>)
		struct S_Expand_Args<T_Request_Args, T_Bind_Args, T_Request_Args_List, T_Bind_Args_List, true>
		{
			using Expand_Request_Args = typename S_Expand_Change<T_Request_Args>::type;
			using Expand_Bind_Args = typename S_Expand_Change<T_Bind_Args>::type;

			using Request_Args_List_Merge = N_Tuple::U_Merge<T_Request_Args_List,Expand_Request_Args>;
			using Bind_Args_List_Merge = N_Tuple::U_Merge<T_Bind_Args_List, Expand_Bind_Args>;

			using Expand_Args_Check = S_Next<typename S_Expand_Args_Check<
				is_convertible_from, Expand_Request_Args
				, Bind_Args_List_Merge>::type,
				S_Expand_Args_Check<std::is_constructible, Expand_Bind_Args
				, T_Request_Args_List>>;

			using type = S_Next<typename Expand_Args_Check::type,
				S_Expand_Args<Expand_Request_Args, Expand_Bind_Args, Request_Args_List_Merge, Bind_Args_List_Merge >>::type;
		};



		//�d�l
		//[T_Request_Args::type]��[T_Bind_Args::type]����ϊ��\�Ȏ��A
		//[T_Request_Args],[T_Bind_Args]���P�i�߂�
		template<class T_Request_Args, class T_Bind_Args>
			requires convertible_to<typename T_Bind_Args::type, typename T_Request_Args::type>
		struct S_Args_Chack<T_Request_Args, T_Bind_Args, false>
		{
			using type = S_Args_Chack<typename T_Request_Args::next, typename T_Bind_Args::next>::type;
		};

		//�d�l
		//[T_Request_Args::type]��[T_Bind_Args::type]����ϊ��s�\�Ȏ��A[S_Expand]�ɂ��W�J���ēx�A�^�̐������s��
		template<class T_Request_Args, class T_Bind_Args>
			requires not_convertible_to<typename T_Bind_Args::type, typename T_Request_Args::type>
		struct S_Args_Chack<T_Request_Args, T_Bind_Args, false>
		{
			using type = S_Expand_Args<T_Request_Args, T_Bind_Args>::type;	
			using type1 = S_Expand_Args<T_Request_Args, T_Bind_Args>;	
		};

		//�d�l
		//���肪�����������Aresult���쐬����
		//[T_Request_Args]�͔��]�������̂�߂��A
		//[T_Bind_Args]�͔��]�������̂�߂��A�|�C���^����菜��
		template<class T_Request_Args, class T_Bind_Args>
		struct S_Args_Chack<T_Request_Args, T_Bind_Args, true>
		{
			template<class T_Tuple_p>
			using reverse_and_remove_p =typename T_Tuple_p::reverse::remove_p;

			using type = S_Result<typename T_Request_Args::reverse, typename T_Bind_Args::reverse::remove_p>;
		};

		template<class T>
		struct S_null_chack
		{
			using request_args = T::Request_Args;
			using bind_args = T::Bind_Args;
		};

		template<>
		struct S_null_chack<invalid_t>
		{
			using request_args = invalid_t;
			using bind_args = invalid_t;
		};

	public:
		using type = typename S_Args_Chack<>;

		using request_args = S_null_chack<typename S_Args_Chack<>::type>::request_args;

		using bind_args = S_null_chack<typename S_Args_Chack<>::type>::bind_args;

	};




}
