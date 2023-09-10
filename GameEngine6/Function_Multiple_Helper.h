#pragma once

#include"Parameter.h"
#include"SwapType.h"
#include"Function_Single_Data.h"


namespace N_Function
{

	template<class ...T_Fn_Parts>
	struct S_Function_Single_Data;

	//仕様
	//関数ポインターに対して、引数の値が正しいか、後方一致で判定する
	//
	//テンプレート
	//TP_Fns::関数ポインター、指定する引数、のTuple
	//
	//補足
	//T_Fn_Argsは関数ポインター、それに指定する引数、次の関数ポインター、となるようにする事
	// //SetJudge::関数に対して、「後ろに続く引数の型、関数にバインド済みの引数の型」が関数に対する引数の型の後方部分と互換性があるか判定する
	//Fns::関数ポインターor[Function_Single]と、後ろに続く引数の型を[Function_Single]としてまとめ、その動作を[TP_Fns...]がなくなるまで繰り返す
	template<class T_FlontFn, class ...TP_Fns>
	struct IS_Function_Multiple_Helper
	{
	private:


		using Parameter = S_Parameter<T_FlontFn, TP_Fns...>;

		template<int _Index>
		using Element_t = U_Element_t< (Parameter::Size * 2 - _Index) % Parameter::Size, Parameter>;

		//仕様
		//関数に対して、「後ろに続く引数の型、関数にバインド済みの引数の型」が関数に対する引数の型の後方部分と互換性があるか判定し、互換性があれば[Function_Single]にまとめる
		//
		//テンプレート
		//t_SearchNumber::現在の探査中の要素番号
		//...TP_BoundFns::[Function_Single]でまとめた型
		template<int t_Search_Number = 1, class TP_BoundFns = S_Parameter<>,
			bool t_Pointer_Judge_Fg=true,
			bool t_Loop_Fg = static_cast<bool>(t_Search_Number % (Parameter::Size + 1))>
		struct S_CorrectType;

		template<int t_Search_Number, bool t_Pointer_Judge_Fg, class ...TP_BoundFns>
		struct S_CorrectType<t_Search_Number, S_Parameter<TP_BoundFns...>, t_Pointer_Judge_Fg, true>
		{

			//仕様
			//[Element<t_Pointer_Number>]が[Element<t_Method_Number>]と互換性があるか判定する
			//
			//条件
			//1:[Element<t_Pointer_Number>]がポインターである
			//2:[Element<t_Method_Number>]がメンバー関数ポインターである
			//3:[Element<t_Pointer_Number>]で[Element<t_Method_Number>]が呼び出せる事
			template<int t_Pointer_Number, int t_Method_Number>
			static constexpr bool p_Judge = is_pointer<Element_t<t_Pointer_Number>>
				&& convertible_to<std::remove_pointer_t<Element_t<t_Pointer_Number>>, typename S_Function_Single_Data<Element_t<t_Method_Number>>::CName>
				&& (!static_cast<bool>(S_Function_Single_Data<Element_t<t_Method_Number>>::Lelve));


			//仕様
			//関数ポインターに対して引数をセットする
			template<int t_TP_Number = t_Search_Number, class TP_ArgsNumbers = S_Parameter_Value<>, bool t_Create_Fg =
				not_same_as<typename S_Function_Single_Data<Element_t<t_TP_Number>>::Method, std::nullopt_t>>
				struct S_Function_Single_Create;

			template<int t_TP_Number, int ...tP_ArgsNumbers>
			struct S_Function_Single_Create<t_TP_Number, S_Parameter_Value<tP_ArgsNumbers...>, false>
			{
				//仕様
				//関数ポインターに対して引数をセットする
				using Type = S_Function_Single_Create<t_TP_Number + 1, S_Parameter_Value<t_TP_Number, tP_ArgsNumbers...>>::Type;
				using Type2 = S_Function_Single_Create<t_TP_Number + 1, S_Parameter_Value<t_TP_Number, tP_ArgsNumbers...>>;
			};

			template<int t_Method_Number, int ...tP_ArgsNumbers>
			struct S_Function_Single_Create<t_Method_Number, S_Parameter_Value<tP_ArgsNumbers...>, true>
			{
				using MethodData = N_Function::S_Function_Single_Data<Element_t<t_Method_Number>>;

				static constexpr bool judge_Pointer=
					p_Judge<t_Method_Number + 1, t_Method_Number> ||
					p_Judge<Parameter::Size, t_Method_Number> ||
					static_cast<bool>(MethodData::Lelve) ||
					same_as<typename MethodData::CName, std::nullopt_t>;

				//仕様
				//先頭の共通のポインターを、先頭の要素が使用しない場合判定をスキップする為のフラグ
				static constexpr bool first_Element_Not_Pointer = is_pointer<Element_t<t_Method_Number + 1>> && static_cast<bool>(MethodData::Lelve) && (t_Method_Number == Parameter::Size - 1);

				template<bool t_Point_Set_Fg>
				struct S_Judge_Return_Type
				{
					using Pointer_Type = U_Swap_t1<Element_t<Parameter::Size>, Element_t<t_Method_Number + 1>, p_Judge<t_Method_Number + 1, t_Method_Number>>;
					using Type = S_Function_Single_Data<Pointer_Type,Element_t<t_Method_Number>,Element_t<tP_ArgsNumbers>...>;
				};

				template<>
				struct S_Judge_Return_Type<false>
				{
					using Type = S_Function_Single_Data<Element_t<t_Method_Number>, Element_t<tP_ArgsNumbers>...>;
				};

				using Return = typename S_Judge_Return_Type<p_Judge<t_Method_Number + 1, t_Method_Number> ||
					p_Judge<Parameter::Size, t_Method_Number>>::Type;

				static constexpr bool judge = not_is_nullopt<typename Return::Method> && (judge_Pointer || !t_Pointer_Judge_Fg);

				//仕様
				//引数を精査し、ラッピングする
				using Type = S_CorrectType<(t_Method_Number + 1 +
					(p_Judge<t_Method_Number + 1, t_Method_Number> || first_Element_Not_Pointer))* judge,
					S_Parameter<Return, TP_BoundFns...>>::Type;
				using Type3 = S_CorrectType<(t_Method_Number + 1 +
					(p_Judge<t_Method_Number + 1, t_Method_Number> || first_Element_Not_Pointer))* judge,
					S_Parameter<Return, TP_BoundFns...>>;

			};

			using Type = S_Function_Single_Create<>::Type;
			using Type1 = S_Function_Single_Create<>;

		};

		//仕様
		//Functionに対してセットした引数の全てが成功した場合はその結果が、失敗すれば[std::nullopt_t]が返る
		template<int t_Search_Number, bool t_Pointer_Judge_Fg, class ...TP_BoundFns>
		struct S_CorrectType<t_Search_Number, S_Parameter<TP_BoundFns...>,t_Pointer_Judge_Fg,false>
		{
			using Type = S_CorrectType;

			using Judge = U_Judge_t<T_FlontFn, t_Search_Number>;

			using Fns = U_Judge_t<S_Parameter<TP_BoundFns...>, t_Search_Number>;
		};

	public:

		//仕様
		//全ての関数オブジェクトにおいて適切なクラスポインターがセットされているか判定する
		using Pointer_Judge = S_CorrectType<>::Type;

		//仕様
		//判定の項目からクラスポインターがセットされているかを除外する
		using Not_Pointer_Judge= S_CorrectType<1,S_Parameter<>,0>::Type;

		//using Fns = Type::Fns;

	};

}