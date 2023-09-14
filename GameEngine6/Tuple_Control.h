#pragma once

#include<tuple>
#include<optional>

#include"Tuple_Declare.h"
#include"Tuple_Pointer.h"
#include"Tuple_Next.h"
#include"Tuple_Prev.h"
#include"Tuple_Remove.h"

namespace N_Tuple
{
	template<class ..._Types>
	struct _Control;

	//仕様
	//[Tuple_t]の選択位置の操作、削除の実施、及び型の取得
	template<class ...T_Head_Types, class T, class ...T_Tail_Types>
	struct _Control<_Head<T_Head_Types...>, T, _Tail<T_Tail_Types...>>
	{
	private:

		using Change_Tuple = _p<_Head<T_Head_Types...>, T, _Tail<T_Tail_Types...>>;

	public:

		//選択中の要素より前にある要素数
		static constexpr size_t Size_Head = sizeof...(T_Head_Types);

		//選択中の要素より後ろにある要素数
		static constexpr size_t Size_Tail = sizeof...(T_Tail_Types);

		//要素数
		static constexpr size_t Size = Size_Head + Size_Tail + 1;

		//次の要素を選択する
		using Next = typename _Next<Change_Tuple>::Type;

		//前の要素を選択する
		using Prev = typename _Prev<Change_Tuple>::Type;

		//選択している要素を削除する
		using Remove = typename _Remove<Change_Tuple>::Type;

		//先頭の要素を選択する
		using Flnot = typename Pointer<0, Change_Tuple>::Type;

		//最後の要素を選択する
		using Back = typename Pointer<Size-1, Change_Tuple>::Type;

		//選択している要素の型を返す
		using Type = T;

	};

	template<>
	struct _Control<_Head<>,_Tail<>>
	{
		static constexpr size_t Size = 0;
		static constexpr size_t Size_Head = 0;
		static constexpr size_t Size_Tail = 0;
		using Flnot= std::nullopt_t;
		using Back = std::nullopt_t;
		using Next = std::nullopt_t;
		using Prev = std::nullopt_t;
		using Flnot= std::nullopt_t;
		using Back = std::nullopt_t;
		using Remove = std::nullopt_t;
		using Select = std::nullopt_t;
		using Type = _p<>;
	};

}