#pragma once

#include"Concept.h"
#include"Parameter.h"
#include<optional>

namespace N_Function
{
	//仕様
	//クラスメソッドとメソッドを同一方法で扱う為のクラス
	template<not_same_as<std::nullopt_t> T_Flont_Method_Parts,class ...T_Method_Parts>
	struct S_Method
	{
		S_Parameter<T_Flont_Method_Parts, T_Method_Parts...> method_Data;
		
		template<class ...MT_Method_Parts>
		S_Method(MT_Method_Parts... set_Method_Parts) :
			method_Data(set_Method_Parts) {}

	};

	template<class T_Flont_Method_Parts, class ...T_Method_Parts>
	S_Method(T_Flont_Method_Parts flont_Method_Part, T_Method_Parts... method_Parts) -> S_Method<T_Method_Parts...>;

}