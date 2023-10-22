#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{
	template<class T_Tuple,class T_Action>
	struct I_For
	{
		template<class T_Tuple,class T_Select=typename T_Tuple::type>
		struct S_For
		{

		};

		using type=S_For

	};

}