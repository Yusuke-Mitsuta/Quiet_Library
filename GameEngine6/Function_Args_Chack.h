#pragma once

#include"Tuple.h"
#include"Expand.h"

namespace N_Function
{


	template<class T_Request_Args, class T_Bind_Args>
	struct I_Function_Args_Chack
	{
		using type = invalid_t;
	};
	
	//�d�l
	//[T_Request_Args]��[T_Bind_Args]����납���r���A
	//�@�݊����̂���^�����肷��B
	//
	// �e���v���[�g
	// [T_Request_Args]�F�v����������̌^(tuple_tp)
	// [T_Bind_Args]�F�Z�b�g��������̌^(tuple_t)
	// 
	//�⑫
	// �݊����̂���^�̒�`�́A[N_Tuple::S_Parameter]�̓��ꉻ�ɂĒ�`���s��
	//
	template<class T_Request_Args, class T_Bind_Args>
		requires requires
	{
		requires N_Tuple::is_Tuple_t<T_Request_Args>;
		requires N_Tuple::is_Tuple_t<T_Bind_Args>;
	}
	struct I_Function_Args_Chack<T_Request_Args,T_Bind_Args>
	{
	private:


		template<class T_Request_Args_Tuple,
			class T_Bind_Args_Tuple,
			bool t_constructible_from,
			bool t_Bind_Args_Expand,
			class ...T_Bind_Args>
		struct S_Function_Args_Chack;

		//�d�l
		// [T_Bind_Args]��[invalid_t]�݂̂ŁA[T_Bind_Args_Tuple]���Ō�܂Ŕ��肵����ƁA
		//���萬���Ƃ���
		template<class T_Request_Args_Tuple,
			class T_Bind_Args_Tuple,
			class ...T_Bind_Args>
		using U_Function_Args_Chack_Next =
			S_Function_Args_Chack<T_Request_Args_Tuple, T_Bind_Args_Tuple,
			std::constructible_from<std::remove_reference_t<typename T_Request_Args_Tuple::type>, typename T_Bind_Args_Tuple::type, T_Bind_Args...> ||
			std::constructible_from<std::remove_pointer_t<typename T_Request_Args_Tuple::type>, typename T_Bind_Args_Tuple::type, T_Bind_Args...> ,
			is_invalid_not<typename N_Tuple::S_Parameter<typename T_Bind_Args_Tuple::type>::tuple>,
			typename T_Bind_Args_Tuple::type, T_Bind_Args...>::type;

		template<class T_Request_Args_Tuple,
			class T_Bind_Args_Tuple,
			class ...T_Bind_Args>
		using U_Function_Args_Chack_Next1 =
			S_Function_Args_Chack<T_Request_Args_Tuple, T_Bind_Args_Tuple,
			std::constructible_from<std::remove_reference_t<typename T_Request_Args_Tuple::type>, typename T_Bind_Args_Tuple::type, T_Bind_Args...> ||
			std::constructible_from<std::remove_pointer_t<typename T_Request_Args_Tuple::type>, typename T_Bind_Args_Tuple::type, T_Bind_Args...>,
			is_invalid_not<typename N_Tuple::S_Parameter<typename T_Bind_Args_Tuple::type>::tuple>,
			typename T_Bind_Args_Tuple::type, T_Bind_Args...>;


		template<class T_Request_Args_Tuple,
			class T_Bind_Args_Tuple,
			bool t_constructible_from,
			bool t_Bind_Args_Expand>
			requires (is_invalid<typename T_Bind_Args_Tuple::type>)
		struct S_Function_Args_Chack<T_Request_Args_Tuple, T_Bind_Args_Tuple, t_constructible_from, t_Bind_Args_Expand, invalid_t>
		{
			using type = T_Request_Args_Tuple::reverse;
		};

		//�d�l
		// [T_Bind_Args]���c���Ă����Ԃ�[T_Bind_Args_Tuple]���Ō�܂Ŕ��肵����ƁA
		//���莸�s�Ƃ���
		template<class T_Request_Args_Tuple,
			class T_Bind_Args_Tuple,
			bool t_constructible_from,
			bool t_Bind_Args_Expand,
			class ...T_Bind_Args>
		requires requires
		{
			requires is_invalid<typename T_Bind_Args_Tuple::type>;
			requires (sizeof...(T_Bind_Args) > 0);
		}
		struct S_Function_Args_Chack<T_Request_Args_Tuple, T_Bind_Args_Tuple, t_constructible_from, t_Bind_Args_Expand, invalid_t,T_Bind_Args...>
		{
			using type = invalid_t;
		};


