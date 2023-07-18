#pragma once
#include"FunctionMultiple.h"
#include"Function.h"
#include"Function_Bind_Fns.h"

template<class T_FlontFn, class ...T_Fns>
	requires not_same_as<T_FlontFn, std::nullopt_t>
class FunctionMultiple
{
protected:

	constexpr FunctionMultiple() {}

public:

	//std::tuple<T_FlontFn, T_Fns...> fns;

	//ƒƒ‚
	//7/17
	//fns‚Ì•ÏŠ·‚ğÀ‘•‚·‚é
	template<class ...MT_Fns>
	constexpr FunctionMultiple(MT_Fns... setFns){}
		//:fns()
	

};

template<class ...MT_Fns>
FunctionMultiple(MT_Fns... fns) -> FunctionMultiple<typename N_Function::IS_BindFns<MT_Fns...>::FnsType>;
