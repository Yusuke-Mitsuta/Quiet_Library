#pragma once

//仕様
//無効値の型を示す
struct invalid_t
{
	constexpr invalid_t() {}

	using type = invalid_t;

};

//仕様
//無効値を示す
inline constexpr invalid_t invalid = invalid_t{};


//仕様
//[T_Main::type]を実行し、結果が無効値[invalid_t]なら
// [T_alternative...]の先頭の[::type]を実行する、以後繰り返す
// 
//テンプレート
//[T_Main]::[T_Main::type]を実行する
//[T_alternative...]::[T_Main::type]が無効値[invalid_t]なら実施する型
template<class T_Main,class ...T_alternative>
struct action_type
{
	template<class T_chack,class ...T_alternative>
	struct invalid_chack
	{
		using type = T_chack;
	};

	template<class T_next_alternative, class ...T_alternative>
	struct invalid_chack<invalid_t,T_next_alternative,T_alternative...>
	{
		using type = invalid_chack<typename T_next_alternative::type,T_alternative...>::type;
	};

	//template<convertible_to<int> T>
	//constexpr operator T()
	//{
	//	return 0;
	//}

	using type = invalid_chack<typename T_Main::type, T_alternative...>::type;

};

//仕様
//[T_Main::type]を実行し、結果が無効値[invalid_t]なら
// [T_alternative...]の先頭の[::type]を実行する、以後繰り返す
// 
//テンプレート
//[T_Main]::[T_Main::type]を実行する
//[T_alternative...]::[T_Main::type]が無効値[invalid_t]なら実施する型
template<class T_Main, class ...T_alternative>
using type_t = typename action_type<T_Main, T_alternative...>::type;
