#pragma once

#include"Tuple_Declare.h"

namespace quiet::N_Tuple
{

	//仕様
	//[T_Change_Type]をTupleに変換する。
	//その後、[tuple_t,tuple_tp,tuple_v,tuple_vp]のいずれかに変換する。
	//
	//テンプレート
	//[t_is_Target_Tuple_p]::要求するTupleがポイントを所持[tuple_tp,tuple_vp]であるか？
	//[t_is_Target_Tuple_t]::要求するTupleが型を管理[tuple_t,tuple_tp]であるか？
	//
	//型の変化は[2つ進む or 1つ戻る]のどちらかで変化をさせる
	//[tp → t → v → vp → tp]
	//

	template<class T_Change_Type,bool t_is_Target_Tuple_p, bool t_is_Target_Tuple_t>
	struct I_Change_Tuple
	{

		template<class T_Convert_Tuple,bool t_Target_Tuple_p= t_is_Target_Tuple_p, bool t_Target_Tuple_t= t_is_Target_Tuple_t>
		struct S_Change_Tuple
		{
			using type = T_Convert_Tuple;
		};

		//t→v
		//vp←tp
		template<class T_Convert_Tuple,bool t_Target_Tuple_p>
			requires requires
		{
			requires (same_as_tuple_t<T_Convert_Tuple>) || (same_as_tuple_tp<T_Convert_Tuple> && t_Target_Tuple_p);
		}
		struct S_Change_Tuple<T_Convert_Tuple,t_Target_Tuple_p, false>
		{
			using type = S_Change_Tuple<U_Tuple_t_To_v<T_Convert_Tuple>,t_Target_Tuple_p, false>::type;
		};

		//v→vp
		//tp←t
		template<class T_Convert_Tuple,bool t_Target_Tuple_t>
			requires requires
		{
			requires (same_as_tuple_v<T_Convert_Tuple>) || (same_as_tuple_t<T_Convert_Tuple> && t_Target_Tuple_t);
		}
		struct S_Change_Tuple<T_Convert_Tuple,true, t_Target_Tuple_t>
		{
			using type = S_Change_Tuple<U_Create_p<T_Convert_Tuple>,true, t_Target_Tuple_t>::type;
		};

		//vp→tp
		//t←v
		template<class T_Convert_Tuple,bool t_Target_Tuple_p>
			requires requires
		{
			requires (same_as_tuple_vp<T_Convert_Tuple>) || (same_as_tuple_v<T_Convert_Tuple> && !t_Target_Tuple_p);
		}
		struct S_Change_Tuple<T_Convert_Tuple,t_Target_Tuple_p, true>
		{
			using type = S_Change_Tuple<U_Tuple_v_To_t<T_Convert_Tuple>,t_Target_Tuple_p, true>::type;
		};

		//tp→t
		//v←vp
		template<class T_Convert_Tuple,bool t_Target_Tuple_t>
			requires requires
		{
			requires (same_as_tuple_tp<T_Convert_Tuple>) || (same_as_tuple_v<T_Convert_Tuple> && !t_Target_Tuple_t);
		}
		struct S_Change_Tuple<T_Convert_Tuple,false, t_Target_Tuple_t>
		{
			using type = S_Change_Tuple< U_Remove_p<T_Convert_Tuple>,false, t_Target_Tuple_t>::type;
		};

		using type = S_Change_Tuple<typename S_Parameter<T_Change_Type>::tuple>::type;

	};

}