#pragma once

#include"Tuple_Declare.h"
#include"Tuple_Apply_Type.h"
#include"Tuple_Apply_Fn.h"
#include"Tuple_Apply_Array_Set.h"
#include"Tuple_Apply_Request.h"
#include"Tuple_Apply_Class_Create.h"
#include"Tuple_Infinite.h"
#include"If_Type.h"

namespace N_Tuple::N_Apply
{

	template<class T_Expand, size_t t_point>
	struct S_Conversion_Expand;

	template<class T_Zip, size_t t_point>
	struct S_Conversion_Zip;


	//�d�l
	//��������^�̃��X�g����A�v������^�̃��X�g�ɁA�^�̓W�J�𔺂��ϊ����o���邩���肷��B
	//
	//�⑫
	// �^�̔���͌�납����{����B
	//template<class T_Request_Types_Tuple,
	//	class T_Set_Types_Tuple>
	//struct I_Apply_Type_Chack
	//{



	//	using conversion = type;

	//};



}