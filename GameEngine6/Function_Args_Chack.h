#pragma once

#include"Tuple.h"
#include"Expand.h"

namespace N_Function
{


	template<class T_Request_Args,class T_Bind_Args>
	struct I_Function_Args_Chack
	{
	//private:

		//仕様
		//T_Request_Args,T_Bind_Argsの中身を適正に展開した結果を返す
		template<class T_Result_Request_Args, class T_Result_Bind_Args>
		struct S_Result
		{
			using Request_Args = T_Result_Request_Args;
			using Bind_Args = T_Result_Bind_Args;
		};


		//仕様
		//[T == invalid_t]なら[T_Next_Type::type]
		//[T != invalid_t]なら[T]を返す
		template<class T,class T_Next_Type>
		struct S_Next
		{
			using type = T;
		};

		template<class T_Next_Type>
		struct S_Next<invalid_t,T_Next_Type>
		{
			using type = T_Next_Type::type;
		};

		//仕様
		//[T_Request_Args]要求する引数の後ろと,[T_Bind_Args]の後ろから引数の型を精査する
		//[T_Request_Args]及び、[T_Bind_Args]の引数の型が正しくない場合[S_Expand]により展開し再度、型の精査を行う
		//
		//テンプレート
		//T_Request_Args::要求する引数の並びを反転させた型
		//T_Bind_Args::指定する引数の並びを反転させた型
		//t_End_fg::T_Bind_Argsを最後まで精査したかのフラグ
		template<class T_Request_Args =typename T_Request_Args::reverse, class T_Bind_Args =typename T_Bind_Args::reverse::front,
			bool t_End_fg = is_invalid<typename T_Bind_Args::type>>
		struct S_Args_Chack
		{
			using type = invalid_t;
		};

		//仕様
		//[T_Tuple_t::type]を[S_Expand]により展開、反転させ、[T_Tuple_t::type]と入れ替える
		template<class T_Tuple_t>
		struct S_Expand_Change
		{
			using type = N_Tuple::U_Change_tuple_expand<T_Tuple_t,
				typename S_Expand<typename T_Tuple_t::type>::type::reverse>;
		};

		//仕様
		//[check_concept]の条件に従って展開した[T_Args]と[T_Args_List]を
		//判定し、一致しなければ、[T_Args_List]の選択位置を進めて再度判定する、
		// 一致すれば[S_Args_Chack]を実行し、成功すれば結果を、
		// 失敗すれば[T_Args_List]の選択位置を進めて再度判定する
		//その結果、[T_Args_List]が全ての[T_Args]と一致しなければ、[invalid_t]を返す
		template<template<class,class>class check_concept,class T_Args,class T_Args_List,
			bool t_Next_Fg= check_concept<typename T_Args::type,typename T_Args_List::type::type>::value>
		struct S_Expand_Args_Check
		{
			using type = S_Expand_Args_Check<check_concept, T_Args,typename T_Args_List::next>::type;
		};

		//仕様
		//[T_Args]=[Bind_Args],[T_Args_List::type]=[Request_Args]
		//とし[S_Args_Chack]を実行する
		//成功すれば値を、失敗すれば[T_Args_List]を進める
		template<class T_Args, class T_Args_List>
		struct S_Expand_Args_Check<std::is_constructible,T_Args, T_Args_List,true>
		{
			using n = T_Args_List;
			using result_type= S_Args_Chack<typename T_Args_List::type, T_Args>::type;
			using type = S_Next<result_type, S_Expand_Args_Check<std::is_constructible, T_Args,typename T_Args_List::next>>::type;
		};


		//仕様
		//[T_Args]=[Request_Args],[T_Args_List::type]=[Bind_Args]
		//とし[S_Args_Chack]を実行する
		//成功すれば値を、失敗すれば[T_Args_List]を進める
		template< class T_Args, class T_Args_List>
		struct S_Expand_Args_Check<is_convertible_from, T_Args, T_Args_List, true>
		{
			using result_type = S_Args_Chack<T_Args,typename T_Args_List::type>::type;
			using type = S_Next<result_type, S_Expand_Args_Check<is_convertible_from, T_Args, typename T_Args_List::next>>::type;

		};

