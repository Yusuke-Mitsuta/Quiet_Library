#pragma once

#include"Tuple_Declare.h"
#include"Tuple_Apply_Type.h"
#include"Tuple_Apply_Convert_Order.h"
#include"Tuple_Apply_Args_Convert_Action.h"
#include"Tuple_Apply_Type_Chack.h"

#include"main.h"

namespace N_Tuple
{

	namespace N_Apply
	{

		template<class T_Fn, class ...T_Set_Types>
		static constexpr bool Chack()
		{
			return static_cast<bool>(N_Apply::I_Type_Chack<
				typename  N_Apply::I_Request<T_Fn, T_Set_Types...>::args,
				tuple_t<T_Set_Types...>>::value+1);
		}

	}




	//仕様
	//変数に対して、一対多、多対一、多対多の変換を行い、
	// 関数オブジェクト、クラスコンストラクタを実行する
	//
	//テンプレート
	// [T_Fn_Action]：変数を入れて実行する、[関数ポインター、Function、クラス]の型
	//[T_Set_Types...]：一対多、多対一、多対多の変換を伴う変数
	// 
	//補足
	//実行は[::Apply(args...)]を呼び出す事
	//一対多の変換はコンストラクタを呼び出せる事、
	//多対一の変換は展開する変数のクラスに
	// [using tuple=tuple_t< ... >]、[auto& get<N>()]記述されている事。
	//
	// 一対多の変換時、変換後の[&],[*]は自動で補完されるが、
	// 変換後の変数と変換に用いた変数の関係は個別に定義されない限りコピーである。
	template<class T_Fn,class ...T_Set_Types>
	struct I_Apply_Action
	{
	//private:


		using request = N_Apply::I_Request<T_Fn, T_Set_Types...>;

		using apply = N_Apply::I_Args_Convert_Action<typename request::args,
			tuple_t<T_Set_Types...>>::type;

	public:

		//仕様
		//型[fn]に対して、要求するに[args...] を一対多、多対一の変換を行い、
		// [fn]のコンストラクタを実行する(生成する)。
		template<class T_Create_class = T_Fn, class ...T_Args>
			requires (N_Apply::is_apply_type<T_Create_class, N_Apply::E_Type::CLASS> ||
					  N_Apply::is_apply_type<T_Create_class, N_Apply::E_Type::CLASS_NEW>)
		static constexpr auto Apply(T_Args&&... args)
		{
			N_Apply::S_Class_Create<T_Create_class> fn_action = {};
			return apply::Apply(&fn_action, std::forward<T_Args>(args)...);
		}

		//仕様
		//配列型のポインター[array_p]に[T_Fn]の0次元目の要素数を追加する。
		template<class T_Array, class ...T_Args>
			requires N_Apply::is_apply_type<T_Fn, N_Apply::E_Type::ARRAY>
		static constexpr auto Apply(T_Array* array_p, T_Args&&... args)
		{
			N_Apply::S_Array_Create fn_action = { array_p };
			return apply::Apply(&fn_action, std::forward<T_Args>(args)...);
		}

		//仕様
		//関数[fn]に対して、要求するに[args...] を一対多、多対一の変換を行い、
		// [fn]を実行する
		template<class ...T_Args>
			requires N_Apply::is_apply_type<T_Fn, N_Apply::E_Type::FN>
		static constexpr auto Apply(T_Fn&& fn,T_Args&&... args)
		{
			N_Apply::S_Fn_Action fn_action(fn, &invalid);
			return apply::Apply(&fn_action,std::forward<T_Args>(args)...);
		
		}

		//仕様
		//関数[fn]に対して、要求するに[args...] を一対多、多対一の変換を行い、
		// ポインターを用いて[fn]を実行する
		template<class ...T_Args>
			requires N_Apply::is_apply_type<T_Fn, N_Apply::E_Type::FN>
		static constexpr auto Apply(T_Fn&& fn,request::pointer* p,T_Args&&... args)
		{
			N_Apply::S_Fn_Action fn_action(fn, p);
			return apply::Apply(&fn_action,std::forward<T_Args>(args)...);
		}
	};


}

