#pragma once

#include"Tuple.h"
#include"Function_Core_Operator.h"

namespace N_Function
{
	template<class ...T_Fn_Parts>
	struct I_Function_Single_Data;

	template<class T_Fn, class ...TP_Bind_Args>
	struct Function_Core;

	template<class T_Fns>
	struct I_Function_Operator
	{

		template<class T_Fns>
		struct S_Function_Select
		{

			
			


			template<class T_Fn_Core>
			struct S_Function_Operator;

			using fn_operator = S_Function_Operator<T_Fns>;
			using next_operator = typename S_Function_Select<typename T_Fns::next>::fn_operator;
			

			template<class T_Fn, class ...T_Bind_Args>
				requires (I_Function_Single_Data<Function_Core<T_Fn>>::fn_count == 1)
			struct S_Function_Operator<Function_Core<T_Fn, T_Bind_Args...>>:
				next_operator
			{

				template<class ...MT_Fn_Parts>
				S_Function_Operator(T_Fn set_fn, T_Bind_Args... set_bind_args, MT_Fn_Parts ...fn_parts) {}


				template<class T_Commond_p, class ...MT_Fn_Parts>
				S_Function_Operator(T_Commond_p* commond_p,T_Fn set_fn,T_Bind_Args... set_bind_args, MT_Fn_Parts ...fn_parts) :
					next_operator(commond_p, fn_parts...)
				{}

				template<class T_Commond_p,class T_Dedicated_p, class ...MT_Fn_Parts>
				S_Function_Operator(T_Commond_p* commond_p,T_Dedicated_p* dedicated_p,T_Fn fn, T_Bind_Args... bind_args, MT_Fn_Parts ...fn_parts):
					next_operator(commond_p, fn_parts...)
				{}


			};


			template<class ...T_Fns,class ...T_Bind_Args>
			struct S_Function_Operator<Function_Core<tuple_t<T_Fns...>, T_Bind_Args...>> :
				next_operator
			{

				template<class T_Commond_p, class T_Dedicated_p, class ...MT_Fn_Parts>
				S_Function_Operator(Function<tuple_t<T_Fns...>> fns, T_Bind_Args... bind_args) :
				next_operator()
				{}

			};


			







		};


		//template<class T_Flont_Fn,class ...T_Fns>
		//struct S_Function_Operator<tuple_t<Function_Core<T_Flont_Fn>, T_Fns...>> :
		//	S_Function_Operator<tuple_t<T_Fns...>>
		//{
		//	T_Flont_Fn fn;
		//	
		//	constexpr S_Function_Operator(T_Flont_Fn set_fn) :
		//	fn(set_fn) {}

		//	constexpr auto operator()()
		//	{

		//	}

		//};

		//template<class T_Flont_Fn, class ...T_Bind_Args,class ...T_Fns>
		//struct S_Function_Operator<tuple_t<Function_Core<T_Flont_Fn,T_Bind_Args...>,T_Fns...>> :
		//	S_Function_Operator<tuple_t<T_Fns...>>
		//{

		//	T_Flont_Fn fn;

		//	tuple_t<T_Bind_Args...> bind_args;

		//	constexpr S_Function_Operator(T_Flont_Fn set_fn, T_Bind_Args... set_bind_args) :
		//		fn(set_fn),bind_args(set_bind_args...) {}



		//};

		using type = int;


	};





	/*
	template<class ...T_Fn_Parts>
	struct S_Function_Single_Data;

	template<class TP_Fns>
	struct IS_Function_Operator
	{

		template<class T_Fns>
		struct S_Function_Operator;


		template<class T_Flont_Fn, class ...T_Fns>
		struct S_Bind_Args_Expand;

		template<class T_Dedicated_P, class T_Fns, class ...T_Bind_Args, class ...T_Fns>
			requires same_as<typename S_Function_Single_Data<T_Fns, T_Bind_Args...>::BindArgs,
		typename S_Function_Single_Data<T_Dedicated_P*, T_Fns, T_Bind_Args...>::BindArgs>
		struct S_Bind_Args_Expand<S_Parameter<S_Function_Single_Data<T_Dedicated_P*, T_Fns, T_Bind_Args...>, T_Fns...>>
		{
			using Fn = S_Function_Single_Data<T_Dedicated_P*, T_Fns, T_Bind_Args...>;

			Fn::BindArgs_Expand bindArgs;

			template<bool t_First_Fn_Judge = (sizeof...(T_Fns) + 1 == TP_Fns::Size)>
				requires (!t_First_Fn_Judge)
			constexpr S_Bind_Args_Expand(T_Dedicated_P* dedicated_P, T_Fns fn,T_Bind_Args... bind_Args, auto... fns) :
				method(fn_Parns...) {}




		};




		template<class T_Dedicated_P,class T_Fns,class ...T_Bind_Args,class ...T_Fns>
			requires same_as<typename S_Function_Single_Data<T_Fns, T_Bind_Args...>::BindArgs,
		typename S_Function_Single_Data<T_Dedicated_P*,T_Fns, T_Bind_Args...>::BindArgs>
		struct S_Function_Operator<S_Parameter<S_Function_Single_Data<T_Dedicated_P*,T_Fns,T_Bind_Args...>,T_Fns...>>
		{

			template<bool t_First_Fn_Judge=(sizeof...(T_Fns)+1==TP_Fns::Size)>
				requires (t_First_Fn_Judge)
			constexpr S_Function_Operator(T_Dedicated_P* dedicated_P,T_Fns fn,T_Bind_Args... bind_Args,auto... fns) :
				method(fn_Parns...){}

			template<bool t_First_Fn_Judge = (sizeof...(T_Fns) + 1 == TP_Fns::Size)>
				requires (!t_First_Fn_Judge)
			constexpr S_Function_Operator(T_Dedicated_P* dedicated_P, T_Fns fn, T_Bind_Args... bind_Args, auto... fns) :
				method(fn_Parns...) {}

			template<class T_Default_P>
			constexpr S_Function_Operator(T_Default_P* default_P,T_Dedicated_P* dedicated_P, T_Fns fn, T_Bind_Args... bind_Args, auto... fns) :
				method(fn_Parns...) {}

		};

		template<class T_Fns, class ...T_Bind_Args, class ...T_Fns>
		struct S_Function_Operator<S_Parameter<S_Function_Single_Data<T_Fns, T_Bind_Args...>, T_Fns...>>
		{

			constexpr S_Function_Operator(T_Fns fn, T_Bind_Args ... bind_Args, auto... fns) :
				method(fn_Parns...) {}

			template<class T_Default_P>
			constexpr S_Function_Operator(T_Default_P* default_P, T_Fns fn, T_Bind_Args ... bind_Args, auto... fns) :
				method(fn_Parns...) {}
		};


	};*/


}