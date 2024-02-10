#pragma once

#include"Tuple_Declare.h"
#include"SwapType.h"

namespace N_Tuple
{
	//仕様
	//[T_Tuple]の[t_Point_1]と[t_Point_2]の間の要素を取得する
	//[t_Point2]が設定されない場合、現在の選択位置を指定する
	template<class T_Tuple,size_t t_Point_1, size_t t_Point_2= S_Parameter<T_Tuple>::head_size>
	struct I_Range
	{
	private:

		using Swap_v = U_Swap_v<t_Point_1, t_Point_2, (t_Point_2 < t_Point_1)>;

		static constexpr int min = Swap_v::_1;
		static constexpr int max = Swap_v::_2;

		template<class T_Base, int t_Count = 0, class T_Center = tuple_t<>>
		struct S_Range
		{
			using type = T_Base;
		};

		//仕様
		//[t_Swap_Num_1]番目と[t_Swap_Num_2]番目が同じ値を指すとき
		template<class ...T_Types, int t_Count>
			requires (min == max)
		struct S_Range< tuple_t<T_Types...>, t_Count,tuple_t<>>
		{
			using type = tuple_t<>;
		};

		//仕様
		//[mix]の値になるまでカウントを進める
		template<class T_Next_Type, class ...T_Types, int t_Count>
			requires (min > t_Count) && (min != max)
		struct S_Range<tuple_t<T_Next_Type, T_Types...>, t_Count , tuple_t<>>
		{
			using type =typename S_Range<tuple_t<T_Types...>, t_Count + 1>::type;
		};

		//仕様
		//[mix]~[max]の場合値を抜き出す
		template< class T_Next_Type, class ...T_Types, int t_Count,  class ...T_Center_Types>
			requires (min <= t_Count) && (max > t_Count) && (min != max)
		struct S_Range<tuple_t<T_Next_Type, T_Types...>, t_Count
			, tuple_t<T_Center_Types...>>
		{
			using type = typename S_Range<tuple_t<T_Types...>, t_Count + 1, tuple_t<T_Center_Types..., T_Next_Type>>::type;
		};

		template< class ...T_Types, int t_Count, class ...T_Center_Types>
			requires (max <= t_Count) && (min != max)
		struct S_Range<tuple_t<T_Types...>, t_Count
			,tuple_t<T_Center_Types...>>
		{
			using type = tuple_t<T_Center_Types...>;
		};

		template<class T_Tuple>
		struct S_Action
		{
			using type = 
				S_Range<T_Tuple>::type;
		};

	public:

		using type = S_Tuple_t_Change_Action<S_Action, T_Tuple>::Return_not_p;
	};

}