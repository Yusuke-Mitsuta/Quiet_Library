#pragma once

#include"Tuple_Declare.h"
#include"SwapType.h"

namespace N_Tuple
{

	//仕様
	//[T_Tuple]の[t_Swap_Num_1]番目と[t_Swap_Num_2]番目の要素を入れ替える
	template<class T_Tuple, size_t t_Swap_Num_1, size_t t_Swap_Num_2>
		requires is_Element<T_Tuple, t_Swap_Num_1>&& is_Element<T_Tuple, t_Swap_Num_2>
	struct I_Swap
	{
	private:

		using Swap_v=U_Swap_v< t_Swap_Num_1 , t_Swap_Num_2 ,( t_Swap_Num_2 < t_Swap_Num_1)>;

		static constexpr int min = Swap_v::_1;
		static constexpr int max= Swap_v::_2;

		template<class T_Base, int t_Count = 0, class T_Head = tuple_t<>, class T_1 = invalid_t, class T_Center = tuple_t<>>
		struct S_Swap;

		//仕様
		//[t_Swap_Num_1]番目と[t_Swap_Num_2]番目が同じ値を指すとき
		template<class ...T_Types, int t_Count , class T_Head , class T_1 ,class T_Center>
			requires (min == max)
		struct S_Swap< tuple_t<T_Types...>, t_Count, T_Head, T_1, T_Center>
		{
			using type = tuple_t<T_Types...>;
		};

		//仕様
		//[t_Swap_Num_1]番目の値を捜索
		template<class T_Next_Type, class ...T_Types,int t_Count, class ...T_Head_Types, class T_1, class T_Center>
			requires (min > t_Count) && (min != max)
		struct S_Swap<tuple_t<T_Next_Type, T_Types...>,t_Count,tuple_t<T_Head_Types...>, T_1
			, T_Center>
		{
			using type= S_Swap<tuple_t<T_Types...>,t_Count + 1, tuple_t<T_Head_Types..., T_Next_Type>, T_1, T_Center>::type;
		};

		//仕様
		//[t_Swap_Num_1]番目の値を選択
		template< class T_Next_Type, class ...T_Types,int t_Count, class ...T_Head_Types, class T_1, class T_Center>
			requires (min == t_Count) && (min != max)
		struct S_Swap<tuple_t<T_Next_Type, T_Types...>,
			t_Count, tuple_t<T_Head_Types...>, T_1
			, T_Center>
		{
			using type = S_Swap<tuple_t<T_Types...>,t_Count + 1, tuple_t<T_Head_Types...>, T_Next_Type, T_Center>::type;
		};

		//仕様
		//[t_Swap_Num_2]番目の値を捜索
		template<int t_Count, class ...T_Head_Types, class T_1, class ...T_Center_Types, class T_Next_Type, class ...T_Types>
			requires (min < t_Count) && (max > t_Count)
		struct S_Swap<tuple_t<T_Next_Type, T_Types...>,
			t_Count,tuple_t<T_Head_Types...>,
			T_1,tuple_t<T_Center_Types...>>
		{
			using type = S_Swap<tuple_t<T_Types...>,t_Count + 1, tuple_t<T_Head_Types...>, T_1, tuple_t<T_Center_Types..., T_Next_Type>>::type;
		};

		//仕様
		//[t_Swap_Num_1]番目と[t_Swap_Num_2]番目の値を入れ替える
		template<class T_Next_Type, class ...T_Types,int t_Count, class ...T_Head_Types, class T_1, class ...T_Center_Types>
			requires (min < t_Count) && (max == t_Count)
		struct S_Swap<tuple_t<T_Next_Type, T_Types...>,
			t_Count,tuple_t<T_Head_Types...>,
			T_1,tuple_t<T_Center_Types...>>
		{
			using Type = tuple_t< T_Head_Types..., T_Next_Type, T_Center_Types..., T_1, T_Types...>;
		};

		template<class T_Tuple>
		struct S_Action
		{
			using type = S_Swap<T_Tuple>::type;
		};

	public:

		using type =S_Tuple_t_Convert_Action<S_Action, T_Tuple>::type;

	};


}