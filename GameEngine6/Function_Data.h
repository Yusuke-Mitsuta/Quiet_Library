#pragma once

#include"Function_Core.h"
#include"Method_Core.h"
#include"Parameter.h"

namespace N_Function
{

	template<class ...T_Fn_Parts>
	struct S_Function_Single_Data;

	template<class ...T_Fn_Parts>
	struct IS_Function_Multiple_Helper;

	template<int t_Number,class ...T_Fn_Parts>
	struct IS_Function_Data
	{

		template<int t_Number, class ...T_Fn_Parts>
		struct S_Function_Data
		{
			using Function_Multiple = IS_Function_Multiple_Helper<T_Fn_Parts...>::Not_Pointer_Judge;

			using Type = U_Element_t<t_Number, Function_Multiple>;
		};

		template<class ...T_Fn_Parts>
			requires not_is_nullopt
				<typename S_Function_Single_Data<T_Fn_Parts...>::Method>
		struct S_Function_Data<0,T_Fn_Parts...>
		{
			using Type = S_Function_Single_Data<T_Fn_Parts...>;
		};

		using Type = typename  S_Function_Data<t_Number, T_Fn_Parts...>::Type;

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
