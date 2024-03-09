/*!
 * Tuple_Expand.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Tuple_Declare.h"

namespace quiet::N_Tuple
{


	//�d�l
	//�^�v�����̗v�f�̒�����A�^�v���ƌ݊��������^��S�ēW�J����
	//
	// �e���v���[�g
	//[T_Tuple_Data]::�W�J����[Tuple_t]�̌^
	//�⑫
	//[T_Tuple_Data]��[tuple]�ł͂Ȃ������ꍇ[T_Tuple_Data]�^��Ԃ�
	template<class T_Expand_Tuple, size_t t_expand_lelve >
	struct I_Expand
	{
	private:

		template<class T_Result, class T_Tuple, size_t t_remaining_expand_lelve>
		struct S_Expand
		{
			using type = T_Tuple;
		};

		template<class T_Result,class T_Tuple,size_t t_remaining_expand_lelve>
		struct I_Element_Expand
		{
			using type = T_Result;
		};

		template<class ...T_Result, class T_Expand_Type, size_t t_remaining_expand_lelve>
		struct I_Element_Expand<tuple_t<T_Result...>,T_Expand_Type, t_remaining_expand_lelve>
		{
			template<class T_Tuple>
			struct S_Element_Expand
			{
				using type = S_Expand<tuple_t<T_Result...>, T_Tuple, t_remaining_expand_lelve - 1>::type;
			};

			template<>
			struct S_Element_Expand<invalid_t>
			{
				using type = tuple_t<T_Result..., T_Expand_Type>;
			};

			using type = S_Element_Expand<typename S_Parameter<T_Expand_Type>::tuple>::type;
		};

		template<class ...T_Result, class T_Front, class ...Ts, size_t t_remaining_expand_lelve>
			requires (static_cast<bool>(t_remaining_expand_lelve))
		struct S_Expand<tuple_t<T_Result...>, tuple_t<T_Front, Ts...>, t_remaining_expand_lelve>
		{
			using result = I_Element_Expand<tuple_t<T_Result...>, T_Front, t_remaining_expand_lelve>::type;

			using type = S_Expand<result, tuple_t<Ts...>, t_remaining_expand_lelve>::type;
		};

		template<class ...T_Result, class ...Ts, size_t t_remaining_expand_lelve>
		struct S_Expand<tuple_t<T_Result...>,tuple_tp<Ts...> , t_remaining_expand_lelve>
		{
			using type = S_Expand<tuple_t<T_Result...>, typename tuple_tp<Ts...>::remove_p, t_remaining_expand_lelve>::type;
		};



		template<class ...T_Result, class ...Ts, size_t t_remaining_expand_lelve>
			requires (static_cast<bool>(sizeof...(Ts))&& !static_cast<bool>(t_remaining_expand_lelve))
		struct S_Expand<tuple_t<T_Result...>, tuple_t<Ts...>, t_remaining_expand_lelve>
		{
			using type = tuple_t<T_Result..., Ts...>;
		};

		template<class ...T_Result, size_t t_remaining_expand_lelve>
		struct S_Expand<tuple_t<T_Result...>, tuple_t<>, t_remaining_expand_lelve>
		{
			using type = tuple_t<T_Result...>;

		};

	public:
		using type = I_Element_Expand<tuple_t<>, T_Expand_Tuple, t_expand_lelve>::type;

	};
}