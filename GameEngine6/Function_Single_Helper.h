#pragma once

#include"Parameter_convertible_to.h"
#include"SwapType.h"


namespace N_Function
{
	template<class ...T_Fn_Parts>
	struct S_Function_Single_Data;
	
	template<class ...MT_Fn_Parts>
	struct IS_Function_Single_Helper
	{
		using Lapping_Fn = S_Function_Single_Data<MT_Fn_Parts...>;

		using Judge = U_Judge_t<U_Element_t<0,MT_Fn_Parts...>,
			not_is_invalid<typename Lapping_Fn::RequestArgs>>;
		
		using Type = Judge;

	};

};

