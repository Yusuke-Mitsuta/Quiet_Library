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
#include<optional>
#include <type_traits>

#include"Using_Type.h"

namespace N_Constexpr
{
	template<class T, Size_Type t_Size>
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
namespace N_Constexpr::N_Array
{
	template<class T, Size_Type t_Initial_Capacity, class U, class ...V>
	class Capacity
	{
	private:

		//�d�l
		//�\�z�\�����莞�̃X�e�[�g�Ǘ�������
		enum class E_State
		{
			T_CONVERTIBLE_U,
			ARRAY_DISASSEMBLY,
			END

		};

		//�d�l
		//[U,V...]�̎��A�X�e�[�g��I������
		template<class U, class ...V>
		static constexpr E_State GetState()
		{
			if (std::convertible_to<U, T>)
			{
				return E_State::T_CONVERTIBLE_U;
			}
			else if (requires{typename U::Array; })
			{
				return E_State::ARRAY_DISASSEMBLY;
			}

			return E_State::END;

		}

		template<Size_Type remaining_Capacity, E_State t_State, class U, class ...V>
		class Calcu;

		//�d�l
		//�^[U]��Array�Ɋi�[�Ȍ^�����肷��
		template<Size_Type remaining_Capacity, class U, class ...V>
		class Calcu<remaining_Capacity, E_State::T_CONVERTIBLE_U, U, V...>
		{
		public:
			using Type = Calcu<remaining_Capacity - 1, GetState<V...>(), V...>::Type;

		};

		//�d�l
		//�^[U]��Array�^���A�^[T]��Array�^�łȂ������肷��
		template<Size_Type remaining_Capacity, class Array_T, Size_Type t_ArraySize, class ...V>
		class Calcu<remaining_Capacity, E_State::ARRAY_DISASSEMBLY, N_Constexpr::Array<Array_T, t_ArraySize>, V...>
		{
		public:
			using Type = Calcu<remaining_Capacity - t_ArraySize, GetState<V...>(), V...>::Type;
		};

		//�d�l
		//Array�ɑ΂��āA[U,V...]�̗v�f�ō\�z���A�\�z�\���ǂ����̔���A�\�Ȃ�Ηv�f���̌v�Z���s��
		//
		//�⑫
		//[Array_Capacity::Type]������̌��ʁA�\�Ȃ�[std::true_type],�s�\�Ȃ�[std::false_type]�ɂȂ�
		template<Size_Type remaining_Capacity, E_State t_State, class U, class ...V>
		class Calcu
		{
		private:

			//�d�l
			//�v�f�����e�ʈȓ������肷��
			static constexpr bool Judge_Capacity()
			{
				if (remaining_Capacity >= 0)
				{
					return true;
				}

				return false;
			}
		public:

			//�d�l
			//[U,V...]�̗v�f�ō\�z�������̌v�Z���ʂɃA�N�Z�X��
			using Type = Calcu<remaining_Capacity, E_State::END, U, V...>;

			//�d�l
			//�N���X[Array]�̗v�f���̏���l�ɑ΂��āA�����ɂƂ�v�f�����K�������肵�����ʂ�Ԃ�
			//
			//�⑫
			//[Array_Capacity::Type]������̌��ʁA�\�Ȃ�[std::true_type],�s�\�Ȃ�[std::false_type]�ɂȂ�
			using Bool_Type = std::bool_constant<Judge_Capacity()>;

			//�d�l
			//�v�f����Ԃ�
			static constexpr Size_Type Size = t_Initial_Capacity - remaining_Capacity;
		};

		//�d�l
		//�N���X[Array]�̂ɑ΂��āA[U,V...]�̗v�f�ō\�z�������̌��ʂɃA�N�Z�X����
		using Type = Calcu<t_Initial_Capacity, GetState<U, V...>(), U, V..., invalid_t>::Type;

	public:

		//�d�l
		//�N���X[Array]�̗v�f���̏���l�ɑ΂��āA�����ɂƂ�v�f�����K�������肵�����ʂ�Ԃ�
		//
		//�⑫
		//[Array_Capacity::Type]������̌��ʁA�\�Ȃ�[std::true_type],�s�\�Ȃ�[std::false_type]�ɂȂ�
		using Bool_Type = Type::Bool_Type;

		//�d�l
		//�v�f����Ԃ�
		static constexpr Size_Type Size = Type::Size;

	};
};