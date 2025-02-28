/*!
 * Tuple_Get.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Tuple_Declare.h"

#include<iostream>

namespace quiet::N_Tuple
{
	template<size_t I, class T>
	concept is_std_get_chack = requires(T t)
	{
		requires is_invalid_not<typename S_Parameter<T>::tuple>;
		requires !is_Tuple<T>;
		requires S_Parameter<T>::size >= I;
	};
}

/*
namespace std
{

	//仕様
	//[S_Parameter<T_Request_Order>]が呼び出せる型かつ、メンバー関数に[get<I>]が定義される場合、
	// 特殊化し動作を可能にする
	template<size_t I, class T_Request_Order>
		requires requires(T_Request_Order&& t)
	{
		requires quiet::N_Tuple::is_std_get_chack<I, T_Request_Order>;
		{t.get<I>()};
	}
	static constexpr auto& get(T_Request_Order&& t)
	{
		return std::forward<T_Request_Order>(t).get<I>();
	}

	//仕様
	//[S_Parameter<T_Request_Order>]が呼び出せる型かつ、メンバー関数に[get<I>]が定義される場合、
	// 特殊化し動作を可能にする
	template<size_t I, class T_Request_Order>
		requires requires(const T_Request_Order& t)
	{
		requires quiet::N_Tuple::is_std_get_chack<I, remove_const_t<T_Request_Order>>;
		{const_cast<T_Request_Order&>(t).get<I>()};
	}
	static constexpr const auto get(const T_Request_Order& t)
	{
		return const_cast<T_Request_Order&>(t).get<I>();
	}

	template<size_t I, class T_Request_Order>
		requires requires(T_Request_Order* t)
	{
		requires quiet::N_Tuple::is_std_get_chack<I,T_Request_Order>;
		{t->get<I>()};
	}
	static constexpr auto& get(T_Request_Order* t)
	{
		return t->get<I>();
	}

	template<size_t I, class T_Request_Order>
		requires requires(const T_Request_Order* t)
	{
		requires quiet::N_Tuple::is_std_get_chack<I, remove_const_t<T_Request_Order>>;
		{const_cast<T_Request_Order*>(t)->get<I>()};
	}
	static constexpr const auto& get(const T_Request_Order* t)
	{
		return const_cast<T_Request_Order*>(t)->get<I>();
	}


	//仕様
	//[S_Parameter<T_Request_Order>]が呼び出せる型かつ、メンバー関数に[get<I>]が定義される場合、
	// で範囲外を指定している場合、無効値を返す。
	template<size_t I, class T_Request_Order>
		requires requires(T_Request_Order t)
	{
		requires quiet::is_invalid_not<typename quiet::N_Tuple::S_Parameter<T_Request_Order>::tuple>;
		requires !quiet::N_Tuple::is_Tuple<T_Request_Order>;
		requires quiet::N_Tuple::S_Parameter<T_Request_Order>::size < I;
	}
	auto get(T_Request_Order t)
	{
		try
		{
			throw std::runtime_error("");
		}
		catch (std::exception& e) {
			std::cout <<
				"[" << Type_id_delete_head_class_struct(typeid(T_Request_Order).name()) << "::get<"<< I<<">() ]範囲外の要素へのアクセスを実施"
				<< std::endl;
			e.what();
		}

		return quiet::invalid;
	}

	template<class T_Request_Order>
	concept is_compatible_tuple = quiet::is_invalid_not<typename quiet::N_Tuple::S_Parameter<T_Request_Order>::tuple>;

}

*/