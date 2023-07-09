#pragma once
#include"Function_BindFn.h"
#include"tuple_convertible_to.h"
#include"Tuple_Unzip.h"
#include<tuple>
#include<optional>

namespace N_Function
{
	//仕様
	//関数ポインターに対して、引数の値が正しいか、後方一致で判定する
	//
	//テンプレート
	//T_Fn_Args::関数ポインター、指定する引数、のTuple
	//
	//補足
	//T_Fn_Argsは関数ポインター、それに指定する引数、次の関数ポインター、となるようにする事
	template<class T_Fn_Args>
	struct IS_BindArgs
	{
		friend class IS_BindArgs;
	private:

		template<int _Index>
		using tuple_element = std::tuple_element<(std::tuple_size<T_Fn_Args>::value + _Index) % std::tuple_size<T_Fn_Args>::value, T_Fn_Args>::type;

		//仕様
		//引数のバインド済み関数ポインターを格納し、最後の関数なら格納処理を終了する
		//
		//テンプレート
		//t_MethodNumber::現在格納した関数の番号
		//t_RemainingAmount::残りのT_Fn_Argsの数
		//...T_Bounds::引数のバインド済み関数ポインター
		//補足
		//T_Fn_Argsを後ろから確認し、既にバインド済み関数の前に格納してゆく
		template<int t_MethodNumber,int t_RemainingAmount = t_MethodNumber,class ...T_Bounds>
		struct S_BoundArgs
		{
			template<class T_Args, int t_NextNumber, class ...T_NewSetArgs>
			struct S_BindArgs
			{
				using Type = S_BindArgs<tuple_element<t_NextNumber - 1>, t_NextNumber - 1, T_Args, T_NewSetArgs...>::Type;

				static auto Bind(T_Fn_Args&& t_Fn_Args)
				{
					C_OUT("TEST");
					return 0;
				}
			};

			//仕様
			//関数ポインターに対して引数をセットする
			template<class C_Name, class R_Type, class ...T_Args, int t_NextNumber, class ...T_NewSetArgs>
			struct S_BindArgs<R_Type(C_Name::*)(T_Args...), t_NextNumber, T_NewSetArgs...>
			{
				//仕様
				//引数が後方一致するか判定する
				static constexpr bool Judge = tuple_back_part_convertible_to<std::tuple<T_NewSetArgs...>, std::tuple<T_Args...>>;

				//仕様
				//引数が後方一致しない、若しくは最後の関数なら格納を終了に移行する
				//一致するなら、格納を継続する
				using Type = S_BoundArgs<t_NextNumber*Judge, t_NextNumber,S_Address<R_Type(C_Name::*)(T_Args...), std::tuple<T_NewSetArgs...>>,T_Bounds...>::Type;
			};

			//仕様
			//S_Addressに対して引数をセットする
			template<class C_Name, class R_Type, class ...T_Args, class ...T_DefaultSetArgs, int t_NextNumber, class ...T_NewSetArgs>
			struct S_BindArgs<S_Address<R_Type(C_Name::*)(T_Args...), std::tuple<T_DefaultSetArgs...>>, t_NextNumber, T_NewSetArgs...>
			{	
				//仕様
				//引数が後方一致するか判定する
				static constexpr bool Judge = tuple_back_part_convertible_to<std::tuple<T_NewSetArgs..., T_DefaultSetArgs...>, std::tuple<T_Args...>>;

				//仕様
				//引数が後方一致しない、若しくは最後の関数なら格納を終了に移行する
				//一致するなら、格納を継続する
				using Type = S_BoundArgs<t_NextNumber*Judge,t_NextNumber,S_Address<R_Type(C_Name::*)(T_Args...), std::tuple<T_NewSetArgs...,T_DefaultSetArgs...>>, T_Bounds...>::Type;
			};


		public:
			//仕様
			//引数を集め、関数ポインターに格納する
			using Type = S_BindArgs<tuple_element<t_MethodNumber - 1>, t_MethodNumber - 1>::Type;


			static auto Bind(T_Fn_Args&& t_Fn_Args)
			{
				C_OUT("TEST");
				return 0;
			}


		};

	public:

		//仕様
		//格納の結果を示す
		template<int t_RemainingAmount ,class ...T_Bounds>
		struct S_BoundArgs<0,t_RemainingAmount,T_Bounds...>
		{
			using Type = S_BoundArgs;

			//仕様
			//格納されたS_Addressのtupleを返す
			using Fns = std::tuple<T_Bounds...>;

			//仕様
			//Fnsが正常に格納されたかを返す
			using Judge = std::bool_constant<!(t_RemainingAmount)>;
		};

		using BoundArgs = S_BoundArgs<std::tuple_size<T_Fn_Args>::value>;

		//仕様
		//関数ポインターに対して、引数の値が正しいか、後方一致で判定する
		using Type = BoundArgs::Type;

		//T_Fn_Args fns;

		template<class MT_Fn_Args>
		constexpr IS_BindArgs(MT_Fn_Args& t_Fn_Args)
		{
			auto a= IS_BindArgs<MT_Fn_Args>::S_BoundArgs<std::tuple_size<MT_Fn_Args>::value>::Bind(std::forward<MT_Fn_Args>(t_Fn_Args));
		}
	};

	template<class MT_Fn_Args>
	IS_BindArgs(MT_Fn_Args& t_Fn_Args) -> IS_BindArgs<typename IS_BindArgs<typename IS_TupleUnzip<MT_Fn_Args>::Type>::Type::Fns>;
	


}