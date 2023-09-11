#pragma once

#include"Concept.h"
#include"Function_Data.h"
#include"Function_Helper.h"

template<class TP_Fns>
class Function
{
public:


	template<class ...MT_Fn_Parts>
	constexpr Function(MT_Fn_Parts... fn_Parts) {}












};

template<class ...T_Fn_Parts>
Function(T_Fn_Parts... fn_Parts) -> Function<typename
	N_Function::IS_Function_Helper<T_Fn_Parts...>::Pointer_Judge>;