#pragma once

#include"Tuple.h"
#include"Function_Core_Operator.h"

namespace N_Function
{
	template<class ...T_Fn_Parts>
	struct I_Function_Single_Data;

	template<class ...T_Fn_Parts>
	struct Function_Core;

	template<class T_Fns,class T_Bind_Args_Type>
	struct I_Function_Operator
	{

		template<class T_Fns,class T_Tuple_Args_Numbers,class T_Args_Numbers=typename T_Tuple_Args_Numbers::type>
		struct S_Function_Select
		{



			template<class T_Fn_Core,class T_Request_Args_Numbers=int>
			struct S_Function_Operator;


			using fn_operator = S_Function_Operator<typename T_Fns::type>;

			using fn_data = I_Function_Single_Data<typename T_Fns::type>;

			using request_args = typename fn_data::request_args;

			using next_operator = typename S_Function_Select<typename T_Fns::next, typename T_Tuple_Args_Numbers::next>::fn_operator;
			

			struct S_Function_Operator_Core
			{
				T_Bind_Args_Type bind_list;

			protected:


				constexpr auto Action_Operator(auto ...args) {}

				constexpr S_Function_Operator_Core(auto... args) :
					bind_list(args...) {}
			};

			template<class T_Fn, class ...T_Bind_Args,size_t ...t_Request_Args_Numbers>
				requires (fn_data::fn_count == 1)
			struct S_Function_Operator<Function_Core<T_Fn, T_Bind_Args...>,tuple_v<t_Request_Args_Numbers...>> :
				next_operator
			{
				constexpr auto operator()(N_Tuple::U_Element_t<t_Request_Args_Numbers, request_args>... args) 
				{
				}

				constexpr S_Function_Operator(auto... args) :
					next_operator(args...) {}
			};


			//template<class T_Return_type,class T_Fns,class T_Flont_Reqest_Args, class ...T_Reqest_Args>
			//struct S_request_args_expand
			//{

			//};

			//
			//template<class T_Return_type,class T_Head_Fns,class T_Fn,class ...T_Tail_Fns,class ...T_Reqest_Args, class T_Reqest_Args_end, class T_Tail, class ...T_Fns_Reqest_Args>
			//struct S_request_args_expand<T_Return_type, tuple_tp<T_Head_Fns,T_Fn,tuple_t<T_Tail_Fns...>>,tuple_tp<tuple_t<T_Reqest_Args...>, T_Reqest_Args_end, T_Tail>, T_Fns_Reqest_Args...>
			//{
			//	constexpr auto operator()(T_Reqest_Args... args, T_Reqest_Args_end args_e)
			//	{
			//		return S_Function_Operator_Core::Action_Operator(args... , args_e);

			//	}
			//};



			//template<class T_Return_type, class T_Head_Fns,class T_Flont_Fn ,class ...T_Fns, class ...T_before_Bind_Args, class ...T_Tail_Fns, class ...T_Reqest_Args, class T_Reqest_Args_end, class T_Tail,class T_Tuple_Reqest_Args..., class ...T_Fns_Reqest_Args>
			//struct S_request_args_expand<T_Return_type, 
			//	tuple_tp<T_Head_Fns, Function_Core<tuple_t<T_Flont_Fn,T_Fns...>, T_before_Bind_Args...>, tuple_t<T_Tail_Fns...>>,
			//	tuple_t<T_Tuple_Reqest_Args...>, T_Fns_Reqest_Args...> 
			//	:
			//	S_request_args_expand<T_Return_type,
			//	tuple_tp<T_Head_Fns, T_Flont_Fn, tuple_t<T_Fns...,T_Tail_Fns...>>,
			//	T_Tuple_Reqest_Args..., T_Fns_Reqest_Args...>>
			//{

			//};



			template<class T_Fn, class ...T_Bind_Args, size_t ...t_Request_Args_Numbers>
				requires (fn_data::fn_count != 1)
			struct S_Function_Operator<Function_Core<T_Fn, T_Bind_Args...>, tuple_v<t_Request_Args_Numbers...>> :
				next_operator
			{


				constexpr S_Function_Operator(auto... args) :
					next_operator(args...) {}
			};



			//template<class ...T_Fns,class ...T_Bind_Args,  size_t ...t_Request_Args_Numbers>
			//struct S_Function_Operator<Function_Core<tuple_t<T_Fns...>,T_Bind_Args...>, tuple_v<t_Request_Args_Numbers...>>:
			//	S_request_args_expand<next_operator,tuple_t<T_Fns...>,request_args>
			//{
			//	constexpr S_Function_Operator(auto... args) :
			//		next_operator(args...) {};

			//};









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