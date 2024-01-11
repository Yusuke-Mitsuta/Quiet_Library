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

	//�d�l
	//[S_Parameter<T>]���Ăяo����^���A�����o�[�֐���[get<I>]����`�����ꍇ�A
	// �Ŕ͈͊O���w�肵�Ă���ꍇ�A�����l��Ԃ��B
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
				"[" << Type_id_delete_head_class_struct(typeid(T).name()) << "::get<N>() ]�͈͊O�̗v�f�ւ̃A�N�Z�X�����{"
				<< std::endl;
		}

		return invalid;
	}


}