#pragma once

#include"Constexpr_String.h"
#include"Core_Base.h"
#include"Core_Parentage.h"

#include"Using_Type.h"
#include"tuple_convertible_to.h"
#include<functional>
#include <tuple>
#include<list>


//#define RECEIVE(SelectMessage) \
//template<N_Constexpr::String t_Address = "", N_Constexpr::String t_Message = "">\
//requires requires \
//{\
//	requires (t_Message == N_Constexpr::String(#SelectMessage));\
//	requires derived_from<Core<t_Address>,Core>;\
//}\
//	void Receive() \
//

class Message_Origin
{

protected:
	Message_Origin() {}
public:

	virtual void Execute() = 0;


};




template<N_Constexpr::String t_Message = "", N_Constexpr::String t_Address = "">
class Message :
	public Message_Origin
{
protected:

	//Core<"Core">* target_Core;

public:

	//template<class C_Fn, class ...t_Set_Args>
	//	requires Fg<(sizeof...(t_Set_Args) == 0)>
	//class Receive
	//{
	//private:
	//public:
	//	C_Fn fn;

	//	Receive(C_Fn setfn):
	//		fn(setfn){}
	//	Receive(C_Fn setfn, void* p){}
	//	Receive(C_Fn setfn, void* p, t_Set_Args ...args){}
	//	Receive(C_Fn setfn, void* p, std::tuple<t_Set_Args...> args){}
	//};



	//template<class C_Name, class R_Type, class ...T_Args>
	//class Receive<R_Type(C_Name::*)(T_Args...)>
	//{
	//protected:

	//	R_Type(C_Name::* fn)(T_Args...);

	//	C_Name* p;

	//public:

	//	constexpr Receive(R_Type(C_Name::* set_Fn)(T_Args...), C_Name* set_P) :
	//		fn(set_Fn), p(set_P){}

	//	template<class ...Args>
	//		requires tuple_convertible_to<std::tuple<T_Args...>, std::tuple<Args...>>
	//	constexpr R_Type operator()(Args ...args)
	//	{
	//		std::function<R_Type()> method = std::bind(fn, p,args...);
	//		return method();
	//	}

	//};


	//template<class C_Name, class R_Type, class ...T_Args,class ...t_Set_Args>
	//class Receive<R_Type(C_Name::*)(T_Args...),t_Set_Args...>
	//{
	//private:

	//	R_Type(C_Name::* fn)(T_Args...);

	//	C_Name* p;

	//	std::tuple<t_Set_Args...> default_Args_Tuple;

	//public:

	//	template<int Select_default_Args_Tuple_Number,class ...Args>
	//	constexpr R_Type Function_Execution(Args... args)
	//	{
	//		return Function_Execution<Select_default_Args_Tuple_Number-1,Args...>
	//			(std::get<Select_default_Args_Tuple_Number>(default_Args_Tuple),args...);
	//	}

	//	template<int Select_default_Args_Tuple_Number,class ...Args>
	//		requires Fg<(Select_default_Args_Tuple_Number == 0)>
	//	constexpr R_Type Function_Execution(Args... args)
	//	{
	//		std::function<R_Type()> method = std::bind(fn, p,
	//			std::get<Select_default_Args_Tuple_Number>(default_Args_Tuple), args...);

	//		return method();
	//	}

	//	constexpr Receive(R_Type(C_Name::* set_Fn)(T_Args...),C_Name* set_P,t_Set_Args ...args) :
	//		fn(set_Fn),p(set_P),default_Args_Tuple(args...){}

	//	template<class ...Args>
	//		requires tuple_convertible_to<std::tuple<T_Args...>,std::tuple<t_Set_Args...,Args...>>
	//	constexpr R_Type operator()(Args ...args)
	//	{
	//		Function_Execution<sizeof...(Set_Args) - 1>(args...);
	//	}

	//};



	void Execute();

	//using Addarss = Core_Name<t_Address>;

	static constexpr N_Constexpr::String message = t_Message;

};




template<N_Constexpr::String t_Address , N_Constexpr::String t_Message>
void Message<t_Address,t_Message>::Execute()
{
	//target_Core->Get_Parentage()->Order<t_Address, t_Message>();
}