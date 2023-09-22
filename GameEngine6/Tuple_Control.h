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
		using Remove = U_Remove<T_Tuple>;

		//先頭の要素を選択する
		using Flnot = U_Flnot<T_Tuple>;

		//最後の要素を選択する
		using Back = U_Back<T_Tuple>;

		//並び順を反転させる
		using Reverse = U_Reverse<T_Tuple>;

	};

	template<same_as_template_type<Head_t> T_Head, class T, same_as_template_type<Tail_t> T_Tail>
	struct Control_tp :
		_Control_p<Tuple_tp<T_Head, T, T_Tail>>
	{
	private:
		using T_Tuple_p = Tuple_tp<T_Head, T, T_Tail>;
		using Control = _Control_p<T_Tuple_p>;
		template<class T_Select_Tuple_t>
		using Select_Tuple_t = typename S_Parameter<T_Select_Tuple_t>::Type;
	public:
		//選択している要素の型を返す
		using type = Select_Tuple_t<T_Tuple_p>;

		using Next_t = Select_Tuple_t<U_Next<T_Tuple_p>>;
		using Prev_t = Select_Tuple_t<U_Prev<T_Tuple_p>>;
		using Flont_t = Select_Tuple_t<U_Flnot<T_Tuple_p>>;
		using Back_t = Select_Tuple_t<U_Back<T_Tuple_p>>;

	};

	template<same_as_template_value<Head_v> T_Head, auto _Value, same_as_template_value<Tail_v> T_Tail>
	struct Control_vp :
		_Control_p<Tuple_vp<T_Head, _Value, T_Tail>>
	{
	private:
		using T_Tuple_v = Tuple_vp<T_Head, _Value, T_Tail>;
		using Control = _Control_p<T_Tuple_v>;

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


	template<>
	struct _Control_p<Tuple_tp<Head_t<>, std::nullopt_t, Tail_t<>>>
	{
	private:
		using r_type = Tuple_tp<Head_t<>, std::nullopt_t, Tail_t<>>;
	public:
		static constexpr size_t Size_Head = 0;
		static constexpr size_t Size_Tail = 0;
		static constexpr size_t Size = 0;
		using Next = r_type;
		using Prev = r_type;
		using Remove = r_type;
		using Flnot = r_type;
		using Back = r_type;
		using Reverse = r_type;
	};

	template<>
	struct _Control_p<Tuple_vp<Head_v<>, std::nullopt, Tail_v<>>>
	{
	private:
		using r_type = Tuple_vp<Head_v<>, std::nullopt, Tail_v<>>;
	public:
		static constexpr size_t Size_Head = 0;
		static constexpr size_t Size_Tail = 0;
		static constexpr size_t Size = 0;
		using Next = r_type;
		using Prev = r_type;
		using Remove = r_type;
		using Flnot = r_type;
		using Back = r_type;
		using Reverse = r_type;
	};

	template<>
	struct Control_tp<Head_t<>, std::nullopt_t, Tail_t<>>
		:_Control_p<Tuple_tp<Head_t<>, std::nullopt_t, Tail_t<>>>
	{
		using type = std::nullopt_t;
		using Next_t = type;
		using Prev_t = type;
		using Flont_t = type;
		using Back_t = type;
	};

	template<>
	struct Control_vp<Head_v<>,std::nullopt,Tail_v<>> :
		_Control_p<Tuple_vp<Head_v<>, std::nullopt, Tail_v<>>>
	{
		static constexpr auto value = std::nullopt;

		static constexpr auto Next_v =value;
		static constexpr auto Prev_v =value;
		static constexpr auto Flont_v = value;
		static constexpr auto Back_v = value;

	};


}