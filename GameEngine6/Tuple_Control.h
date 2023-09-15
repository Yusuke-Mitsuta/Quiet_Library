#pragma once

#include<tuple>
#include<optional>

#include"Tuple_Parameter.h"
#include"Tuple_Declare.h"
#include"Tuple_Select.h"
#include"Tuple_Next.h"
#include"Tuple_Prev.h"
#include"Tuple_Remove.h"

namespace N_Tuple
{
	//仕様
	//[T_Tuple]の選択位置の操作、削除の実施
	template<class T_Tuple>
	struct _Control
	{

		//選択中の要素より前にある要素数
		static constexpr size_t Size_Head = S_Parameter<T_Tuple>::Size_Head;

		//選択中の要素より後ろにある要素数
		static constexpr size_t Size_Tail = S_Parameter<T_Tuple>::Size_Tail;

		//要素数
		static constexpr size_t Size = S_Parameter<T_Tuple>::Size;

		//次の要素を選択する
		using Next = U_Next<T_Tuple>;

		//前の要素を選択する
		using Prev = U_Prev<T_Tuple>;

		//選択している要素を削除する
		using Remove = typename I_Remove<T_Tuple>::Type;

		//先頭の要素を選択する
		using Flnot = U_Flnot<T_Tuple>;

		//最後の要素を選択する
		using Back = U_Back<T_Tuple>;

		//並び順を反転させる
		using Reverse = U_Reverse<T_Tuple>;

	};

	template<class T_Tuple_t>
	struct _Control_t :
		public _Control<T_Tuple_t>
	{
	private:
		using Control = _Control<T_Tuple_t>;

		template<class T_Select_Tuple_t>
		using Select_Tuple_t = typename S_Parameter<T_Select_Tuple_t>::Type;
	public:
		//選択している要素の型を返す
		using Type = Select_Tuple_t<T_Tuple_t>;

		using Next_t = Select_Tuple_t<U_Next<T_Tuple_t>>;
		using Prev_t = Select_Tuple_t<U_Prev<T_Tuple_t>>;
		using Flont_t = Select_Tuple_t<U_Flnot<T_Tuple_t>>;
		using Back_t = Select_Tuple_t<U_Back<T_Tuple_t>>;

	};

	template<class T_Tuple_v>
	struct _Control_v :
		public _Control<T_Tuple_v>
	{
	private:
		using Control = _Control<T_Tuple_v>;

		template<class T_Select_Tuple_v>
		static constexpr auto Select_Tuple_v = S_Parameter<T_Select_Tuple_v>::value;
	public:
		//選択している要素を返す
		static constexpr auto value = Select_Tuple_v<T_Tuple_v>;

		static constexpr auto Next_v = Select_Tuple_v<U_Next<T_Tuple_v>>;
		static constexpr auto Prev_v = Select_Tuple_v<U_Prev<T_Tuple_v>>;
		static constexpr auto Flont_v = Select_Tuple_v<U_Flnot<T_Tuple_v>>;
		static constexpr auto Back_v = Select_Tuple_v<U_Back<T_Tuple_v>>;

	};


}