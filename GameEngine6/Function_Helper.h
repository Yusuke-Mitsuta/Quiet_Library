#pragma once

#include"Concept.h"
#include"Function_Single_Helper.h"
#include"Function_Multiple_Helper.h"

namespace quiet::N_Function
{

	//仕様
	// 関数に対して、次の関数オブジェクトが出てくるまでの間の型が引数の型と互換性があるか判定する
	//メソッドに対しては、上記に加え、メソッドの前の型がポインターの型と互換性があるか判定し、
	//	失敗すれば、テンプレートの先頭の型がポインターの型と互換性があるか判定する
	//この操作を繰り返し、全て成功すれば、[Function_Core]事に纏められた後、[tuple_t]に纏められる。
	//
	//テンプレート
	//[T_Fn_Parts...]:
	//	メソッドに使用する共通のポインターの型(省略可能)
	//	関数オブジェクトの型
	//	それに対する引数の型(並びの一番後ろの型が、関数の引数型の一番後ろと判定される)
	//	次のメソッドに対する専用のポインターの型(次にメソッドを使用する場合)
	//	関数オブジェクトの型
	// と続く
	// 
	//補足
	//関数に対する引数の型として関数の型を取る場合
	//その間の型と引数の型に互換性があれば、引数として取ろうとしてる関数の型が次の関数として見なされる為、
	//	単体の関数として処理をする事
	template<class ...T_Fn_Parts>
	struct I_Function_Helper
	{
	private:

		//仕様
		//単体の関数オブジェクトとして処理できるか判定する
		template<class T_Fn_Single = I_Function_Single_Helper<T_Fn_Parts...>,
			class T_Fn_Single_Judge =typename T_Fn_Single::judge>
		struct S_Function_Helper
		{
			using type = T_Fn_Single;
		};

		//仕様
		//単体の関数オブジェクトとして処理できない場合、複数の関数オブジェクトとして判定する
		template<class T_Fn_Single>
		struct S_Function_Helper<T_Fn_Single,invalid_t>
		{
			using type = I_Function_Multiple_Helper<T_Fn_Parts...>;
		};

		using function_helper =
			//I_Function_Multiple_Helper<T_Fn_Parts...>;
			S_Function_Helper<>::type;
		
	public:

		//仕様
		//[Function_Core]が纏められた[tuple_t]、若しくは[Function_Core]
		using type = function_helper::type;

		//仕様
		//纏められた関数オブジェクト一つ一つに対応した、使用した型の番号をが纏められた[tupel_t]
		using access_number = function_helper::access_number;

		//仕様
		//纏め作業が成功すれば、[T_Fn_Parts...]の先頭の型が、失敗すれば、[invalid_t]を返す
		using judge = function_helper::judge;

	};


}