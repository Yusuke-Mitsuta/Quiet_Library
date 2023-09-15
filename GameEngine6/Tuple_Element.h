#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{
	
	template<int _Index, class T_Tuple>
	struct I_Element
	{
		using Type =typename U_Select<_Index, T_Tuple>::Type;
	};

	template<size_t _Index,class T_Head_v,auto value,class T_Tail_v>
	struct I_Element<_Index,Tuple_vp<T_Head_v,value,T_Tail_v>>
	{
	private:
		using T_Tuple = Tuple_vp<T_Head_v, value, T_Tail_v>;
		template< class T_Tuple>
		struct S_Action
		{
			using Type = typename I_Select<static_cast<int>(_Index), T_Tuple>::Type;
		};


		using Action = S_Tuple_Action<T_Tuple, S_Action>;

		friend struct Action;

	public:

		static constexpr auto value = Action::Type::value;

	};

}