#pragma once

#include<tuple>

#include"Tuple_Declare.h"
#include"Tuple_Class_Declare.h"
#include"Tuple_Type.h"
#include"Tuple_Head.h"
#include"Tuple_Tail.h"
#include"Tuple_Next.h"
#include"Tuple_Prev.h"
#include"Tuple_Select.h"
#include"Tuple_Remove.h"
#include"Tuple_Value.h"
#include"Tuple_Parameter.h"
#include"Tuple_Action.h"
#include"Tuple_Reverse.h"
#include"Tuple_t_To_v.h"
#include"Tuple_v_To_t.h"
#include"Tuple_Insert.h"
#include"Tuple_Element.h"
#include"Tuple_Merge.h"
#include"Tuple_Change.h"
#include"Tuple_Swap.h"

#include"Tuple_Remove_Pointer.h"
#include"Tuple_Create_Pointer.h"


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