		//仕様
		//[T_Args_List]の最後まで精査し一つも正しくなければ、[ invalid_t]とする
		template<template<class, class>class check_concept, class T_Args, class T_Head>
		struct S_Expand_Args_Check<check_concept,T_Args, tuple_tp<T_Head,invalid_t,tuple_t<>>>
		{
			using type = invalid_t;
		};

		//仕様
		//[T_Request_Args::type],[T_Bind_Args::type]で展開出来るか判定し、可能であれば展開し
		//展開後のリストと、展開してない方の[T_Request_Args_List]or[T_Bind_Args_List]の全ての型と判定する。
		//判定が失敗すれば、展開した方の型のlistに展開後の型を追加し、展開後の型が更に展開出来るか判定する。
		//展開できなく、型の判定に失敗すれば[std:;nullopt_t]を返す
		template<class T_Request_Args, class T_Bind_Args, class T_Request_Args_List = tuple_t<T_Request_Args>, class T_Bind_Args_List = tuple_t<T_Bind_Args>, bool t_Loop_fg =(!is_expand<typename T_Request_Args::type>)|| (!is_expand<typename T_Bind_Args::type>)>
		struct S_Expand_Args
		{
			using type = invalid_t;
		};


		//仕様
		//[T_Request_Args::type]展開し、展開後のリストと、[T_Bind_Args_List]の全ての型と判定する。
		//判定が失敗すれば、[T_Request_Args_List]に展開後の型を追加し、展開後の型が更に展開出来るか判定する。
		template<class T_Request_Args, class T_Bind_Args, class T_Request_Args_List, class T_Bind_Args_List>
			requires (is_expand<typename T_Request_Args::type>)
		struct S_Expand_Args<T_Request_Args,T_Bind_Args, T_Request_Args_List, T_Bind_Args_List,true>
		{
			using Expand_Request_Args = typename S_Expand_Change<T_Request_Args>::type;

			using type = S_Next<typename S_Expand_Args_Check<
				is_convertible_from,Expand_Request_Args,
				T_Bind_Args_List>::type,
				S_Expand_Args<Expand_Request_Args, T_Bind_Args, N_Tuple::U_Merge< T_Request_Args_List, Expand_Request_Args>, T_Bind_Args_List>>::type;

		};

		//仕様
		//[T_Bind_Args::type]展開し、展開後のリストと、[T_Request_Args_List]の全ての型と判定する。
		//判定が失敗すれば、[T_Bind_Args_List]に展開後の型を追加し、展開後の型が更に展開出来るか判定する。
		template<class T_Request_Args, class T_Bind_Args, class T_Request_Args_List, class T_Bind_Args_List>
			requires (is_expand<typename T_Bind_Args::type>)
		struct S_Expand_Args<T_Request_Args, T_Bind_Args, T_Request_Args_List, T_Bind_Args_List, true>
		{
			using Expand_Bind_Args = typename S_Expand_Change<T_Bind_Args>::type;
			using Expand_Bind_Args1 = typename S_Expand_Change<T_Bind_Args>;

			//using type = invalid_t;


			using type1 = typename S_Expand_Args_Check<
				std::is_constructible,
				Expand_Bind_Args
				, T_Request_Args_List>;

			using type = S_Next<typename S_Expand_Args_Check<
				std::is_constructible,
				Expand_Bind_Args
				, T_Request_Args_List>::type,
				S_Expand_Args<T_Request_Args,Expand_Bind_Args, T_Request_Args_List,N_Tuple::U_Merge<T_Bind_Args_List, Expand_Bind_Args>>>::type;

		};

