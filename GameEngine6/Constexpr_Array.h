#pragma once

#include<initializer_list>
#include<compare>
#include"Concept.h"
#include"Using_Type.h"
#include"Array_Capacity.h"

namespace N_Constexpr::N_Array
{

	//�d�l
	//[t_Size]���i���ŕ\�������́A�ŏ�ʂ̗����Ă�r�b�g��2�̉���ɂȂ邩�𒲂ׂ�
	//
	//template
	//t_Size::�ŏ�ʃr�b�g�𒲂ׂ�l
	//
	//����
	//two_index::�w���𒲂׎n�߂�ŏ��l
	//
	//�߂�l
	//�ŏ�ʂ̃r�b�g�̎w��
	template<size_t t_Size>
	constexpr size_t Get_Binary_Digit(size_t two_index = 1)
	{
		if (t_Size <= (static_cast<size_t>(1) << two_index))
		{
			return two_index - 1;
		}

		return Get_Binary_Digit<t_Size>(two_index + 1);
	}

	//�d�l
	//Acces�̃X�e�[�g�Ǘ�
	enum class E_AccesState
	{
		NORMAL,//�ʏ�
		END,//Data�ɃA�N�Z�X����
		NOT_Select_1//1�͑I��s��
	};

	//�d�l
	//Acces�̃X�e�[�g�Ǘ����s��
	// 
	//template
	//t_Size::�v�f�̍��v
	//t_Two_index::��i����2�̉���ɃA�N�Z�X���Ă��邩
	//t_SelectNum::���ݑI�����Ă��鐔��(�H���Ă��郋�[�g)
	//
	//�߂�l
	//���݂̃X�e�[�g
	template<size_t t_Size, short t_Two_index, size_t t_SelectNum>
		requires Fg<(t_Two_index >= 0)>
	constexpr E_AccesState Get_State()
	{
		if (t_Size <= (t_SelectNum | (1 << t_Two_index)))
		{
			return E_AccesState::NOT_Select_1;
		}
		return E_AccesState::NORMAL;
	}

	template<size_t t_Size, short t_Two_index, size_t t_SelectNum>
		requires Fg<(t_Two_index < 0)>
	constexpr E_AccesState Get_State()
	{
		return E_AccesState::END;

	}

	//�d�l
	//Constexpr_Array�̊e�v�f���i���Ŋi�[����
	//
	//template
	//T::�v�f�̌^
	//t_Size::�v�f�̍��v
	//t_Two_index::��i����2�̉���ɃA�N�Z�X���Ă��邩
	//t_SelectNum::���ݑI�����Ă��鐔��(�H���Ă��郋�[�g)
	//t_State::�A�N�Z�X�̏�ԊǗ�
	template<class T, size_t t_Size,
		short t_Two_index,
		size_t t_SelectNum = 0,
		E_AccesState t_State = Get_State<t_Size, t_Two_index, t_SelectNum>()>
	class Access
	{
	public:


		//�d�l
		//��i����[0]��I������
		Access<T, t_Size, t_Two_index - 1, t_SelectNum> _0;

		//�d�l
		//��i����[1]��I������
		Access< T, t_Size, t_Two_index - 1,( t_SelectNum | (size_t(1) << t_Two_index))> _1;

		//�d�l
		//�e�v�f�ɃA�N�Z�X����
		//
		//����
		//selectNum::�A�N�Z�X����v�f�̔ԍ�
		//
		//�߂�l
		//�A�N�Z�X�����v�f�̎Q��
		constexpr T& operator[](size_t selectNum)
		{
			if (selectNum < (1 << t_Two_index))
			{
				return _0.operator[](selectNum);
			}
			return _1.operator[](selectNum - (1 << t_Two_index));
		}
		
	};

	//�d�l
	//����[_1]��I������Ɨv�f���𒴂��Ă��܂��Ƃ��A[_1]��I��������O��
	template<class T, size_t t_Size, short t_Two_index, size_t t_SelectNum>
	class Access<T, t_Size, t_Two_index, t_SelectNum, E_AccesState::NOT_Select_1>
	{
	public:
		Access<T, t_Size, t_Two_index - 1, t_SelectNum> _0;

		constexpr T& operator[](size_t selectNum)
		{
			return _0.operator[](selectNum);
		}

	};

