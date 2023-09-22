#pragma once

#include"Tuple_Declare.h"
#include"Concept.h"

#include"Outer_Change.h"
#include"SwapType.h"

namespace N_Tuple
{

	//�d�l
	//[Type]�̑I���ʒu��[t_Point]�Ɉړ�������
	template<int t_Point, class T_Tuple_t>
	struct I_Select
	{
	private:

		//�d�l
		//�ړI�|�C���g�܂ŋ���[t_Point]��
		//	[+]�ł����[Type::Next],
		//	[-]�ł����[Type::Flont]
		//	[0]�ł���Έړ������ƂȂ�
		template<int t_Point, class T_Tuple_t>
		struct Select_Core
		{
			using type = T_Tuple_t;
		};

		template<int t_Point, class ...T_Head_Types, class T, class ...T_Tail_Types>
			requires(t_Point > 0)
		struct Select_Core<t_Point, Tuple_tp<Head_t<T_Head_Types...>, T, Tail_t<T_Tail_Types...>>>
		{
			using type = Select_Core<t_Point - 1,U_Next<Tuple_tp<Head_t< T_Head_Types...>, T, Tail_t<T_Tail_Types...>>>>::type;
		};

		template<int t_Point, class T_Head_Flont_Type, class ...T_Head_Types, class T, class ...T_Tail_Types>
			requires(t_Point < 0)
		struct Select_Core<t_Point, Tuple_tp<Head_t<T_Head_Flont_Type, T_Head_Types...>, T, Tail_t<T_Tail_Types...>>>
		{
			using type = Select_Core<t_Point + sizeof...(T_Head_Types) + 1, Tuple_tp<Head_t<>, T_Head_Flont_Type, Tail_t<T_Head_Types..., T, T_Tail_Types...>>>::type;
		};


		template<class T_Tuple_t>
		using Pointer_Core_t = typename Select_Core<t_Point - static_cast<int>(S_Parameter<T_Tuple_t>::Size_Head), T_Tuple_t>::type;


		//�d�l
		//�ړI�|�C���g[t_Point]��
		//	[0 <= t_Point <= t_Tuple_Size] ���A
		//	[Type::Type]��[std::nullopt_t]�Ŗ�����ΒT���Ɉڍs
		//		�ł����[std::nullopt_t]�������ĒT���Ɉڍs
		// 
		//	[0 <= t_Point <= t_Tuple_Size] �Ŗ�����΁A[std::nullopt_t]�ɂ��͈͊O����
		template<int t_Point, size_t t_Tuple_Size, class T_Tuple_t ,bool t_Out_Range = (t_Point < 0) || (t_Point >= t_Tuple_Size)>
		struct Select_Range_Judge
		{
			using type = Pointer_Core_t<T_Tuple_t>;
		};

		template<int t_Point, size_t t_Tuple_Size, class ...T_Head_Types , class ...T_Tail_Types>
		struct Select_Range_Judge<t_Point, t_Tuple_Size, Tuple_tp<Head_t<T_Head_Types...>,std::nullopt_t, Tail_t<T_Tail_Types...>>,false>
		{
			using type = Pointer_Core_t<U_Create_p<Tuple_t< T_Head_Types..., T_Tail_Types...>>>;
				
		};

		template<int t_Point, size_t t_Tuple_Size, class ...T_Head_Types, class T, class ...T_Tail_Types>
		struct Select_Range_Judge<t_Point,t_Tuple_Size, Tuple_tp<Head_t<T_Head_Types...>, T, Tail_t<T_Tail_Types...>>,true>
		{
			using Swap_Null = U_Swap_t1<Head_t<T_Head_Types..., T_Tail_Types...>, Head_t<T_Head_Types..., T, T_Tail_Types...>, not_is_nullopt<T>>;

			using Swap_Head = U_Swap_t1<Head_t<>,Swap_Null, (t_Point > 0) >;
			using Swap_Tail = U_Swap_t1< U_Change_Outer<Tail_t, Swap_Null>, Tail_t<>, (t_Point > 0)>;

			using type = Tuple_tp<Swap_Head, std::nullopt_t, Swap_Tail>;

		};

		template<class T_Tuple_t>
		struct S_Action
		{
			using type = typename Select_Range_Judge<t_Point, S_Parameter<T_Tuple_t>::Size, T_Tuple_t>::type;
		};

	public:

		using type = S_Action_Tuple_tp<S_Action, T_Tuple_t>::type;


	};


}
