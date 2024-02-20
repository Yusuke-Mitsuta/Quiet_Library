#pragma once

#include"Tuple.h"

namespace quiet::N_Function
{

	template<class T_Request_Args, class T_Bind_Args>
	struct I_Function_Args_Chack
	{
		using type = invalid_t;
	};
	
	//仕様
	//[T_Request_Args]と[T_Bind_Args]を比較し、
	//　互換性のある型か判定する。
	//
	// テンプレート
	// [T_Request_Args]：要求する引数の型(tuple_tp)
	// [T_Bind_Args]：セットする引数の型(tuple_t)
	// 
	//補足
	// 互換性のある型の定義は、[N_Tuple::S_Parameter]の特殊化にて定義を行う
	template<class T_Request_Args, class T_Bind_Args>
		requires requires
	{
		requires N_Tuple::is_Tuple_t<T_Request_Args>;
		requires N_Tuple::is_Tuple_t<T_Bind_Args>;
	}
	struct I_Function_Args_Chack<T_Request_Args,T_Bind_Args>
	{
	public:


		//改善メモ
		//要求する型のリストは[tuple_tp]、
		//複数の要求する型リストを纏めた型は[tuple_t]で区別しているため改善すること

		//仕様
		//[I_Convert_Order]による照合し、
		// セットした引数全てで互換性があるか判定する
		// 
		// 補足
		//要求する型のリストは[tuple_tp]、
		// 複数の要求する型リストを纏めた型は[tuple_t]で区別している
		template<class T_Chack_Result =
			typename N_Tuple::N_Apply::I_Convert_Order<typename T_Request_Args::remove_p, T_Bind_Args>::type,
			//class T_Request_Args = typename T_Chack_Result::request,
			class T_Bind_Args= typename T_Chack_Result::set>
		struct S_Function_Args_Chack
		{
			using type = invalid_t;
		};

		template<class T_Chack_Result>
		struct S_Function_Args_Chack<T_Chack_Result, tuple_t<>>
		{
			using type = typename T_Chack_Result::request::create_p;
		};

		using type = typename S_Function_Args_Chack<>::type;

	};

}
