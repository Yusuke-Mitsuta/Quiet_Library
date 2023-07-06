#pragma once
#include"Function_Address.h"
#include"Using_Type.h"

#include"tuple_convertible_to.h"
#include"Tuple_Unzip.h"

template<class Args, int t_Fns_Number = 0, class ...t_Fns>
struct S_Function_Select
{
	using Type0 = bool;
};

template<int t_Fns_Number,class t_C_Name, class t_R_Type>
struct S_Function_Data
{
	static constexpr int Fns_Number = t_Fns_Number;
	using C_Name = t_C_Name;
	using R_Type = t_R_Type;
};

template<class ...Args,int t_Fns_Number,class t_Fn, class ...t_Fns>
struct S_Function_Select<std::tuple<Args...>, t_Fns_Number, t_Fn, t_Fns...>
{
	//using Type = S_Function_Select<std::tuple<Args...>, t_Fns_Number + 1, t_Fns...>::Type;
	using Type1 = S_Function_Select<std::tuple<Args...>, t_Fns_Number + 1, t_Fns...>;
};

//指定引数あり、Function_Address
template< class ...Args, int t_Fns_Number, class t_C_Name, class t_R_Type, class ...T_Args, class ...t_Set_Args, class ...t_Fns>
	requires tuple_convertible_to<std::tuple<T_Args...>, std::tuple<Args..., t_Set_Args...>>
struct S_Function_Select< std::tuple<Args...>, t_Fns_Number, Function_Address<t_R_Type(t_C_Name::*)(T_Args...), t_Set_Args...>,t_Fns...>
{
	using Type2 = S_Function_Data<t_Fns_Number,t_C_Name,t_R_Type>;
};

//指定引数なし、Function_Address
template< class ...Args, int t_Fns_Number, class t_C_Name, class t_R_Type, class ...T_Args,class ...t_Fns>
	requires tuple_convertible_to<std::tuple<T_Args...>, std::tuple<Args...>>
struct S_Function_Select<std::tuple<Args...>, t_Fns_Number, Function_Address<t_R_Type(t_C_Name::*)(T_Args...)>, t_Fns...>
{
	using Type3 = S_Function_Data<t_Fns_Number, t_C_Name, t_R_Type>;
	
};

//引数なし、Function_Address
template< class ...Args, int t_Fns_Number, class t_C_Name, class t_R_Type, class ...t_Fns>
	requires (sizeof...(Args) == 0)
struct S_Function_Select< std::tuple<Args...>, t_Fns_Number, Function_Address<t_R_Type(t_C_Name::*)(void)>, t_Fns...>
{
	using Type4 = S_Function_Data<t_Fns_Number, t_C_Name, t_R_Type>;
};

//引数なし、アドレス直渡し
template< class ...Args, int t_Fns_Number, class t_C_Name, class t_R_Type, class ...t_Fns>
	requires (sizeof...(Args) == 0)
struct S_Function_Select<std::tuple<Args...>, t_Fns_Number, t_R_Type(t_C_Name::*)(void), t_Fns...>
{
	using Type5 = S_Function_Data<t_Fns_Number, t_C_Name, t_R_Type>;
};


//指定引数なし、アドレス直渡し
template<class ...Args, int t_Fns_Number, class t_C_Name, class t_R_Type, class ...T_Args, class ...t_Fns>
struct S_Function_Select<std::tuple<Args...>, t_Fns_Number, t_R_Type(t_C_Name::*)(T_Args...), t_Fns...>
{

	//using Type = S_Function_Select<std::tuple<Args...>, t_Fns_Number, Function_Address<t_R_Type(t_C_Name::*)(T_Args...), Set_Args>, t_Fns...>::Type;
	using Type6 = S_Function_Select<std::tuple<Args...>, t_Fns_Number, Function_Address<t_R_Type(t_C_Name::*)(T_Args...), Set_Args>, t_Fns...>;
};

template<class Args,class ...T_Fns>
struct I_S_Function_Select
{
	using Type=S_Function_Select<I_S_TupleUnzip<Args>,>
};


template<class T, class ...t_Fns>
class Function
{
	T* p;

	std::tuple<t_Fns...> fns;

public:

	template<class T,class ...t_Fns, std::make_integer_sequence<int, std::tuple_size<I_S_TupleUnzip<t_Fns...>::Type>::value> N=0>
	constexpr Function(T* set_p, t_Fns ...set_Fns):
		p(set_p), fns(set_Fns...) {}


	template<class ...Args>
		//requires tuple_convertible_to<std::tuple<T_Args...>, std::tuple<t_Set_Args..., Args...>>
	constexpr void operator()(Args ...args)
	{
		std::apply();
		//Function_Execution<sizeof...(t_Set_Args) - 1>(args...);
	}

	//// C++17
	//template<class F, class Tuple, size_t... I>
	//constexpr decltype(auto) apply - impl(F && f, Tuple && t, std::index_sequence<I...>) {
	//	return std::invoke(std::forward<F>(f), std::get<I>(std::forward<Tuple>(t))...);
	//}


};
//void f(Args&&... args) {
	//hoge(std::forward<Args>(args)...);
	// std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<Tuple>>>
//std::make_integer_sequence<int, 3>
template<class T,class ...t_Fns>
Function(T* set_p,t_Fns ...set_Fns) -> Function<T, typename std::tuple_element<0,typename I_S_TupleUnzip<t_Fns...>::Type>::type>;