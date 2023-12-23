#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{
	//仕様
	//[tuple_name]の名前を[t_remove_lelve]の数だけ外していく
	template<class T_Tuple_name,size_t t_remove_lelve>
	struct I_Remove_name
	{
		template<class T_Tuple_name, size_t t_remove_lelve>
		struct S_Remove_name
		{
			using type = T_Tuple_name;
		};

		template<N_Constexpr::String t_name,class ...T_Types, size_t t_remove_lelve>
			requires (t_remove_lelve > 0)
		struct S_Remove_name<tuple_name_t<t_name,T_Types...>,t_remove_lelve>
		{
			using type = S_Remove_name<tuple_t<T_Types...>, t_remove_lelve - 1>::type;
		};

		template<N_Constexpr::String t_name, auto ...t_value, size_t t_remove_lelve>
			requires (t_remove_lelve > 0)
		struct S_Remove_name<tuple_name_v<t_name, t_value...>, t_remove_lelve>
		{
			using type = S_Remove_name<tuple_v<t_value...>, t_remove_lelve - 1>::type;

		};

		template<N_Constexpr::String t_name, is_Tuple T_Tuple, size_t t_remove_lelve>
			requires (t_remove_lelve > 0)
		struct S_Remove_name<tuple_name<t_name,T_Tuple>, t_remove_lelve>
		{
			using type = S_Remove_name<T_Tuple, t_remove_lelve - 1>::type;
		};

		using type = S_Remove_name<T_Tuple_name, t_remove_lelve>::type;
	};

}