		//仕様
		//[T_Request_Args::type]展開し、展開後のリストと、[T_Bind_Args_List]の全ての型と判定する。
		//判定が失敗すれば、[T_Request_Args_List]に展開後の型を追加し、
		// [T_Bind_Args::type]展開し、展開後のリストと、[T_Request_Args_List]の全ての型と判定する。
		//判定が失敗すれば、[T_Bind_Args_List]に展開後の型を追加し、[T_Request_Args::type],[T_Bind_Args::type]の展開後の型が更に展開出来るか判定する。
		template<class T_Request_Args, class T_Bind_Args, class T_Request_Args_List, class T_Bind_Args_List>
			requires (is_expand<typename T_Request_Args::type>) && (is_expand<typename T_Bind_Args::type>)
		struct S_Expand_Args<T_Request_Args, T_Bind_Args, T_Request_Args_List, T_Bind_Args_List, true>
		{
			using Expand_Request_Args = typename S_Expand_Change<T_Request_Args>::type;
			using Expand_Bind_Args = typename S_Expand_Change<T_Bind_Args>::type;

			using Request_Args_List_Merge = N_Tuple::U_Merge<T_Request_Args_List,Expand_Request_Args>;
			using Bind_Args_List_Merge = N_Tuple::U_Merge<T_Bind_Args_List, Expand_Bind_Args>;

			using Expand_Args_Check = S_Next<typename S_Expand_Args_Check<
				is_convertible_from, Expand_Request_Args
				, Bind_Args_List_Merge>::type,
				S_Expand_Args_Check<std::is_constructible, Expand_Bind_Args
				, T_Request_Args_List>>;

			using type = S_Next<typename Expand_Args_Check::type,
				S_Expand_Args<Expand_Request_Args, Expand_Bind_Args, Request_Args_List_Merge, Bind_Args_List_Merge >>::type;
		};



		//仕様
		//[T_Request_Args::type]が[T_Bind_Args::type]から変換可能な時、
		//[T_Request_Args],[T_Bind_Args]を１つ進める
		template<class T_Request_Args, class T_Bind_Args>
			requires convertible_to<typename T_Bind_Args::type, typename T_Request_Args::type>
		struct S_Args_Chack<T_Request_Args, T_Bind_Args, false>
		{
			using type = S_Args_Chack<typename T_Request_Args::next, typename T_Bind_Args::next>::type;
		};

		//仕様
		//[T_Request_Args::type]が[T_Bind_Args::type]から変換不可能な時、[S_Expand]により展開し再度、型の精査を行う
		template<class T_Request_Args, class T_Bind_Args>
			requires not_convertible_to<typename T_Bind_Args::type, typename T_Request_Args::type>
		struct S_Args_Chack<T_Request_Args, T_Bind_Args, false>
		{
			using type = S_Expand_Args<T_Request_Args, T_Bind_Args>::type;	
			using type1 = S_Expand_Args<T_Request_Args, T_Bind_Args>;	
		};

		//仕様
		//判定が成功した時、resultを作成する
		//[T_Request_Args]は反転させたのを戻し、
		//[T_Bind_Args]は反転させたのを戻し、ポインタを取り除く
		template<class T_Request_Args, class T_Bind_Args>
		struct S_Args_Chack<T_Request_Args, T_Bind_Args, true>
		{
			template<class T_Tuple_p>
			using reverse_and_remove_p =typename T_Tuple_p::reverse::remove_p;

			using type = S_Result<typename T_Request_Args::reverse, typename T_Bind_Args::reverse::remove_p>;
		};

		template<class T>
		struct S_null_chack
		{
			using request_args = T::Request_Args;
			using bind_args = T::Bind_Args;
		};

		template<>
		struct S_null_chack<invalid_t>
		{
			using request_args = invalid_t;
			using bind_args = invalid_t;
		};

	public:
		using type = typename S_Args_Chack<>;

		using request_args = S_null_chack<typename S_Args_Chack<>::type>::request_args;

		using bind_args = S_null_chack<typename S_Args_Chack<>::type>::bind_args;

	};




}
