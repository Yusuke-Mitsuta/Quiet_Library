/*!
 * Tuple_Control.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include<tuple>
#include<optional>

#include"Tuple_Parameter.h"
#include"Tuple_Declare.h"

namespace quiet::N_Tuple
{
	//仕様
	//[T_Tuple]の選択位置の操作、削除の実施
	template<class T_Tuple>
	struct Control_p
	{

		//選択中の要素より前にある要素数
		static constexpr size_t head_size = S_Parameter<T_Tuple>::head_size;

		//選択中の要素より後ろにある要素数
		static constexpr size_t tail_size = S_Parameter<T_Tuple>::tail_size;

		//要素数
		static constexpr size_t size = S_Parameter<T_Tuple>::size;

		//現在選択している番号
		//static constexpr int select = S_Parameter<T_Tuple>::select;

		//現在選択している型より、前の型リスト
		// [tuple_t,v]の場合、先頭の値が選択されている物と見なす
		using head = S_Parameter<T_Tuple>::head;

		//現在選択している型より、前の型リスト
		// [tuple_t,v]の場合、先頭の値が選択されている物と見なす
		using tail = S_Parameter<T_Tuple>::tail;

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

		//[tuple_tp,vp]を[tuple_t,v]に変更する
		//	[tuple_t,v]の場合はそのままとなる
		using remove_p = U_Remove_p<T_Tuple>;

		//[tuple_t,v]を[tuple_tp,vp]に変更する
		//	[tuple_tp,vp]の場合はそのままとなる
		using create_p = U_Create_p<T_Tuple>;

	};

	template<class T_Tuple_t>
	struct Control_t :
		Control_p<T_Tuple_t>
	{
	private:

		using Tuple_t = T_Tuple_t;

		template<class T_Select_Tuple_t>
		using Select_Tuple_t = typename S_Parameter<T_Select_Tuple_t>::type;

	public:

		//選択している要素の型を返す
		using type = Select_Tuple_t<Tuple_t>;

		using next_t = Select_Tuple_t<U_Next<Tuple_t>>;
		using prev_t = Select_Tuple_t<U_Prev<Tuple_t>>;
		using front_t = Select_Tuple_t<U_Front<Tuple_t>>;
		using back_t = Select_Tuple_t<U_Back<Tuple_t>>;

	};

	template<class T_Tuple_v>
	struct Control_v :
		Control_p<T_Tuple_v>
	{
		using Tuple_v = T_Tuple_v;
	private:
		template<class T_Select_Tuple_v>
		static constexpr auto Select_Tuple_v = S_Parameter<T_Select_Tuple_v>::value;
	public:

		//選択している要素を返す
		static constexpr auto value = Select_Tuple_v<Tuple_v>;

		static constexpr auto next_v = Select_Tuple_v<U_Next<Tuple_v>>;
		static constexpr auto prev_v = Select_Tuple_v<U_Prev<Tuple_v>>;
		static constexpr auto front_v = Select_Tuple_v<U_Front<Tuple_v>>;
		static constexpr auto back_v = Select_Tuple_v<U_Back<Tuple_v>>;

	};



}