#pragma once
#include"FunctionMultiple.h"
#include"Function.h"
#include"Function_BindFn.h"


template<class ...T_Fns>
class FunctionMultiple
{
protected:
	FunctionMultiple() {}
public:

};

template<class ...T_Fns>
class FunctionMultiple<std::tuple<T_Fns...>>
{
public:

	template<class ...MT_Fn>
	FunctionMultiple(MT_Fn... fn)
	{

	}

};

//template<class ...MT_Fn>
//FunctionMultiple(MT_Fn... fn)->FunctionMultiple<N_Function::IS_BindFns>
