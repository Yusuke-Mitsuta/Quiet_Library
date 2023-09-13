#pragma once

#include"Parameter.h"
#include"Parameter_convertible_to.h"

namespace N_Function
{
	template<class ...T_Fn_Parts>
	struct S_Function_Single_Data;

	template<class TP_Fns>
	struct IS_Function_Operator
	{

		template<class T_Fns>
		struct S_Function_Operator;


		template<class T_Flont_Fn, class ...T_Fns>
		struct S_Bind_Args_Expand;

		template<class T_Dedicated_P, class T_Method, class ...T_Bind_Args, class ...T_Fns>
			requires same_as<typename S_Function_Single_Data<T_Method, T_Bind_Args...>::BindArgs,
		typename S_Function_Single_Data<T_Dedicated_P*, T_Method, T_Bind_Args...>::BindArgs>
		struct S_Bind_Args_Expand<S_Parameter<S_Function_Single_Data<T_Dedicated_P*, T_Method, T_Bind_Args...>, T_Fns...>>
		{
			using Fn = S_Function_Single_Data<T_Dedicated_P*, T_Method, T_Bind_Args...>;

			Fn::BindArgs_Expand bindArgs;

			template<bool t_First_Fn_Judge = (sizeof...(T_Fns) + 1 == TP_Fns::Size)>
				requires (!t_First_Fn_Judge)
			constexpr S_Bind_Args_Expand(T_Dedicated_P* dedicated_P, T_Method fn,T_Bind_Args... bind_Args, auto... fns) :
				method(fn_Parns...) {}




		};




		template<class T_Dedicated_P,class T_Method,class ...T_Bind_Args,class ...T_Fns>
			requires same_as<typename S_Function_Single_Data<T_Method, T_Bind_Args...>::BindArgs,
		typename S_Function_Single_Data<T_Dedicated_P*,T_Method, T_Bind_Args...>::BindArgs>
		struct S_Function_Operator<S_Parameter<S_Function_Single_Data<T_Dedicated_P*,T_Method,T_Bind_Args...>,T_Fns...>>
		{

			template<bool t_First_Fn_Judge=(sizeof...(T_Fns)+1==TP_Fns::Size)>
				requires (t_First_Fn_Judge)
			constexpr S_Function_Operator(T_Dedicated_P* dedicated_P,T_Method fn,T_Bind_Args... bind_Args,auto... fns) :
				method(fn_Parns...){}

			template<bool t_First_Fn_Judge = (sizeof...(T_Fns) + 1 == TP_Fns::Size)>
				requires (!t_First_Fn_Judge)
			constexpr S_Function_Operator(T_Dedicated_P* dedicated_P, T_Method fn, T_Bind_Args... bind_Args, auto... fns) :
				method(fn_Parns...) {}

			template<class T_Default_P>
			constexpr S_Function_Operator(T_Default_P* default_P,T_Dedicated_P* dedicated_P, T_Method fn, T_Bind_Args... bind_Args, auto... fns) :
				method(fn_Parns...) {}

		};

		template<class T_Method, class ...T_Bind_Args, class ...T_Fns>
		struct S_Function_Operator<S_Parameter<S_Function_Single_Data<T_Method, T_Bind_Args...>, T_Fns...>>
		{

			constexpr S_Function_Operator(T_Method fn, T_Bind_Args ... bind_Args, auto... fns) :
				method(fn_Parns...) {}

			template<class T_Default_P>
			constexpr S_Function_Operator(T_Default_P* default_P, T_Method fn, T_Bind_Args ... bind_Args, auto... fns) :
				method(fn_Parns...) {}
		};


	};


}