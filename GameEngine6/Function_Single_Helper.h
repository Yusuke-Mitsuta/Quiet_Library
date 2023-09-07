#pragma once

#include"Parameter_convertible_to.h"
#include"SwapType.h"

namespace N_Function
{
	template<class ...MT_Fn_Parts>
	struct S_Function_Single_Data;
	
	template<class ...MT_Fn_Parts>
	struct IS_Function_Single_Helper
	{
		using Lapping_Meth = S_Function_Single_Data<MT_Fn_Parts...>;

		using Judge = U_Judge_t<U_Element_t<0,MT_Fn_Parts...>,
			parameter_back_part_convertible_to<
			typename Lapping_Meth::BoundArgs,
			typename Lapping_Meth::RequestArgs>>;

	};

};

