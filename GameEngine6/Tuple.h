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

#include"Tuple_v_Calculate.h"
#include"Tuple_index_sequence.h"
#include"Tuple_Size.h"
#include"Tuple_Get.h"
#include"Tuple_Apply.h"
#include"Tuple_Repeat_Multiple.h"
#include"Tuple_Expand.h"
#include"Tuple_Zip.h"

#include"Tuple_Calculation.h"



template<class ..._Types>
struct Tuple :
	public std::tuple<_Types...>
{
private:

	using tuple = std::tuple<_Types...>;

public:
	template<class ..._Types>
	constexpr Tuple(_Types... types) :
		std::tuple<_Types...>(types...) {}

};

template<class ..._Types>
Tuple(_Types... types) -> Tuple<_Types...>;