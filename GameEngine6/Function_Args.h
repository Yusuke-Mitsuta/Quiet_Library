#pragma once
#include"Function_Helper.h"
#include"Using_Type.h"

#include"tuple_convertible_to.h"
#include"Tuple_Unzip.h"
#include"MethodData.h"
#include"Function_Operator.h"



namespace N_Function
{
	template<class ...T_Args>
	class Function_Args
	{
	protected:


		template<class ...MT_Args>
		constexpr Function_Args(MT_Args ...setArgs){}

	};

	template<class ...T_Args>
	Function_Args(T_Args... setArgs) -> Function_Args<T_Args...>;

}

template<auto t_Fn=std::nullopt, class T_Fn = std::nullopt_t>
class Functiona;

template<class T_Fn>
class Functiona<std::nullopt,T_Fn>
{
public:
	template<class ...T_Args>
	struct Args
	{
		constexpr Args(T_Args... args) {}
	};

	constexpr Functiona() {}
};

template<auto t_Fn>
class Functiona<t_Fn>
{
public:
	
	template<class ...T_Args>
	struct Args
	{
		constexpr Args(T_Args... args) {}
	};

	constexpr Functiona() {}
};