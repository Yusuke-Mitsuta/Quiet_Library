#pragma once

#include"Tuple_Declare.h"

#include<iostream>
namespace std
{

	//�d�l
	//[S_Parameter<T>]���Ăяo����^���A�����o�[�֐���[get<I>]����`�����ꍇ�A
	// ���ꉻ��������\�ɂ���
	template<size_t I, class T>
		requires requires(T&& t)
	{
		requires is_invalid_not<typename quiet::N_Tuple::S_Parameter<T>::tuple>;
		requires !quiet::N_Tuple::is_Tuple<T>;
		requires quiet::N_Tuple::S_Parameter<T>::size >= I;
		{t.get<I>()};
	}
	static constexpr auto& get(T&& t)
	{
		return std::forward<T>(t).get<I>();
	}

	//�d�l
	//[S_Parameter<T>]���Ăяo����^���A�����o�[�֐���[get<I>]����`�����ꍇ�A
	// ���ꉻ��������\�ɂ���
	template<size_t I, class T>
		requires requires(const T&& t)
	{
		requires is_invalid_not<typename quiet::N_Tuple::S_Parameter<remove_const_t<T>>::tuple>;
		requires !quiet::N_Tuple::is_Tuple<remove_const_t<T>>;
		requires quiet::N_Tuple::S_Parameter<remove_const_t<T>>::size >= I;
		//{const_cast<T>(std::forward<const T>(t)).get<I>()};
	}
	static constexpr const auto get(const T& t)
	{
		return const_cast<T&>(t).get<I>();
	}

	template<size_t I, class T>
		requires requires(T t)
	{
		requires is_invalid_not<typename quiet::N_Tuple::S_Parameter<T>::tuple>;
		requires !quiet::N_Tuple::is_Tuple<T>;
		requires quiet::N_Tuple::S_Parameter<T>::size >= I;
		{t.get<I>()};
	}
	static constexpr auto& get(T* t)
	{
		return t->get<I>();
	}

	template<size_t I, class T>
		requires requires(const T* t)
	{
		requires is_invalid_not<typename quiet::N_Tuple::S_Parameter<T>::tuple>;
		requires !quiet::N_Tuple::is_Tuple<T>;
		requires quiet::N_Tuple::S_Parameter<T>::size >= I;
		{const_cast<T*>(t)->get<I>()};
	}
	static constexpr const auto& get(const T* t)
	{
		return const_cast<T*>(t)->get<I>();
	}


	//�d�l
	//[S_Parameter<T>]���Ăяo����^���A�����o�[�֐���[get<I>]����`�����ꍇ�A
	// �Ŕ͈͊O���w�肵�Ă���ꍇ�A�����l��Ԃ��B
	template<size_t I, class T>
		requires requires(T t)
	{
		requires is_invalid_not<typename quiet::N_Tuple::S_Parameter<T>::tuple>;
		requires !quiet::N_Tuple::is_Tuple<T>;
		requires quiet::N_Tuple::S_Parameter<T>::size < I;
	}
	auto get(T t)
	{
		try
		{
			throw std::runtime_error("");
		}
		catch (std::exception& e) {
			std::cout <<
				"[" << Type_id_delete_head_class_struct(typeid(T).name()) << "::get<"<< I<<">() ]�͈͊O�̗v�f�ւ̃A�N�Z�X�����{"
				<< std::endl;
			e.what();
		}

		return invalid;
	}

	template<class T>
	concept is_compatible_tuple = is_invalid_not<typename quiet::N_Tuple::S_Parameter<T>::tuple>;

}