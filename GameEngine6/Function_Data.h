#pragma once

#include"Function_Core.h"
#include"Parameter.h"

namespace N_Function
{

	template<not_same_as<std::nullopt_t> T_Flont_Method_Parts, class ...T_Method_Parts>
	struct S_Method;

	template<not_same_as<std::nullopt_t> T_Flont_Function_Parts, class ...T_Function_Parts>
	struct S_Function;


	template<class ...MT_Fn_Parts>
	struct IS_Function_Single_Helper;

	template<class ...T_Fn_Parts>
		requires not_same_as<typename IS_Function_Single_Helper<T_Fn_Parts...>::Judge,std::nullopt_t>
	struct S_Function_Data
	{

		using Function = std::nullopt_t;
		using Method = std::nullopt_t;
		using RequestArgs = std::nullopt_t;
		using BindArgs = std::nullopt_t;
		using BoundArgs = std::nullopt_t;
		using CName = std::nullopt_t;
		using RType = std::nullopt_t;

		static constexpr int Lelve = -1;

	};

	template<class T_RType, class ...T_Args, class ...T_Bind_Args>
	struct S_Function_Data<T_RType(*)(T_Args...), T_Bind_Args...>
	{

		using Method = T_RType(*)(T_Args...);
		using Function = Function_Core<Method>;
		using RequestArgs = S_Parameter<T_Args...>;
		using BoundArgs = S_Parameter<T_Bind_Args...>;
		using BindArgs = BoundArgs;
		using CName = std::nullopt_t;
		using RType = T_RType;

		static constexpr int Lelve = 0;

	};

	template<class T_CName, class T_RType, class ...T_Args, class ...T_Bind_Args>
	struct S_Function_Data<T_RType(T_CName::*)(T_Args...), T_Bind_Args...> :
		public S_Function_Data<T_RType(*)(T_Args...), T_Bind_Args...>
	{
		using Function = std::nullopt_t;
		using CName = T_CName;

	};


	template<class T_Dedicated_Point,class T_CName, class T_RType, class ...T_Args, class ...T_Bind_Args>
	struct S_Function_Data<T_Dedicated_Point*,T_RType(T_CName::*)(T_Args...), T_Bind_Args...> :
		public S_Function_Data<T_RType(T_CName::*)(T_Args...), T_Bind_Args...>
	{
		using Function = Function_Core<T_RType(T_CName::*)(T_Args...)>;
	};



	template<class ...TP_Method_Inner,class ...T_Bind_Args>
	struct S_Function_Data<S_Method<TP_Method_Inner...>, T_Bind_Args...> :
		public S_Function_Data<TP_Method_Inner...>
	{
		using Parent = S_Function_Data<TP_Method_Inner...>;

		using BindArgs = S_Parameter<T_Bind_Args...>;
		using BoundArgs = U_Merge_Element_t<T_Bind_Args..., typename Parent::BoundArgs>;

		static constexpr int Lelve = S_Function_Data<TP_Method_Inner>::Lelve + 1;
	};

	template<class T_Dedicated_Point, class ...TP_Method_Inner, class ...T_Bind_Args>
	struct S_Function_Data<T_Dedicated_Point*, S_Method<TP_Method_Inner...>, T_Bind_Args...> :
		public S_Function_Data<S_Method<TP_Method_Inner...>, T_Bind_Args...>
	{
		using Function = Function_Core<S_Method<TP_Method_Inner...>>;
	};


	template<class ...TP_Function_Inner, class ...T_Bind_Args>
	struct S_Function_Data<S_Function<TP_Function_Inner...>, T_Bind_Args...> :
		public S_Function_Data<TP_Function_Inner...>
	{
		using Parent = S_Function_Data<TP_Function_Inner...>;

		using Function = S_Function<TP_Function_Inner...>;
		using BindArgs = S_Parameter<T_Bind_Args...>;
		using BoundArgs = U_Merge_Element_t<T_Bind_Args..., typename Parent::BoundArgs>;

		static constexpr int Lelve = S_Function_Data<TP_Function_Inner>::Lelve + 1;
	};

}