		//�d�l
		//�v����������̌^�ɑ΂��āA[T_Bind_Args...]�̌^�Ő����ł������ꍇ�̓���
		// [T_Bind_Args...]�����p���A[T_Bind_Args_Tuple]�����ɐi�߂�
		//
		//�⑫
		//[U_Function_Args_Chack_Next]���ŁA���p����[T_Bind_Args...]�ɑ΂��āA
		// [T_Bind_Args_Tuple]�����ɐi�߂��ۂ̑I�𒆂̌^��ǉ�����B
		template<class T_Request_Args_Tuple,
			class T_Bind_Args_Tuple,
			class ...T_Bind_Args>
		requires requires
		{
			requires is_invalid_not<typename T_Bind_Args_Tuple::type>;
		}
		struct S_Function_Args_Chack<T_Request_Args_Tuple, T_Bind_Args_Tuple, false, false, T_Bind_Args...>
		{
			using type = U_Function_Args_Chack_Next<T_Request_Args_Tuple,
				typename T_Bind_Args_Tuple::next,T_Bind_Args...>;
		};

		//�d�l
		//�v����������̌^�ɑ΂��āA[T_Bind_Args...]�̌^�Ő����ł���ꍇ�̓���
		// [T_Bind_Args...]�����Z�b�g���A[T_Request_Args_Tuple][T_Bind_Args_Tuple]�����̔���ɐi�߂�A
		template<class T_Request_Args_Tuple,
			class T_Bind_Args_Tuple,
			bool t_Bind_Args_Expand,
			class ...T_Bind_Args>
			requires requires
		{
			requires is_invalid_not<typename T_Bind_Args_Tuple::type>;
		}
		struct S_Function_Args_Chack<T_Request_Args_Tuple,T_Bind_Args_Tuple,true,t_Bind_Args_Expand,T_Bind_Args...>
		{

			template<class T = typename S_Function_Args_Chack<T_Request_Args_Tuple, T_Bind_Args_Tuple, false, t_Bind_Args_Expand,
				T_Bind_Args...>::type>
			struct S_last_args_chack
			{
				using type = typename S_Function_Args_Chack<T_Request_Args_Tuple, T_Bind_Args_Tuple, false, t_Bind_Args_Expand,
					T_Bind_Args...>::type;
			};

			template<>
			struct S_last_args_chack<invalid_t>
			{
				using type = U_Function_Args_Chack_Next<
					typename T_Request_Args_Tuple::next,
					typename T_Bind_Args_Tuple::next>;

				using type3 = U_Function_Args_Chack_Next1<
					typename T_Request_Args_Tuple::next,
					typename T_Bind_Args_Tuple::next>;
			};

			using type = S_last_args_chack<>::type;
			using type2 = S_last_args_chack<>;

		};

		//�d�l
		//�݊����̂���^�̒�`������Ă���ꍇ�A���̌`�ɕϊ������{����
		// 
		//�⑫
		// �݊����̂���^�̒�`�́A[N_Tuple::S_Parameter]�̓��ꉻ�ɂĒ�`���s��
		template<class T_Request_Args_Tuple,
			class T_Bind_Args_Tuple,
			class T_Front_Bind_Args,
			class ...T_Bind_Args>
		requires requires
		{
			requires is_invalid_not<typename T_Bind_Args_Tuple::type>;
		}
		struct S_Function_Args_Chack<T_Request_Args_Tuple,T_Bind_Args_Tuple,false, true, T_Front_Bind_Args,T_Bind_Args...>
		{
			using convert = N_Tuple::S_Parameter<T_Front_Bind_Args>::tuple;
		
			using insert_bind_args = N_Tuple::U_Insert_tuple_expand<typename T_Bind_Args_Tuple::remove, convert>;
		
			using type = U_Function_Args_Chack_Next<T_Request_Args_Tuple, insert_bind_args, T_Bind_Args...>;
		};

	public:

		using type =U_Function_Args_Chack_Next<typename T_Request_Args::reverse,
			typename T_Bind_Args::reverse>;

		using type1 = U_Function_Args_Chack_Next1<typename T_Request_Args::reverse,
			typename T_Bind_Args::reverse>;
	};

}
