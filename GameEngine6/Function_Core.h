#pragma once

#include"Method_Core.h"

namespace N_Function
{
	//�d�l
	//�N���X���\�b�h�ƃ��\�b�h�𓯈���@�ň����ׂ̃N���X
	template<class T_Fn,class ...TP_Bind_Args>
	struct Function_Core 
	{
		constexpr Function_Core(T_Fn set_Methed, TP_Bind_Args... set_Args) {}

		constexpr Function_Core(void* set_p, T_Fn set_Methed, TP_Bind_Args... set_Args) {}

	};



}
