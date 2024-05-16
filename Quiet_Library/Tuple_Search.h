#pragma once

#include"Tuple_Declare.h"

namespace quiet::N_Tuple
{
	//�d�l
	//[Tuple_t]�ƌ݊����̂���^�̃��X�g����A�w�肵���^�����ԖڂɊ܂܂�邩�T���B
	//
	//�e���v���[�g
	//[T_Search_Tuple]::�w�肵���^��T���A[Tuple_t]�ƌ݊����̂���^
	//[T_Search_Type]::[T_Search_Tuple]����T���^
	template<class T_Search_Tuple, class T_Search_Type>
	struct I_Search_t
	{

		template<class T_Tuple,size_t ...t_hit_Number>
		struct S_Search_t
		{
			using type = tuple_v<t_hit_Number...>;
		};
		
		template<class T_Tuple, size_t ...t_hit_Number>
			requires requires
		{
			requires same_as<typename T_Tuple::front_t, T_Search_Type>;
		}
		struct S_Search_t<T_Tuple,t_hit_Number...>
		{
			using type = S_Search_t<typename T_Tuple::next, 
				t_hit_Number..., T_Tuple::head_size>::type;
		};

		template<class T_Tuple, size_t ...t_hit_Number>
			requires requires
		{
			requires same_as_nor<typename T_Tuple::front_t, T_Search_Type,invalid_t>;
		}
		struct S_Search_t<T_Tuple, t_hit_Number...>
		{
			using type = S_Search_t<typename T_Tuple::next,
				t_hit_Number...>::type;
		};

		using type = S_Search_t<U_Change_Tuple_t<T_Search_Tuple>>::type;

	};

	//�d�l
	//[Tuple_v]�ƌ݊����̂���^�̃��X�g����A�w�肵���l�����ԖڂɊ܂܂�邩�T���B
	//
	//�e���v���[�g
	//[T_Search_Tuple]::�w�肵���l��T���A[Tuple_v]�ƌ݊����̂���^
	//[T_Search_Value]::[T_Search_Tuple]����T���^
	template<class T_Search_Tuple, auto t_Search_Value>
	struct I_Search_v
	{
		using type = I_Search_t<U_Change_Tuple_t<T_Search_Tuple>,
			integral_constant<t_Search_Value>>::type;
	};

}