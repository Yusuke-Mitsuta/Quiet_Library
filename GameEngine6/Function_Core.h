#pragma once

#include"Function_Valid_Data.h"

namespace quiet::N_Function
{
	//�d�l
	//�N���X���\�b�h�ƃ��\�b�h�𓯈���@�ň����ׂ̃N���X
	template<class ...T_Parts>
	struct Function_Core :
		I_Function_Valid_Data<T_Parts...>
	{


	};

}
