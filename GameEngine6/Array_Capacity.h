#pragma once

//�t�@�C����
//Array_Capacity.h
//
//�쐬��
//2023/03/01
//
//�����
//YUSUKE
//=================================================================

#include<concepts>
#include <type_traits>
#include<tuple>
//#include"Constexpr_Array.h"

namespace N_Constexpr
{

	template<class T, unsigned int t_Size>
	class Array;
};


	//�d�l
	//�N���X[Array]�̗v�f���̏���l�ɑ΂��āA�����ɂƂ�v�f�����K�������肷��
	//
	//�e���v���[�g
	//remaining_Capacity::�N���X[Array]�̗v�f��
	//T::Array�̊Ǘ�����^
	//U::�����̈�ڌ^
	//...V::������2�ڈȍ~�̌^
	//
	//�⑫
	//[Array_Capacity::Type]������̌��ʁA�\�Ȃ�[std::true_type],�s�\�Ȃ�[std::false_type]�ɂȂ�
	//�^T��Array�^�łȂ��A�����̌^��Array�^�̎��AArray����������A���ꂼ���̌^�Ƃ��Ċm�F����
template<class T,size_t remaining_Capacity, class U, class ...V>
class Array_Capacity
{
private:

	enum class State
	{
		T_CONVERTIBLE_U,
		ARRAY_DISASSEMBLY,
		ARRAY_DISASSEMBLY_END

	};

	template<class U,class ...V>
	State GetState()
	{
		if (std::convertible_to<U, T>)
		{
			return State::T_CONVERTIBLE_U;
		}
	}

	template<class Array_T,size_t t_ArraySize, class ...V>
	State GetState<N_Constexpr::Array<Array_T,t_ArraySize>,V...>()
	{
		if (std::convertible_to<N_Constexpr::Array<Array_T, t_ArraySize>,T>)
		{
			return State::T_CONVERTIBLE_U;
		}
		else if(t_ArraySize>1)
		{
			return State::ARRAY_DISASSEMBLY;
		}
		return State::ARRAY_DISASSEMBLY_END;
	}




	//�d�l
	//�^[U]��Array�Ɋi�[�Ȍ^�����肷��
	template<size_t remaining_Capacity, class U, class ...V,State t_State = GetState<U, V...>>
	class Capacity_Calcu
	{
	public:
		using Type = Capacity_Calcu<remaining_Capacity - 1,V...>::Type;
		
	};


	//�d�l
	//�^[U]��Array�Ɋi�[�Ȍ^�����肷��
	template<size_t remaining_Capacity, class U, class ...V>
	class Capacity_Calcu<remaining_Capacit,U,V...,State::ARRAY_DISASSEMBLY>
	{
	public:
		using Type = Capacity_Calcu<remaining_Capacity -, V...>::Type;

	};











public:

	//�d�l
	//�N���X[Array]�̗v�f���̏���l�ɑ΂��āA�����ɂƂ�v�f�����K�������肵�����ʂ�Ԃ�
	//
	//�⑫
	//[Array_Capacity::Type]������̌��ʁA�\�Ȃ�[std::true_type],�s�\�Ȃ�[std::false_type]�ɂȂ�
	using Type = Capacity_Calcu<T,remaining_Capacity, U, V...>::Type;

};
