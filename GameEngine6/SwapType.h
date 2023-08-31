#pragma once

#include<optional>
#include"Concept.h"

//仕様
//[T_1],[T_2]を[t_Order]によって入れ替える
//
//template
//T_1::タイプ1
//T_2::タイプ2
//t_Order::trueなら[T_1],[T_2]を入れ替える
template<class T_1, class T_2,long long t_Order>
struct IS_Swap_Type
{
	template<bool t_Order>
	struct S_SwapType
	{
		using Type = T_1;
	};

	template<>
	struct S_SwapType<true>
	{
		using Type = T_2;
	};

	using Type_1 = S_SwapType<static_cast<bool>(t_Order)>::Type;
	using Type_2 = S_SwapType<!static_cast<bool>(t_Order)>::Type;
};

//仕様
//[t_Order]が0なら[T_1],0以外なら[T_2]を返す
//
//template
//T_1::タイプ1
//T_2::タイプ2
//t_Order::trueなら[T_1],[T_2]を入れ替える
template<class T_1, class T_2, long long t_Order>
using U_Swap_t1 = typename IS_Swap_Type<T_1, T_2, t_Order>::Type_1;

//仕様
//[t_Order]が0なら[T_2],0以外なら[T_1]を返す
//
//template
//T_1::タイプ1
//T_2::タイプ2
//t_Order::trueなら[T_1],[T_2]を入れ替える
template<class T_1, class T_2, long long t_Order>
using U_Swap_t2 = typename IS_Swap_Type<T_1, T_2, t_Order>::Type_2;

//仕様
//[T],[std::nullopt_t]で[IS_Swap_Type]を作成する
//
//template
//T::タイプ
//t_Order::trueなら[Type1 = T],falseなら[Type1 = std::nullopt_t]
template<class T, long long t_Order>
using U_Judge = IS_Swap_Type<std::nullopt_t, T, t_Order>;

//仕様
//[t_Order]が0なら[std::nullopt_t],0以外なら[T]を返す
//
//template
//T::タイプ
//t_Order::フラグ
template<class T, long long t_Order>
using U_Judge_t = typename U_Judge<T, t_Order>::Type_1;

//仕様
//Judgeの判定にコンセプトを使用する
//
//template
//_Ty1::判定の結果trueなら[::Type_1 = _Ty1]
//_Ty2::_Ty1との判定に使用する型
//T_Concept::Conceptをクラス化型
// 
//補足
//[T_Concept]はテンプレートを二つ取り、定数[Concept]を持つ事
template<class _Ty1, class _Ty2, template<class...>class T_Concept>
	requires is_Concept<T_Concept>
using U_Judge_concept = U_Judge<_Ty1, T_Concept<_Ty1, _Ty2>::Concept>;

//仕様
//Judgeの判定に[T_Concept]を使用し、その結果がtrueなら[_Ty1],falseなら[std::nullopt_t]
//
//template
//_Ty1::判定の結果trueなら[::Type_1 = _Ty1]
//_Ty2::_Ty1との判定に使用する型
//T_Concept::Conceptをクラス化型
// 
//補足
//[T_Concept]はテンプレートを二つ取り、定数[Concept]を持つ事
template<class _Ty1, class _Ty2, template<class...>class T_Concept>
	requires is_Concept<T_Concept>
using U_Judge_concept_t = U_Judge_concept<_Ty1, _Ty2, T_Concept>::Type_1;

//仕様
//[same_as<_Ty1,_Ty2>]の結果がtrueなら[_Ty1],falseなら[std::nullopt_t]
//
//template
//_Ty1::判定の結果trueなら返るタイプ
//_Ty2::_Ty1との判定に使用する型
template <class _Ty1, class _Ty2>
using U_Judge_same_as_t = U_Judge_concept_t<_Ty1, _Ty2, same_as_S>;

//仕様
//[not_same_as<_Ty1,_Ty2>]の結果がtrueなら[_Ty1],falseなら[std::nullopt_t]
//
//template
//_Ty1::判定の結果trueなら返るタイプ
//_Ty2::_Ty1との判定に使用する型
template <class _Ty1, class _Ty2>
using U_Judge_not_same_as_t = U_Judge_concept_t<_Ty1, _Ty2, not_same_as_S>;

//仕様
//[convertible_to<_From, _To>]の結果がtrueなら[_From],falseなら[std::nullopt_t]
//
//template
//_From::判定の結果trueなら返るタイプ
//_To::_Fromとの判定に使用する型
template <class _From, class _To>
using U_Judge_convertible_to_t = U_Judge_concept_t<_From,_To, convertible_to_S>;

//仕様
//[not_convertible_to<_From, _To>]の結果がtrueなら[_From],falseなら[std::nullopt_t]
//
//template
//_From::判定の結果trueなら返るタイプ
//_To::_Fromとの判定に使用する型
template <class _From, class _To>
using U_Judge_not_convertible_to_t = U_Judge_concept_t<_From, _To, not_convertible_to_S>;

//仕様
//[t_1],[t_2]を[t_Order]によって入れ替える
//
//template
//T_1::変数１
//T_2::変数１
//t_Order::trueなら[T_1],[T_2]を入れ替える
template<auto t_1, auto t_2, int t_Order>
struct IS_Swap_Variable
{
	template<bool t_Order>
	struct S_SwapType
	{
		static constexpr auto Variable = t_1;
	};

	template<>
	struct S_SwapType<true>
	{
		static constexpr auto Variable = t_2;
	};

	static constexpr auto _1 = S_SwapType<static_cast<bool>(t_Order)>::Variable;
	static constexpr auto _2 = S_SwapType<!static_cast<bool>(t_Order)>::Variable;
};

template<auto t_1, auto t_2, int t_Order>
using U_Swap_v= IS_Swap_Variable<t_1, t_2, t_Order>;

template<auto t_1, auto t_2, int t_Order>
static constexpr auto U_Swap_v1 = IS_Swap_Variable<t_1, t_2, t_Order>::_1;

template<auto t_1, auto t_2, int t_Order>
static constexpr auto U_Swap_v2 = IS_Swap_Variable<t_1, t_2, t_Order>::_2;