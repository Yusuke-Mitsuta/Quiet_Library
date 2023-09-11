#pragma once

#include"Function_Core.h"
#include"Parameter.h"
#include"Concept.h"

#include"Function_Single_Data_Request_Args.h"

namespace N_Function
{

	template<class ...T_Fn_Parts>
	struct S_Function_Single_Data
	{
		using Function = std::nullopt_t;
		using Method = std::nullopt_t;
		using RequestArgs = std::nullopt_t;
		using BindArgs = std::nullopt_t;
		using BindArgs_Expand= std::nullopt_t;
		using BoundArgs = std::nullopt_t;
		using CName = std::nullopt_t;
		using RType = std::nullopt_t;

		static constexpr int Lelve = -1;
	};

	template<class T_RType, class ...T_Args, class ...T_Bind_Args>
		requires not_is_nullopt
	<typename IS_Request_Args<S_Parameter<T_Args...>,
	S_Parameter<T_Bind_Args...>>::Request_Args>
	struct S_Function_Single_Data<T_RType(*)(T_Args...), T_Bind_Args...>
	{
	private:
		using Args_Set = IS_Request_Args<S_Parameter<T_Args...>,
			S_Parameter<T_Bind_Args...>>;
	public:
		using Method = Method_Core<T_RType(*)(T_Args...)>;
		using Function = Function_Core<Method>;


		using RequestArgs = Args_Set::Request_Args;
		using BindArgs = S_Parameter<T_Bind_Args...>;

		using BindArgs_Expand = Args_Set::Bind_Args;

		using BoundArgs = BindArgs;

		using CName = std::nullopt_t;
		using RType = T_RType;

		static constexpr int Lelve = 0;

	};

	template<class T_CName, class T_RType, class ...T_Args, class ...T_Bind_Args>
		requires not_is_nullopt<typename IS_Request_Args<S_Parameter<T_Args...>,
	S_Parameter<T_Bind_Args...>>::Request_Args>
	struct S_Function_Single_Data<T_RType(T_CName::*)(T_Args...), T_Bind_Args...> :
		public S_Function_Single_Data<T_RType(*)(T_Args...), T_Bind_Args...>
	{
		using Method = Method_Core<T_RType(T_CName::*)(T_Args...)>;
		using Function = std::nullopt_t;
		using CName = T_CName;

	};


	template<class T_Dedicated_Point, class T_CName, class T_RType, class ...T_Args, class ...T_Bind_Args>
		requires not_is_nullopt<typename IS_Request_Args<S_Parameter<T_Args...>,
		S_Parameter<T_Bind_Args...>>::Request_Args>
			&& convertible_to<T_Dedicated_Point, T_CName>
	struct S_Function_Single_Data<T_Dedicated_Point*, T_RType(T_CName::*)(T_Args...), T_Bind_Args...> :
		public S_Function_Single_Data<T_RType(T_CName::*)(T_Args...), T_Bind_Args...>
	{
		using Parent = S_Function_Single_Data<T_RType(T_CName::*)(T_Args...), T_Bind_Args...>;

		using Function = Function_Core<typename Parent::Method>;
	};


	template<class ...TP_Method_Inner, class ...T_Bind_Args>
		requires not_is_nullopt<typename IS_Request_Args<typename S_Function_Single_Data<TP_Method_Inner...>::RequestArgs,
			S_Parameter<T_Bind_Args...>>::Request_Args>
	struct S_Function_Single_Data<Method_Core<TP_Method_Inner...>, T_Bind_Args...> :
		public S_Function_Single_Data<TP_Method_Inner...>
	{
	private:
		using Parent = S_Function_Single_Data<TP_Method_Inner...>;
		using Args_Set = IS_Request_Args<typename Parent::RequestArgs,
			S_Parameter<T_Bind_Args...>>;
	public:

		using Method = Method_Core<Method_Core<TP_Method_Inner...>>;
		using BindArgs = S_Parameter<T_Bind_Args...>;
		using BindArgs_Expand = Args_Set::Bind_Args;
		using RequestArgs = Args_Set::Request_Args;
		using BoundArgs = U_Merge_Element_t<T_Bind_Args..., typename Parent::BoundArgs>;

		static constexpr int Lelve = Parent::Lelve + 1;
	};

	template<class T_Dedicated_Point, class ...TP_Method_Inner, class ...T_Bind_Args>
		requires not_is_nullopt<typename S_Function_Single_Data<Method_Core<TP_Method_Inner...>, T_Bind_Args...>::RequestArgs> &&
	convertible_to<T_Dedicated_Point,typename  S_Function_Single_Data<Method_Core<TP_Method_Inner...>, T_Bind_Args...>::CName>
	struct S_Function_Single_Data<T_Dedicated_Point*, Method_Core<TP_Method_Inner...>, T_Bind_Args...> :
		public S_Function_Single_Data<Method_Core<TP_Method_Inner...>, T_Bind_Args...>
	{
		using Parent = S_Function_Single_Data<Method_Core<TP_Method_Inner...>, T_Bind_Args...>;
		using Function = Function_Core<typename Parent::Method>;
	};

	template<class ...TP_Function_Inner, class ...T_Bind_Args>
		requires not_is_nullopt<typename IS_Request_Args<
			typename S_Function_Single_Data<Function_Core<TP_Function_Inner...>>::RequestArgs,
			S_Parameter<T_Bind_Args...>>::Request_Args>
	struct S_Function_Single_Data<Function_Core<TP_Function_Inner...>, T_Bind_Args...> :
		public S_Function_Single_Data<TP_Function_Inner...>
	{
	private:
		using Parent = S_Function_Single_Data<TP_Function_Inner...>;
		using Args_Set = IS_Request_Args<typename Parent::RequestArgs,
			S_Parameter<T_Bind_Args...>>;
	public:

		using Method = Method_Core<Method_Core<TP_Function_Inner...>>;
		using Function = Function_Core<Function_Core<TP_Function_Inner...>>;
		using BindArgs = S_Parameter<T_Bind_Args...>;
		using BindArgs_Expand = Args_Set::Bind_Args;
		using RequestArgs = Args_Set::Request_Args;
		using BoundArgs = U_Merge_Element_t<T_Bind_Args...,typename Parent::BoundArgs>;

		static constexpr int Lelve = Parent::Lelve + 1;
	};


}
