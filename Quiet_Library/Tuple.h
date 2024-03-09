/*!
 * Tuple.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include<tuple>

#include"Tuple_Declare.h"
#include"Tuple_Class_Declare.h"
#include"Tuple_Type.h"
#include"Tuple_Next.h"
#include"Tuple_Prev.h"
#include"Tuple_Select.h"
#include"Tuple_Remove.h"
#include"Tuple_Value.h"
#include"Tuple_Parameter.h"
#include"Tuple_Type_Change_Action.h"
#include"Tuple_Type_Change_Action_Helper.h"
#include"Tuple_Reverse.h"
#include"Tuple_t_To_v.h"
#include"Tuple_v_To_t.h"
#include"Tuple_Insert.h"
#include"Tuple_Element.h"
#include"Tuple_Merge.h"
#include"Tuple_Change.h"
#include"Tuple_Swap.h"
#include"Tuple_Range.h"
#include"Tuple_Extract.h"
#include"Tuple_Move_Template.h"
#include"Tuple_Elements_Action.h"

#include"Tuple_Remove_Pointer.h"
#include"Tuple_Create_Pointer.h"


#include"Tuple_Template_Calculate.h"
#include"Tuple_index_sequence.h"
#include"Tuple_Size.h"
#include"Tuple_Get.h"
#include"Tuple_Apply.h"
#include"Tuple_Repeat_Multiple.h"
#include"Tuple_Expand.h"
#include"Tuple_Zip.h"

#include"Tuple_Calculation.h"

namespace quiet
{
	template<class ..._Types>
	struct N_Tuple::S_Parameter<std::tuple<_Types...>> :
		N_Tuple::S_Parameter<tuple_t<_Types...>>
	{};

	template<class ..._Types>
	struct Tuple :
		std::tuple<_Types...>
	{

		using tuple = tuple_t<_Types...>;

		//仕様
		//要求する引数が引数の型と一致した場合
		template<class T_Tuple = tuple, class ...T_Args>
			requires requires
		{
			requires same_as<T_Tuple, tuple_t<T_Args...>>;
		}
		constexpr Tuple(T_Args... args):
			std::tuple<T_Args...>(args...)
		{}

		//仕様
		// [N_Tuple::Apply]を用いて適切に変換の結果、成功した場合
		template<class T_Tuple =tuple, class ...T_Args>
			requires requires
		{
			requires N_Tuple::N_Apply::Chack<T_Tuple, T_Args...>();
			requires same_as_not<T_Tuple, tuple_t<T_Args...>>;
		}
		constexpr Tuple(T_Args... args) :
			std::tuple<_Types...>({N_Tuple::Apply<std::tuple<_Types...>>(args...)})
		{}

		

	};

	template<class ..._Types>
	Tuple(_Types...) -> Tuple<_Types...>;

}