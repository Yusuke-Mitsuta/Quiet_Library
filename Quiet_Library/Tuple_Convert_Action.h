/*!
 * Tuple_Type_Change_Action.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Tuple_Declare.h"

#include"Tuple_Convert_Action_Helper.h"

namespace quiet::N_Tuple
{
	//仕様
	//[T_Convert_Tuple]を指定したTupleに変形する。
	//	テンプレートテンプレートパラメータ[T_Action<...>]のパラメータとしてセットする。
	//	その後メンバー宣言の[type]を呼び出す。
	//実行後の型に対して、Tupleに変形時と逆の動作を行う。
	struct I_Tuple_Convert_Action
	{
	public:

		using Target_Tuple_tp = N_Tuple_Convert_Action::I_Helper<true, true>::type;

		using Target_Tuple_vp = N_Tuple_Convert_Action::I_Helper<true,false>::type;

		using Target_Tuple_t = N_Tuple_Convert_Action::I_Helper<false, true>::type;

		using Target_Tuple_v = N_Tuple_Convert_Action::I_Helper<false,false>::type;
	};

}