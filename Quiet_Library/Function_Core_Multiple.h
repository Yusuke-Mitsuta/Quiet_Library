/*!
 * Function_Core.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Function_Valid_Data.h"

namespace quiet::N_Function
{
	//�d�l
	//�����̊֐���Z�߂�N���X
	template<class ...T_Parts>
	struct Function_Core_Multiple :
		I_Function_Valid_Data<T_Parts...>
	{


	};

}
