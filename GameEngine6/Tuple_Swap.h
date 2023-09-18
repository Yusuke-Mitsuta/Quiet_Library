#pragma once

#include"Tuple_Declare.h"
#include"SwapType.h"

namespace N_Tuple
{

	//�d�l
	//[T_Tuple]��[t_Swap_Num_1]�Ԗڂ�[t_Swap_Num_2]�Ԗڂ̗v�f�����ւ���
	template<class T_Tuple, size_t t_Swap_Num_1, size_t t_Swap_Num_2= S_Parameter<T_Tuple>::Size_Head>
		requires is_Element<T_Tuple, t_Swap_Num_1>&& is_Element<T_Tuple, t_Swap_Num_2>
	struct I_Swap
	{
	private:

		using Swap_v=U_Swap_v< t_Swap_Num_1 , t_Swap_Num_2 ,( t_Swap_Num_2 < t_Swap_Num_1)>;

		static constexpr int min = Swap_v::_1;
		static constexpr int max= Swap_v::_2;

		template<class T_Base, int t_Count = 0, class T_Head = Tuple_t<>, class T_1 = std::nullopt_t, class T_Center = Tuple_t<>>
		struct S_Swap;

		//�d�l
		//[t_Swap_Num_1]�Ԗڂ�[t_Swap_Num_2]�Ԗڂ������l���w���Ƃ�
		template<class ...T_Types, int t_Count , class T_Head , class T_1 ,class T_Center>
			requires (min == max)
		struct S_Swap< Tuple_t<T_Types...>, t_Count, T_Head, T_1, T_Center>
		{
			using Type = Tuple_t<T_Types...>;
		};

		//�d�l
		//[t_Swap_Num_1]�Ԗڂ̒l��{��
		template<class T_Next_Type, class ...T_Types,int t_Count, class ...T_Head_Types, class T_1, class T_Center>
			requires (min > t_Count) && (min != max)
		struct S_Swap<Tuple_t<T_Next_Type, T_Types...>,t_Count,Tuple_t<T_Head_Types...>, T_1
			, T_Center>
		{
			using Type= S_Swap<Tuple_t<T_Types...>,t_Count + 1, Tuple_t<T_Head_Types..., T_Next_Type>, T_1, T_Center>::Type;
		};

		//�d�l
		//[t_Swap_Num_1]�Ԗڂ̒l��I��
		template< class T_Next_Type, class ...T_Types,int t_Count, class ...T_Head_Types, class T_1, class T_Center>
			requires (min == t_Count) && (min != max)
		struct S_Swap<Tuple_t<T_Next_Type, T_Types...>,
			t_Count, Tuple_t<T_Head_Types...>, T_1
			, T_Center>
		{
			using Type = S_Swap<Tuple_t<T_Types...>,t_Count + 1, Tuple_t<T_Head_Types...>, T_Next_Type, T_Center>::Type;
		};

		//�d�l
		//[t_Swap_Num_2]�Ԗڂ̒l��{��
		template<int t_Count, class ...T_Head_Types, class T_1, class ...T_Center_Types, class T_Next_Type, class ...T_Types>
			requires (min < t_Count) && (max > t_Count)
		struct S_Swap<Tuple_t<T_Next_Type, T_Types...>,
			t_Count,Tuple_t<T_Head_Types...>,
			T_1,Tuple_t<T_Center_Types...>>
		{
			using Type = S_Swap<Tuple_t<T_Types...>,t_Count + 1, Tuple_t<T_Head_Types...>, T_1, Tuple_t<T_Center_Types..., T_Next_Type>>::Type;
		};

		//�d�l
		//[t_Swap_Num_1]�Ԗڂ�[t_Swap_Num_2]�Ԗڂ̒l�����ւ���
		template<class T_Next_Type, class ...T_Types,int t_Count, class ...T_Head_Types, class T_1, class ...T_Center_Types>
			requires (min < t_Count) && (max == t_Count)
		struct S_Swap<Tuple_t<T_Next_Type, T_Types...>,
			t_Count,Tuple_t<T_Head_Types...>,
			T_1,Tuple_t<T_Center_Types...>>
		{
			using Type = Tuple_t< T_Head_Types..., T_Next_Type, T_Center_Types..., T_1, T_Types...>;
		};

		template<class T_Tuple>
		struct S_Action
		{
			static constexpr size_t Select_Point = S_Parameter<T_Tuple>::Size_Head;
			using Remove_p = typename I_Remove_Pointer<T_Tuple>::Type;
			using Swap =typename S_Tuple_Action<S_Action, Remove_p>::Type;
			using Creat_p = typename I_Create_Pointer<Swap>::Type;
			using Select = U_Select<Select_Point, Creat_p>;
			using Type = Select;
		};

		template<auto ...t_Value>
		struct S_Action<Tuple_v<t_Value...>>
		{
			using Type= typename S_Tuple_Action<S_Action, Tuple_v<t_Value...>>::Type;
		};

		template<class ...T_Types>
		struct S_Action<Tuple_t<T_Types...>>
		{
			using Type = typename S_Swap<Tuple_t<T_Types...>>::Type;
		};

		using Action = S_Tuple_Action<S_Action, T_Tuple>;
		friend struct Action;

	public:

		using Type = typename S_Action<T_Tuple>::Type;

	};


}