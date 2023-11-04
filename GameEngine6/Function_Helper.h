#pragma once

#include"Concept.h"
#include"Parameter.h"

namespace N_Function
{

	template<class ...T_Fn_Parts>
	struct S_Function_Single_Data;

	template<class ...T_Fn_Parts>
	struct I_Function_Multiple_Helper;

	//仕様
	//関数に対して、次の関数又はメソッドが出てくるまでの間の型が引数の型と互換性があるか判定する
	//メソッドに対しては、上記に加え、メソッドの前の型がポインターの型と互換性があるか判定し、
	//	失敗すれば、テンプレートの先頭の型がポインターの型と互換性があるか判定する
	//この操作を繰り返し、全て成功すれば、関数、メソッドオブジェクト事に纏められた後、[tuple_t]に纏められる。
	//
	//テンプレート
	//[T_Fn_Parts...]:
	//	メソッドに使用する共通のポインターの型(省略可能)
	//	関数、又はメソッドの型
	//	それに対する引数の型(並びの一番後ろの型が、関数の引数型の一番後ろと判定される)
	//	次のメソッドに対する専用のポインターの型(次にメソッドを使用する場合)
	//	関数、又はメソッドの型
	// と続く
	// 
	//補足 
	//関数に対する引数の型として関数の型を取る場合
	//その間の型と引数の型に互換性があれば、引数として取ろうとしてる関数の型が次の関数として見なされる為、
	//	単体の関数として処理をする事
	template<class ...T_Fn_Parts>
	struct I_Function_Helper
	{
		using single_judge = S_Function_Single_Data<T_Fn_Parts...>;

		using multiple_judge = I_Function_Multiple_Helper<T_Fn_Parts... >;

		template<bool t_function_check_fg, bool t_method_check_fg,
				 class T_Function_Check = typename single_judge::function,
				 class T_Method_Check= typename single_judge::method>
		struct S_Function_Helper
		{
			using type = tuple_t<T_Function_Check>;
		};

		template<bool t_function_check_fg, bool t_method_check_fg,class T_Method_Check>
		struct S_Function_Helper<t_function_check_fg,t_method_check_fg,invalid_t,T_Method_Check>
		{
			using type = tuple_t<T_Method_Check>;
		};

		template<>
		struct S_Function_Helper<true,true, invalid_t, invalid_t>
		{
			using type = multiple_judge::type;
		};

		template<>
		struct S_Function_Helper<true,false, invalid_t, invalid_t>
		{
			using type = multiple_judge::function_check;
		};

		template<>
		struct S_Function_Helper<false,true, invalid_t, invalid_t>
		{
			using type = multiple_judge::method_check;
		};


		//仕様
		//ファンクションとして判定し、失敗すれば、メソッドとして判定する
		using type = S_Function_Helper<true, true>::type;

		//仕様
		//ファンクションとして判定する
		using function_check = S_Function_Helper<true, false>::type;

		//仕様
		//メソッドとして判定する
		using method_check = S_Function_Helper<false, true,invalid_t>::type;

	};


}