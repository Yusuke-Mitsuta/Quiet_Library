#pragma once

#include"Tuple.h"
#include"Expand.h"

namespace N_Function
{


	template<class T_Request_Args,class T_Bind_Args>
	struct IS_Request_Args
	{
	//private:

		template<class T_Result_Request_Args, class T_Result_Bind_Args>
		struct S_Result
		{
			using Request_Args = T_Result_Request_Args;
			using Bind_Args = T_Result_Bind_Args;
		};


		template<class T_Request_Args = T_Request_Args::reverse::flont, class T_Bind_Args = T_Bind_Args::reverse::flont, bool t_Loop_fg = false>
		struct S_Request_Args
		{

		};
		template<class T_Tuple_t>
		struct S_Expand_Change
		{
			using type = N_Tuple::U_Change_tuple_expand<T_Tuple_t,
				typename S_Expand<typename T_Tuple_t::type>::type::reverse>;
		};

		template<class T_Request_Args, class T_Bind_Args, class T_Request_Args_List = tuple_t<T_Request_Args>, class T_Bind_Args_List = tuple_t<T_Bind_Args>, bool t_Loop_fg = false>
		struct S_Expand_Args
		{

		};

		template<class T_Request_Args, class T_Bind_Args, class T_Request_Args_List, class T_Bind_Args_List>
			requires(convertible_to<T_Request_Args::type,T_Bind_Args::type>)
		struct S_Expand_Args<T_Request_Args, T_Bind_Args, T_Request_Args_List, T_Bind_Args_List, true>
		{

		};

		template<class T_Request_Args, class T_Bind_Args, class T_Request_Args_List, class T_Bind_Args_List>
			requires not_convertible_to<T_Request_Args::type, T_Bind_Args::type> &&
		(is_expand<T_Request_Args::type>)
		struct S_Expand_Args<T_Request_Args,T_Bind_Args, T_Request_Args_List, T_Bind_Args_List,true>
		{

		};


		//template<class T_Request_Args, class T_Bind_Args, class T_Request_Args_List, class T_Bind_Args_List>
		//struct S_Expand_Args<T_Request_Args, T_Bind_Args, T_Request_Args_List, T_Bind_Args_List, true>
		//{

		//};

		//template<class T_Request_Args, class T_Bind_Args, class T_Request_Args_List, class T_Bind_Args_List>
		//struct S_Expand_Args<T_Request_Args, T_Bind_Args, T_Request_Args_List, T_Bind_Args_List, true>
		//{

		//};

		template<class T_Request_Args, class T_Bind_Args>
			requires convertible_to<T_Bind_Args::type,T_Request_Args::type>
		struct S_Request_Args<T_Request_Args, T_Bind_Args, true>
		{
			using type = S_Request_Args<typename T_Request_Args::next,typename T_Bind_Args::next>::type;
		};

		template<class T_Request_Args, class T_Bind_Args>
			requires not_convertible_to<T_Bind_Args::type, T_Request_Args::type>
		struct S_Request_Args<T_Request_Args, T_Bind_Args, true>
		{
			using type = S_Expand_Args< T_Request_Args, T_Bind_Args>::type;	
		};



	public:

		using Request_Args = T_Request_Args;

		using Bind_Args = T_Bind_Args;

	};




}