	//�d�l
	//�H���Ă������[�g�̃A�N�Z�X��f�[�^
	template<class T, size_t t_Size, short t_Two_index, size_t t_SelectNum>
	class Access<T, t_Size, t_Two_index, t_SelectNum, E_AccesState::END>
	{
	public:

		T Data = T();

		constexpr T& operator[](size_t selectNum)
		{
			return Data;
		}

	};


}

namespace N_Constexpr
{
	//�d�l
	//Constexpr_Array�̊e�v�f���i���Ŋi�[����
	//template
	//T::�v�f�̌^
	//t_Size::�v�f�̍��v
	template<class T, size_t t_Size>
	class Array
	{
	private:
		//�d�l
		//[u]��[t_Number]�Ɋi�[����
		//
		//template
		//t_Number::�ۑ�����v�f�ԍ�
		template<size_t t_Number, class U, class ...V>
		constexpr void Set(U u, V ...v);

		template<size_t t_Number, class U, size_t t_Array_Size, class ...V>
		constexpr void Set(Array<U, t_Array_Size> u, V ...v);


		template<size_t t_Number, class U, class ...V>
		constexpr void Set(invalid_t nullopt, V ...v) {}

	public:
		//�d�l
		//�f�[�^�̊i�[��ň��ڂ�[_0]��I������
		N_Array::Access<T, t_Size, N_Array::Get_Binary_Digit<t_Size>() - 1, 0> _0;

		//�d�l
		//�f�[�^�̊i�[��ň��ڂ�[_1]��I������
		N_Array::Access<T, t_Size, N_Array::Get_Binary_Digit<t_Size>() - 1, (1 << N_Array::Get_Binary_Digit<t_Size>())> _1;

		//�d�l
		//�e�v�f�ɃA�N�Z�X����
		//
		//����
		//selectNum::�A�N�Z�X����v�f�̔ԍ�
		//
		//�߂�l
		//�A�N�Z�X�����v�f�̎Q��
		constexpr T& operator[](size_t selectNum)
		{

			if (selectNum < (size_t(1) << N_Array::Get_Binary_Digit<t_Size>()))
			{
				return _0.operator[](selectNum);
			}
			return _1.operator[](selectNum - (size_t(1)<< N_Array::Get_Binary_Digit<t_Size>()));
		}


		template< class U, class ...V >
			requires N_Array::chack_C<T, t_Size, U, V...>
		constexpr Array(U u, V... v);

		constexpr Array() {}

		template<std::same_as<Array<T,t_Size>> T_2>
		constexpr bool operator==(T_2 t)
		{
			for (int i = 0; i < t_Size; i++)
			{
				if (this->operator[](i) != t[i])
				{
					return false;
				}
			}
			return true;
		}



	};

	template<class T>
	class Array<T, 1>
	{
	public:
		//�d�l
		//�f�[�^�̊i�[��ň��ڂ�[_0]��I������
		N_Array::Access<T, 1,static_cast<short>(N_Array::Get_Binary_Digit<1>() -1), 0> _0;

		constexpr T& operator[](size_t selectNum)
		{
			return _0.operator[](selectNum);
		}

	};

	template<class U, class ...V>
	Array(U, V...) -> Array<U, N_Array::Capacity<U, 0, U, V...>::Size>;


	template<class T, size_t t_Size>
	template<size_t t_Number, class U, class ...V>
	inline constexpr void Array<T, t_Size>::Set(U u, V ...v)
	{
		this->operator[](t_Number) = static_cast<T>(u);
		Set<t_Number + 1, V...>(v...);
	}

	template<class T,size_t t_Size>
	template<size_t t_Number, class U, size_t t_Array_Size, class ...V>
	inline constexpr void Array<T, t_Size>::Set(Array<U, t_Array_Size> u, V ...v)
	{
		int i = 0;
		for (i = 0; i < t_Array_Size; i++)
		{
			this->operator[](t_Number + i) = static_cast<T>(u[i]);
		}
		Set<t_Number + i, V...>(v...);
	}

	template<class T, size_t t_Size>
	template<class U, class ...V>
		requires N_Array::chack_C<T, t_Size, U, V...>
	inline constexpr Array<T, t_Size>::Array(U u, V ...v)
	{
		Set<0, U, V...>(u, v..., invalid);
	}

}

