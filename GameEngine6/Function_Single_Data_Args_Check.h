//#pragma once
//
//#include"Function_Single_Data.h"
//
//namespace N_Function
//{
//	template<class ...T_Fn_Parts>
//	template<class T_Fns, class ...T_Bind_Args>
//	struct I_Function_Single_Data<T_Fn_Parts...>::S_Args
//	{
//
//		template<class T_Request_args>
//		struct S_request_args
//		{
//			using type = S_Args<T_Request_args, T_Bind_Args...>::request_args;
//		};
//
//		template<class ...T_Fns_Request_args>
//		struct S_request_args<tuple_t<T_Fns_Request_args...>>
//		{
//			using type = tuple_t<typename S_request_args<T_Fns_Request_args>::type...>;
//
//			//typename S_request_args<T_Flont_Fn_Request_args>::type,
//			//typename S_request_args<tuple_t<T_Fns_Request_args...>>::type>;
//
//		};
//
//
//		template<class T_Fn_Core>
//		struct S_before_request_args
//		{
//			using type = typename S_Function_Data<T_Fn_Core>::request_args;
//
//		};
//
//		template<class ...T_Fns_Core, class ...T_before_Bind_Args>
//		struct S_before_request_args<Function_Core<tuple_t<T_Fns_Core...>, T_before_Bind_Args...>>
//		{
//			using type = tuple_t<typename S_before_request_args<Function_Core<T_Fns_Core, T_before_Bind_Args...>>::type...>;
//
//		};
//
//
//		using request_args = S_request_args<S_before_request_args<T_Fns>>::type;
//
//		using bind_args = tuple_t<T_Bind_Args...>;
//
//	};
//
//	//�d�l
//	//[using request_args],[using bind_args]���`����
//	//�v����������̌^�ɁA�w�肷������̌^�������������肷��
//	// 
//	//�e���v���[�g
//	//[tuple_tp<T_Head,T,T_Tail>]::�v����������̌^�A�y�сA���̌^�̖�����̈����̈ʒu������
//	//[T_Bind_Args...]::�w�肷������̌^
//	template<class ...T_Fn_Parts>
//	template<class T_Head, class T, class T_Tail, class ...T_Bind_Args>
//	struct I_Function_Single_Data<T_Fn_Parts...>::S_Args<tuple_tp<T_Head, T, T_Tail>, T_Bind_Args...>
//	{
//	private:
//		using args_chack = I_Function_Args_Chack<
//			tuple_tp<T_Head, T, T_Tail>, tuple_t<T_Bind_Args...>>;
//
//	public:
//		using request_args = args_chack::request_args;
//
//		using bind_args = tuple_t<T_Bind_Args...>;
//		//args_chack::bind_args;
//
//	};
//
//
//
//TEST
//<
//	N_Function::Function_Core
//	<
//	N_Function::Function_Core
//	<
//	void(__cdecl*)(int, int, int), int
//	>
//	, int
//	>
//>,
//TEST
//<
//	N_Function::Function_Core
//	<
//	N_Function::Function_Core<void(__cdecl*)(int, int, int)
//	>
//	, int
//	>
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
