#pragma once
#include"tuple_convertible_to.h"
#include"Tuple_Unzip.h"
#include"Parameter.h"
#include"SwapType.h"

#define FUNCTION_MULTIPLE(Variable,...)\
S_MoveTupleInnerType<FunctionMultiple,decltype(std::tuple(__VA_ARGS__))>::Type Variable = { __VA_ARGS__ };\

namespace N_Function
{

	template<class T_Method, class ...T_Args>
	struct S_MethodData;

	template<not_same_as<std::nullopt_t> T_Method, class ...TP_Args>
	class Function_Single;


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
		//[Element<t_Pointer_Number>]が[Element<t_Method_Number>]と互換性があるか判定する
		//
		//条件
		//1:[Element<t_Pointer_Number>]がポインターである
		//2:[Element<t_Method_Number>]がメンバー関数ポインターである
		//3:[Element<t_Pointer_Number>]で[Element<t_Method_Number>]が呼び出せる事
		template<int t_Pointer_Number, int t_Method_Number>
		static constexpr bool p_Judge = is_pointer<Element_t<t_Pointer_Number>> &&
			convertible_to<std::remove_pointer_t<Element_t<t_Pointer_Number>>, typename S_MethodData<Element_t<t_Method_Number>>::CName>&&
			same_as<typename S_MethodData<Element_t<t_Method_Number>>::Root, std::true_type>;


		//仕様
		//関数に対して、「後ろに続く引数の型、関数にバインド済みの引数の型」が関数に対する引数の型の後方部分と互換性があるか判定し、互換性があれば[Function_Single]にまとめる
		//
		//テンプレート
		//t_SearchNumber::現在の探査中の要素番号
		//...TP_BoundFns::[Function_Single]でまとめた型
		template<int t_Search_Number = 1, class TP_BoundFns= S_Parameter<>,
			bool t_Loop_Fg= static_cast<bool>(t_Search_Number % (Parameter::Size + 1))>
		struct S_CorrectType;

		template<int t_Search_Number , class ...TP_BoundFns>
		struct S_CorrectType<t_Search_Number, S_Parameter<TP_BoundFns...>,true>
		{
			//仕様
			//関数ポインターに対して引数をセットする
			template<int t_TP_Number=t_Search_Number, class TP_ArgsNumbers = S_Parameter_Value<>, bool t_Create_Fg =
				not_same_as<typename S_MethodData<Element_t<t_TP_Number>>::Method, std::nullopt_t>>
				struct S_Function_Single_Create;

			template<int t_TP_Number, int ...tP_ArgsNumbers>
			struct S_Function_Single_Create<t_TP_Number, S_Parameter_Value<tP_ArgsNumbers...>, false>
			{
				//仕様
				//関数ポインターに対して引数をセットする
				using Type = S_Function_Single_Create<t_TP_Number + 1, S_Parameter_Value<t_TP_Number, tP_ArgsNumbers...>>::Type;
			};

			template<int t_Method_Number, int ...tP_ArgsNumbers>
			struct S_Function_Single_Create<t_Method_Number, S_Parameter_Value<tP_ArgsNumbers...>, true>
			{
				using MethodData = N_Function::S_MethodData<Element_t<t_Method_Number>>;
				
				//仕様
				//引数が関数に対して、正しいか判定する
				//
				//条件
				//1:引数の型が後方一致する事
				//2_1:[Element<t_Method_Number>]がメンバー関数ポインター、かつ[Element<t_Method_Number+1>]がメンバー関数ポインターを呼び出せるクラス
				//2_2:共通のポインター[Element<Parameter::Size>]で[Element<t_Method_Number>]が呼び出せる事
				//2_3:既に構築済みの関数オブジェクトの場合
				//2_4:クラスに所属しないメソッドの場合
				static constexpr bool judge = tuple_back_part_convertible_to<typename IS_TupleUnzip<Element_t<tP_ArgsNumbers>..., typename MethodData::BoundArgs>::Type, typename MethodData::Args> && (
					p_Judge<t_Method_Number + 1, t_Method_Number> ||
					p_Judge<Parameter::Size, t_Method_Number> ||
					same_as<typename MethodData::Root, std::false_type> ||
					same_as<typename MethodData::CName, std::nullopt_t>);

				//仕様
				//先頭の共通のポインターを、先頭の要素が使用しない場合判定をスキップする為のフラグ
				static constexpr bool first_Element_Not_Pointer = is_pointer<Element_t<t_Method_Number + 1>> && same_as<typename MethodData::Root, std::false_type> && (t_Method_Number == Parameter::Size - 1);

				//仕様
				//引数を精査し、ラッピングする
				using Type = S_CorrectType<(t_Method_Number + 1 +
					(p_Judge<t_Method_Number + 1, t_Method_Number> || first_Element_Not_Pointer))* judge,
					S_Parameter<Function_Single<Element_t<t_Method_Number>, Element_t<tP_ArgsNumbers>...>, TP_BoundFns...>>::Type;
			};

			using Type = S_Function_Single_Create<>::Type;

		};

		//仕様
		//Functionに対してセットした引数の全てが成功した場合はその結果が、失敗すれば[std::nullopt_t]が返る
		template<int t_Search_Number , class ...TP_BoundFns>
		struct S_CorrectType<t_Search_Number, S_Parameter<TP_BoundFns...>,false>
		{
			using Type = S_CorrectType;

			using Judge = U_Judge_t<T_FlontFn, t_Search_Number>;

			using Fns = U_Judge_t<S_Parameter<TP_BoundFns...>, t_Search_Number>;
		};

	public:

		using Type = S_CorrectType<>::Type;

		using Judge = Type::Judge;

		using Fns = Type::Fns;

	};

}