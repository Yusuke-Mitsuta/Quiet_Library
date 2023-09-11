#pragma once

#include"Parameter.h"
#include"Parameter_convertible_to.h"
#include"Expand.h"

namespace N_Function
{


	template<class T_Request_Args,class T_Bind_Args>
	struct IS_Request_Args
	{
	private:
		template<class T_Result_Request_Args, class T_Result_Bind_Args>
		struct S_Result
		{
			using Request_Args = T_Result_Request_Args;
			using Bind_Args = T_Result_Bind_Args;
		};

		template<
			class TP_Request_Args = T_Request_Args,
			class TP_Bind_Args = T_Bind_Args,
			int t_Request_Args_Number = T_Request_Args::Size - 1,
			int t_Bind_Args_Number = T_Bind_Args::Size - 1,
			class T_Request_Args_Part = U_Element_t<t_Request_Args_Number, TP_Request_Args>,
			class T_Bind_Args_Part = U_Element_t<t_Bind_Args_Number, TP_Bind_Args>,
			bool t_Loop_Fg = static_cast<bool>(t_Bind_Args_Number)>
		struct S_Request_Args
		{
			using Type = S_Result< std::nullopt_t, std::nullopt_t>;
		};


		template<
			class TP_Request_Args, class TP_Bind_Args,
			int t_Request_Args_Number, int t_Bind_Args_Number,
			class T_Request_Args_Part, class T_Bind_Args_Part>
			requires convertible_to<T_Bind_Args_Part, T_Request_Args_Part>
		struct S_Request_Args<TP_Request_Args, TP_Bind_Args, t_Request_Args_Number, t_Bind_Args_Number,
			T_Request_Args_Part, T_Bind_Args_Part, true>
		{
			using Type = S_Request_Args<TP_Request_Args, TP_Bind_Args, t_Request_Args_Number - 1, t_Bind_Args_Number - 1>::Type;
		};

		template<
			class TP_Request_Args, class TP_Bind_Args,
			int t_Request_Args_Number, int t_Bind_Args_Number,
			class T_Request_Args_Part, class T_Bind_Args_Part>
			requires not_convertible_to<T_Bind_Args_Part, T_Request_Args_Part>&&
		is_expand<T_Request_Args_Part>
			struct S_Request_Args<TP_Request_Args, TP_Bind_Args, t_Request_Args_Number, t_Bind_Args_Number,
			T_Request_Args_Part, T_Bind_Args_Part, true>
		{
			using Remove = U_Remove_Element_t<TP_Request_Args, t_Request_Args_Number>;

			using Expand = S_Expand<T_Request_Args_Part>::Type ;

			using Request_Args = U_Insert_Element_P_t<Remove, t_Request_Args_Number, Expand>;

			using Type = S_Request_Args<Request_Args, TP_Bind_Args, t_Request_Args_Number + Expand::Size - 1, t_Bind_Args_Number>::Type;

		};

		template<
			class TP_Request_Args, class TP_Bind_Args,
			int t_Request_Args_Number, int t_Bind_Args_Number,
			class T_Request_Args_Part, class T_Bind_Args_Part>
			requires not_convertible_to<T_Bind_Args_Part, T_Request_Args_Part> &&
		!is_expand<T_Request_Args_Part> && is_expand<T_Bind_Args_Part>
			struct S_Request_Args<TP_Request_Args, TP_Bind_Args, t_Request_Args_Number, t_Bind_Args_Number,
			T_Request_Args_Part, T_Bind_Args_Part, true>
		{
			using Remove = U_Remove_Element_t<TP_Bind_Args, t_Bind_Args_Number>;

			using Expand =S_Expand<T_Bind_Args_Part>::Type;

			using Bind_Args = U_Insert_Element_P_t<Remove, t_Bind_Args_Number,Expand>;

			using Type = S_Request_Args<TP_Request_Args,Bind_Args,t_Request_Args_Number, t_Bind_Args_Number + Expand::Size - 1>::Type;

		};

		template<
			class TP_Request_Args, class TP_Bind_Args,
			int t_Request_Args_Number, int t_Bind_Args_Number,
			class T_Request_Args_Part, class T_Bind_Args_Part>
			requires convertible_to<T_Bind_Args_Part, T_Request_Args_Part>
		struct S_Request_Args<TP_Request_Args, TP_Bind_Args, t_Request_Args_Number, t_Bind_Args_Number,
			T_Request_Args_Part, T_Bind_Args_Part, false>
		{
			using Request_Args = U_Range_Element_t<TP_Request_Args, 0, t_Request_Args_Number>;

			using Type= S_Result<Request_Args,TP_Bind_Args>;
		};

		template<class T_Request_Args=T_Request_Args, class T_Bind_Args=T_Bind_Args>
		struct S_Args_Empty_Judge 
		{
			using Type = S_Request_Args<>::Type;
		};

		template<class T_Bind_Args>
			requires (static_cast<bool>(T_Bind_Args::Size))
		struct S_Args_Empty_Judge<S_Parameter<>,T_Bind_Args>
		{
			using Type = S_Result<std::nullopt_t, std::nullopt_t>;
		};
		template<class T_Request_Args>
		struct S_Args_Empty_Judge<T_Request_Args, S_Parameter<>>
		{
			using Type = S_Result<T_Request_Args, S_Parameter<>>;
		};

		using Type = S_Args_Empty_Judge<>::Type;
	public:

		using Request_Args = Type::Request_Args;
		using Bind_Args = Type::Bind_Args;

	};




}
