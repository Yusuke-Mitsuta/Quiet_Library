/*!
 * Function_Request_Core.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Invalid.h"

namespace quiet::N_Function
{

	template<class T_Request_Args = invalid_t, class T_Request_Pointer = invalid_t>
	struct Request_Core
	{
		using request_args = T_Request_Args;

		using request_pointer = T_Request_Pointer;
	};



}