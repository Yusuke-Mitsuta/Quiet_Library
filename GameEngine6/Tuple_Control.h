#pragma once

#include<tuple>
#include<optional>

#include"Tuple_Parameter.h"
#include"Tuple_Declare.h"

namespace N_Tuple
{
	//仕様
	//[T_Tuple]の選択位置の操作、削除の実施
	template<class T_Tuple>
	struct _Control_p
	{

		//選択中の要素より前にある要素数
		static constexpr size_t head_size = S_Parameter<T_Tuple>::Size_Head;

		//選択中の要素より後ろにある要素数
		static constexpr size_t tail_size = S_Parameter<T_Tuple>::Size_Tail;

		//要素数
		static constexpr size_t size = S_Parameter<T_Tuple>::Size;

		//現在選択している番号
		static constexpr int select = S_Parameter<T_Tuple>::select;

		//次の要素を選択する
		using next = U_Next<T_Tuple>;

		//前の要素を選択する
		using prev = U_Prev<T_Tuple>;

		//選択している要素を削除する
		using remove = U_Remove<T_Tuple>;

		//先頭の要素を選択する
		using front = U_Front<T_Tuple>;

		//最後の要素を選択する
		using back = U_Back<T_Tuple>;

		//並び順を反転させる
		using reverse = U_Reverse<T_Tuple>;

	};

	template<same_as_template_type<tuple_t> T_Head, class T, same_as_template_type<tuple_t> T_Tail>
	struct Control_tp :
		_Control_p<tuple_tp<T_Head, T, T_Tail>>
	{
	private:
		using T_Tuple_p = tuple_tp<T_Head, T, T_Tail>;
		using Control = _Control_p<T_Tuple_p>;
		template<class T_Select_Tuple_t>
		using Select_Tuple_t = typename S_Parameter<T_Select_Tuple_t>::Type;
	public:
		//選択している要素の型を返す
		using type = Select_Tuple_t<T_Tuple_p>;

		using next_t = Select_Tuple_t<U_Next<T_Tuple_p>>;
		using prev_t = Select_Tuple_t<U_Prev<T_Tuple_p>>;
		using front_t = Select_Tuple_t<U_Front<T_Tuple_p>>;
		using back_t = Select_Tuple_t<U_Back<T_Tuple_p>>;

	};

	template<same_as_template_value<tuple_v> T_Head, auto _Value, same_as_template_value<tuple_v> T_Tail>
	struct Control_vp :
		_Control_p<tuple_vp<T_Head, _Value, T_Tail>>
	{
	private:
		using T_Tuple_v = tuple_vp<T_Head, _Value, T_Tail>;
		using Control = _Control_p<T_Tuple_v>;

		template<class T_Select_Tuple_v>
		static constexpr auto Select_Tuple_v = S_Parameter<T_Select_Tuple_v>::value;
	public:
		//選択している要素を返す
		static constexpr auto value = Select_Tuple_v<T_Tuple_v>;

		static constexpr auto next_v = Select_Tuple_v<U_Next<T_Tuple_v>>;
		static constexpr auto prev_v = Select_Tuple_v<U_Prev<T_Tuple_v>>;
		static constexpr auto front_v = Select_Tuple_v<U_Front<T_Tuple_v>>;
		static constexpr auto back_v = Select_Tuple_v<U_Back<T_Tuple_v>>;

	};


	template<>
	struct _Control_p<tuple_tp<tuple_t<>, invalid_t, tuple_t<>>>
	{
	private:
		using r_type = tuple_tp<tuple_t<>, invalid_t, tuple_t<>>;
	public:

		static constexpr size_t head_size = 0;
		static constexpr size_t tail_size = 0;
		static constexpr size_t size = 0;

		using next = r_type;
		using prev = r_type;
		using remove = r_type;
		using front = r_type;
		using back = r_type;
		using reverse = r_type;
	};

	template<>
	struct _Control_p<tuple_vp<tuple_v<>, invalid, tuple_v<>>>
	{
	private:
		using r_type = tuple_vp<tuple_v<>, invalid, tuple_v<>>;
	public:
		static constexpr size_t head_size = 0;
		static constexpr size_t tail_size = 0;
		static constexpr size_t size = 0;
		using next = r_type;
		using prev = r_type;
		using remove = r_type;
		using front = r_type;
		using back = r_type;
		using reverse = r_type;
	};

	template<>
	struct Control_tp<tuple_t<>, invalid_t, tuple_t<>>
		:_Control_p<tuple_tp<tuple_t<>, invalid_t, tuple_t<>>>
	{
		using type = invalid_t;
		using next_t = type;
		using prev_t = type;
		using front_t = type;
		using back_t = type;
	};

	template<>
	struct Control_vp<tuple_v<>,invalid,tuple_v<>> :
		_Control_p<tuple_vp<tuple_v<>, invalid, tuple_v<>>>
	{
		static constexpr auto value = invalid;

		static constexpr auto next_v =value;
		static constexpr auto prev_v =value;
		static constexpr auto front_v = value;
		static constexpr auto back_v = value;

	};

}