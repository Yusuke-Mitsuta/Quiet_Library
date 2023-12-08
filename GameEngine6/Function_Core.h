#pragma once

#include"Method_Core.h"

#include"Parts.h"

namespace N_Function
{
	//仕様
	//クラスメソッドとメソッドを同一方法で扱う為のクラス
	template<class ...T_Fn_Parts>
	struct Function_Core
	{
		template<N_Constexpr::String t_Parts_Name>
		using U_Search = U_Parts_Search<t_Parts_Name, T_Fn_Parts...>;

		using function = U_Search<"function">;

		using c_name = U_Search<"c_name">;

		using r_type = U_Search<"r_type">;

		using request_pointer = U_Search<"request_pointer">;

		using bind_args = U_Search<"bind_args">;

		using request_args = U_Search<"request_args">;
	};

}
