#pragma once

#include"Concept.h"
#include"Parameter.h"
#include<optional>

namespace N_Function
{
	//�d�l
	//�N���X���\�b�h�ƃ��\�b�h�𓯈���@�ň����ׂ̃N���X

	template<class T_Method,class ...TP_Bind_Args>
	struct Method_Core
	{
		T_Method method;
		S_Parameter<TP_Bind_Args...> bind_Args;
		
		constexpr Method_Core(T_Method set_Method, TP_Bind_Args... set_Bind_Args) :
			method(set_Method), bind_Args(set_Bind_Args...) {}

	};

	template<class T_Method>
	struct Method_Core<T_Method>
	{
		T_Method method;

		constexpr Method_Core(T_Method set_Method) :
			method(set_Method) {}

	};

}