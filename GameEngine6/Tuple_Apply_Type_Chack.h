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


	//仕様
	//供給する型のリストから、要求する型のリストに、型の展開を伴い変換を出来るか判定する。
	//
	//補足
	// 型の判定は後ろから実施する。
	//template<class T_Request_Types_Tuple,
	//	class T_Set_Types_Tuple>
	//struct I_Apply_Type_Chack
	//{



	//	using conversion = type;

	//};



}