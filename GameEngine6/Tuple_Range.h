#pragma once

#include"Tuple_Declare.h"
#include"SwapType.h"

namespace N_Tuple
{
	//仕様
	//[T_Tuple]の[t_Point_1]と[t_Point_2]の間の要素を取得する
	//[t_Point2]が設定されない場合、現在の選択位置を指定する
	template<class T_Tuple,size_t t_Point_1, size_t t_Point_2= S_Parameter<T_Tuple>::Size_Head>
		requires is_Element<T_Tuple, t_Point_1>&& is_Element<T_Tuple, t_Point_2>
	struct I_Range
	{
	private:

		using Swap_v = U_Swap_v<t_Point_1, t_Point_2, (t_Point_2 < t_Point_1)>;

		static constexpr int min = Swap_v::_1;
		static constexpr int max = Swap_v::_2;

		template<class T_Base, int t_Count = 0, class T_Center = Tuple_t<>>
		struct S_Range;

		//仕様
		//[t_Swap_Num_1]番目と[t_Swap_Num_2]番目が同じ値を指すとき
		template<class ...T_Types, int t_Count>
			requires (min == max)
		struct S_Range< Tuple_t<T_Types...>, t_Count,Tuple_t<>>
		{
			using Type = Tuple_t<U_Element_t<min, Tuple_t<T_Types...>>>;
		};

		//仕様
		//[mix]の値になるまでカウントを進める
		template<class T_Next_Type, class ...T_Types, int t_Count>
			requires (min > t_Count) && (min != max)
		struct S_Range<Tuple_t<T_Next_Type, T_Types...>, t_Count , Tuple_t<>>
		{
			using Type =typename S_Range<Tuple_t<T_Types...>, t_Count + 1>::Type;
		};

		//仕様
		//[mix]~[max]の場合値を抜き出す
		template< class T_Next_Type, class ...T_Types, int t_Count,  class ...T_Center_Types>
			requires (min <= t_Count) && (max >= t_Count) && (min != max)
		struct S_Range<Tuple_t<T_Next_Type, T_Types...>, t_Count
			, Tuple_t<T_Center_Types...>>
		{
			using Type = typename S_Range<Tuple_t<T_Types...>, t_Count + 1, Tuple_t<T_Center_Types..., T_Next_Type>>::Type;
		};

		template< class ...T_Types, int t_Count, class ...T_Center_Types>
			requires (max <= t_Count) && (min != max)
		struct S_Range<Tuple_t<T_Types...>, t_Count
			, Tuple_t<T_Center_Types...>>
		{
			using Type = Tuple_t<T_Center_Types...>;
		};

		template<class T_Tuple>
		struct S_Action
		{
			using Remove_p = typename I_Remove_Pointer<T_Tuple>::Type;
			using Select_Range = typename S_Tuple_Action<S_Action, Remove_p>::Type;
			using Type = Select_Range;
		};

		template<auto ...t_Value>
		struct S_Action<Tuple_v<t_Value...>>
		{
			using Type = typename S_Tuple_Action<S_Action, Tuple_v<t_Value...>>::Type;
		};

		template<class ...T_Types>
		struct S_Action<Tuple_t<T_Types...>>
		{
			using Type = typename S_Range<Tuple_t<T_Types...>>::Type;
		};

		using Action = S_Tuple_Action<S_Action, T_Tuple>;
		friend struct Action;

	public:

		using Type = typename S_Action<T_Tuple>::Type;

	};

}