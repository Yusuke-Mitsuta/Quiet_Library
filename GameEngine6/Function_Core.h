#pragma once

#include"Function_Single_Data.h"


namespace N_Function
{
	//�d�l
	//�N���X���\�b�h�ƃ��\�b�h�𓯈���@�ň����ׂ̃N���X
	template<class ...T_Parts>
	struct Function_Core :
		I_Function_Single_Data<T_Parts...>
	{


	};

}
