#pragma once

#include"Parameter_convertible_to.h"
#include"SwapType.h"


namespace N_Function
{
	template<class ...T_Fn_Parts>
	struct S_Function_Single_Data;
	
	template<class ...MT_Fn_Parts>
	struct IS_Function_Single_Data_Helper
	{

		using Lapping_Fn = S_Function_Single_Data<MT_Fn_Parts...>;

		using Request_Args= typename Lapping_Fn::RequestArgs;
		using Bound_Args = typename Lapping_Fn::BoundArgs;

		using Judge = U_Judge_t<U_Element_t<0,MT_Fn_Parts...>,
			parameter_back_part_convertible_to<
			typename Lapping_Fn::BoundArgs,
			typename Lapping_Fn::RequestArgs>>;


		template<class TP_Request_Args = Request_Args,
			class TP_Bind_Args = typename Lapping_Fn::BindArgs>
		struct S_Function_Single_Data_Helper
		{

			template<
				int t_Request_Args_Number = Request_Args::Size - Bound_Args::Size,
				int t_Bind_Args_Number = 0>
			struct S_Bind_Args_Chack
			{
				
				static constexpr bool judge = convertible_to<U_Element_t<t_Bind_Args_Number,TP_Request_Args>, U_Element_t<t_Request_Args_Number, TP_Bind_Args>>;

				using Swap_1= S_Bind_Args_Chack<t_Request_Args_Number-1,t_Bind_Args_Number-1>;


				using Type = S_Bind_Args_Chack<>;
			};


			using Type = S_Bind_Args_Chack<U_Element_t<TP_Request_Args, t_Request_Args_Number>, U_Element_t<TP_Bind_Args, t_Bind_Args_Number>>;


		};
			

		using Type = S_Function_Single_Data_Helper<>;



	};

};

