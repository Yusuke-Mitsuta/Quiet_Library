#pragma once

#include"Function_Core.h"
#include"Method_Core.h"
#include"Parameter.h"

namespace N_Function
{

	template<class T_Request_Args, class T_Bind_Args>
	struct IS_Request_Args;

	template<class ...MT_Fn_Parts>
	struct IS_Function_Single_Helper;

	template<class T_FlontFn, class ...TP_Fns>
	struct IS_Function_Multiple_Helper;

	template<int t_Number,class ...T_Fn_Parts>
	struct IS_Function_Data
	{

		template<class ...T_Fn_Parts>
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

			using Method = Method_Core<T_RType(*)(T_Args...)>;
			using Function = Function_Core<Method>;
			using BoundArgs = S_Parameter<T_Bind_Args...>;
			using BindArgs = BoundArgs;

			using RequestArgs = S_Parameter<T_Args...>;

			using CName = std::nullopt_t;
			using RType = T_RType;

			static constexpr int Lelve = 0;

		};

		template<class T_CName, class T_RType, class ...T_Args, class ...T_Bind_Args>
			requires not_is_nullopt<typename IS_Request_Args<S_Parameter<T_Args...>
		, S_Parameter<T_Bind_Args...>>::Type>
		struct S_Function_Data<T_RType(T_CName::*)(T_Args...),T_Bind_Args...> :
			public S_Function_Data<T_RType(*)(T_Args...), T_Bind_Args...>
		{
			using Method = Method_Core<T_RType(T_CName::*)(T_Args...)>;
			using Function = std::nullopt_t;
			using CName = T_CName;

		};


		template<class T_Dedicated_Point, class T_CName, class T_RType, class ...T_Args, class ...T_Bind_Args>
		struct S_Function_Data<T_Dedicated_Point*, T_RType(T_CName::*)(T_Args...), T_Bind_Args...> :
			public S_Function_Data<T_RType(T_CName::*)(T_Args...), T_Bind_Args...>
		{
			using Parent = S_Function_Data<T_RType(T_CName::*)(T_Args...),T_Bind_Args...>;
			using Function = Function_Core<typename Parent::Method>;
		};


		template<class ...TP_Method_Inner, class ...T_Bind_Args>
		struct S_Function_Data<Method_Core<TP_Method_Inner...>, T_Bind_Args...> :
			public S_Function_Data<TP_Method_Inner...>
		{
			using Parent = S_Function_Data<TP_Method_Inner...>;

			using Method = Method_Core<Method_Core<TP_Method_Inner...>>;
			using BindArgs = S_Parameter<T_Bind_Args...>;
			using BoundArgs = U_Merge_Element_t<T_Bind_Args...,typename Parent::BoundArgs>;

			static constexpr int Lelve = Parent::Lelve + 1;
		};

		template<class T_Dedicated_Point, class ...TP_Method_Inner, class ...T_Bind_Args>
		struct S_Function_Data<T_Dedicated_Point*, Method_Core<TP_Method_Inner...>, T_Bind_Args...> :
			public S_Function_Data<Method_Core<TP_Method_Inner...>, T_Bind_Args...>
		{
			using Parent = S_Function_Data<Method_Core<TP_Method_Inner...>, T_Bind_Args...>;
			using Function = Function_Core<typename Parent::Method>;
		};



		template<class ...TP_Function_Inner, class ...T_Bind_Args>
		struct S_Function_Data<Function_Core<TP_Function_Inner...>, T_Bind_Args...> :
			public S_Function_Data<TP_Function_Inner...>
		{
			using Parent = S_Function_Data<TP_Function_Inner...>;

			using Method = Method_Core<Method_Core<TP_Function_Inner...>>;
			using Function = Function_Core<Function_Core<TP_Function_Inner...>>;
			using BindArgs = S_Parameter<T_Bind_Args...>;
			using BoundArgs = U_Merge_Element_t<T_Bind_Args..., typename Parent::BoundArgs>;

			static constexpr int Lelve = Parent::Lelve + 1;
		};


		using Type = U_Swap_t1<S_Function_Data<T_Fn_Parts...>, S_Function_Data_Separate<T_Fn_Parts...>, t_Number>;

		using Function = typename Type::Function;
		using Method = typename Type::Method;
		using RequestArgs = typename Type::RequestArgs;
		using BindArgs = typename Type::BindArgs;
		using BoundArgs = typename Type::BoundArgs;
		using CName = typename Type::CName;
		using RType = typename Type::RType;

		static constexpr int Lelve = Type::Lelve;

	};
}
