#pragma once
#include"Function_BindFn.h"
#include"Using_Type.h"

#include"tuple_convertible_to.h"
#include"Tuple_Unzip.h"
#include"MethodData.h"
#include"Function_Operator.h"
#include"Function_Static.h"

template<not_same_as<std::nullopt_t> T_Fn,class ...T_Args>
class Function :
	public N_Function::IS_FunctionOperator<T_Fn, T_Args...>::Type
{
protected:

	using MethodData = N_Function::S_MethodData<T_Fn, T_Args...>;

	using FunctionOperator = N_Function::IS_FunctionOperator<T_Fn, T_Args...>::Type;

public:

	using FunctionOperator::operator();

	using BoundArgs = MethodData::BoundArgs;
	using BindArgs = MethodData::BindArgs;
	using CName = MethodData::CName;
	using RType = MethodData::RType;
	using Args = MethodData::Args;
	using Fn = MethodData::Fn;
	
	template<class MT_Fn,class ...MT_Args>
	constexpr Function(MT_Fn setFn, MT_Args ...setArgs) :
		N_Function::IS_FunctionOperator<MT_Fn,MT_Args...>::Type(setFn,setArgs...){}

};

template<class MT_Fn, class ...T_Args>
Function(MT_Fn setFn, T_Args... setArgs) -> Function<typename N_Function::IS_FunctionHelper<MT_Fn,T_Args...>::Judge,T_Args...>;

