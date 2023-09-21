#pragma once

#include"Tuple_Declare.h"
#include"If_Type.h"



namespace N_Tuple
{

		template<bool t_Action_Type_Tuple_p, bool t_Action_Type_Tuple_t,bool t_Action_break, template<class...>class T_Action, class T_Tuple, class ...T_Types>
		struct S_Action_Tuple
		{
			using type = T_Action<T_Tuple>::Type;
		};

		template<bool t_Action_Type_Tuple_p, template<class...>class T_Action, is_Tuple_t T_Tuple_t, bool t_Action_break, class ...T_Types>
		struct S_Action_Tuple<t_Action_Type_Tuple_p,false, t_Action_break, T_Action, T_Tuple_t ,T_Types...>
		{
			using type = Tuple_v_To_t<typename S_Action_Tuple<t_Action_Type_Tuple_p, false, t_Action_break, T_Action,typename Tuple_t_To_v<T_Tuple_t>::Type,T_Types...>::type>::Type;
		};

		template<bool t_Action_Type_Tuple_t, bool t_Action_break,template<class...>class T_Action, is_Tuple_p T_Tuple_p, class ...T_Types >
		struct S_Action_Tuple<false, t_Action_Type_Tuple_t, t_Action_break, T_Action, T_Tuple_p, T_Types...>
		{
			using action_return = typename S_Action_Tuple<false, t_Action_Type_Tuple_t, t_Action_break, T_Action, U_Remove_p<T_Tuple_p>, T_Types...>::type;

			using create_p = U_if_t1<U_Select<S_Parameter<T_Tuple_p>::Size_Head,action_return>,U_Create_p<action_return>,
				(S_Parameter<T_Tuple_p>::Size == S_Parameter<action_return>::Size)>;

			using type = U_if_t1<action_return, create_p, t_Action_break>;
		};

		template<bool t_Action_Type_Tuple_p, bool t_Action_break, template<class...>class T_Action,is_Tuple_v T_Tuple_v, class ...T_Types >
		struct S_Action_Tuple<t_Action_Type_Tuple_p, true, t_Action_break, T_Action, T_Tuple_v, T_Types... >
		{
			using type = Tuple_t_To_v<typename S_Action_Tuple<t_Action_Type_Tuple_p,true, t_Action_break, T_Action, typename Tuple_v_To_t<T_Tuple_v>::Type, T_Types...>::type>::Type;
		};

		template< bool t_Action_Type_Tuple_t, bool t_Action_break, template<class...>class T_Action, is_Tuple_not_p T_Tuple_not_p, class ...T_Types >
		struct S_Action_Tuple<true, t_Action_Type_Tuple_t, t_Action_break, T_Action, T_Tuple_not_p, T_Types... >
		{
			using type = U_Remove_p<typename S_Action_Tuple<true, t_Action_Type_Tuple_t, t_Action_break, T_Action, U_Create_p<T_Tuple_not_p>, T_Types...>::type>;
		};


		template<bool t_Action_Type_Tuple_p, bool t_Action_Type_Tuple_t, template<class...>class T_Action, class T_Tuple, class ...T_Types>
		struct S_Action_Return_Tuple
		{
		private:
			template<bool t_Action_break>
			using Return_Tuple = S_Action_Tuple<t_Action_Type_Tuple_p, t_Action_Type_Tuple_t, (t_Action_break^
				is_Tuple_not_p<T_Tuple>), T_Action, T_Tuple, T_Types...>;

		public:
			using Return_not_p = Return_Tuple<true>::type;

			using Return_p = Return_Tuple<false>::type;

			using type = typename S_Action_Tuple<t_Action_Type_Tuple_p, t_Action_Type_Tuple_t, false, T_Action, T_Tuple, T_Types...>::type;

		};

}