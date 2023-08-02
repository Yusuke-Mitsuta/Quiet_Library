#pragma once
#include"Function_Single_Helper.h"
#include"Using_Type.h"

#include"tuple_convertible_to.h"
#include"Tuple_Unzip.h"
#include"MethodData.h"
#include"Function_Single_Operator.h"



namespace N_Function
{
	template<class ...TP_Args>
	class Function_Args
	{
	protected:


		template<class ...MT_Args>
		constexpr Function_Args(MT_Args ...setArgs){}

	};

	template<class ...TP_Args>
	Function_Args(TP_Args... setArgs) -> Function_Args<TP_Args...>;

}

template<auto t_Fn=std::nullopt, class T_Method = std::nullopt_t>
class Functiona;

template<class T_Method>
class Functiona<std::nullopt,T_Method>
{
public:
	template<class ...TP_Args>
	struct Args
	{
		constexpr Args(TP_Args... args) {}
	};

	constexpr Functiona() {}
};

template<auto t_Fn>
class Functiona<t_Fn>
{
public:
	
	template<class ...TP_Args>
	struct Args
	{
		constexpr Args(TP_Args... args) {}
	};

	constexpr Functiona() {}
};