#pragma once
#include"Expand.h"

namespace N_Function
{
	template<class T_Request_Args>
	struct I_Function_Request_Args_List
	{

		template<class T_Request_Args>
		struct S_Expand_Args
		{

		};

		template<class T_Request_Args>
			requires requires
		{
			requires is_expand<typename T_Request_Args::type>;
		}
		struct S_Expand_Args
		{
			//using type = 
		};


		template<class T_Result, class T_Request_Args>
		struct S_Expand_Set
		{
			//using type =S_

		};

	};

}