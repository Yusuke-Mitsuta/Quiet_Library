#pragma once

#include"Tuple_Declare.h"

#include<iostream>
namespace std
{

	//仕様
	//[S_Parameter<T>]が呼び出せる型かつ、メンバー関数に[get<I>]が定義される場合、
	// 特殊化し動作を可能にする
	template<size_t I, class T>
		requires requires(T&& t)
	{
		requires is_invalid_not<typename N_Tuple::S_Parameter<T>::tuple>;
		requires !N_Tuple::is_Tuple<T>;
		requires N_Tuple::S_Parameter<T>::size >= I;
		{t.get<I>()};
	}
	auto& get(T&& t)
	{
		return std::forward<T>(t).get<I>();
	}

	template<size_t I, class T>
		requires requires(T t)
	{
		requires is_invalid_not<typename N_Tuple::S_Parameter<T>::tuple>;
		requires !N_Tuple::is_Tuple<T>;
		requires N_Tuple::S_Parameter<T>::size >= I;
		{t.get<I>()};
	}
	auto* get(T* t)
	{
		return &t->get<I>();
	}

	//仕様
	//[S_Parameter<T>]が呼び出せる型かつ、メンバー関数に[get<I>]が定義される場合、
	// で範囲外を指定している場合、無効値を返す。
	template<size_t I, class T>
		requires requires(T t)
	{
		requires is_invalid_not<typename N_Tuple::S_Parameter<T>::tuple>;
		requires !N_Tuple::is_Tuple<T>;
		requires N_Tuple::S_Parameter<T>::size < I;
	}
	auto get(T t)
	{
		try
		{
			throw std::runtime_error("");
		}
		catch (std::exception& e) {
			std::cout <<
				"[" << Type_id_delete_head_class_struct(typeid(T).name()) << "::get<N>() ]範囲外の要素へのアクセスを実施"
				<< std::endl;
		}

		return invalid;
	}


}