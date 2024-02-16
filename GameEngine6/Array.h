#pragma once

#include<array>
#include"Tuple.h"
#include"Function_Args_Chack.h"

namespace N_Tuple
{
	template<class T, size_t N>
	struct S_Parameter<std::array<T, N>> :
		S_Parameter<U_Repeat_Multiple<T, N>>
	{};

	
}

namespace N_Array
{

	template<class T_Base_Type, class ...T_Args>
	static constexpr int args_size = 
		N_Tuple::N_Apply::I_Type_Chack<
		tuple_t<N_Tuple::N_Apply::S_Infinite_Args<T_Base_Type>>,
		tuple_t<T_Args...>>::value;

	template<class _Ty1,size_t N>
	struct S_Storge
	{
		std::array<_Ty1, N> elems;

		//�d�l
		// [N_Tuple::Apply]��p���ēK�؂ɕϊ��̌��ʁA���������ꍇ
		template<size_t N = N, class _Ty1=_Ty1, class ..._Ty2>
			requires requires
		{
			requires args_size<_Ty1, _Ty2...> == N;
		}
		constexpr S_Storge(_Ty2... t)
			:elems(N_Tuple::I_Apply_Action<std::array<_Ty1, N>, _Ty2...>::Apply
				(t...)) {}

		//�d�l
		// [N_Tuple::Apply]��p���ēK�؂ɕϊ��̌��ʁA
		// �v�f���s�����Ă���ꍇ�́A�f�t�H���g�ō\�z���s��
		template<size_t N = N, class _Ty1=_Ty1, class ..._Ty2>
			requires requires
		{
			requires !(args_size<_Ty1, _Ty2...> <= 0);
			requires !(args_size<_Ty1, _Ty2...> >= N);
			_Ty1{};
		}
		explicit constexpr S_Storge(_Ty2 ...t)
			: elems(N_Tuple::I_Apply_Action<std::array<_Ty1, N>, _Ty2...>::Apply
				(t...)) {}


		template<size_t N = N, class _Ty1 = _Ty1>
			requires requires
		{
			_Ty1{};
		}
		explicit constexpr S_Storge()
			:elems({}) {}


	};
}

//�d�l
//[_Ty1[N] elems]�̔z��𐶐����A�Ǘ�����
//
//�⑫
//�R���X�g���N�^�̈����ɑ΂��āA
// [N_Tuple::Apply]��p���ēK�؂ɕϊ��̌��ʁA
//	�v�f�����s�����Ă���ꍇ�A
// �f�t�H���g�Ō^���\�z�\�ȏꍇ���A
// �ÖٓI�ȕϊ��łȂ��ꍇ�͕s�������f�t�H���g�ō\�z����
// 
//	void Hoge(Array<int, 3>�@);
//	
//	void main()
//	{
//	�@Hoge(1); //�����[int]����[Array<int, 3>]�ɈÖٓI�ɕϊ�����Ă���ׁA�s�ƂȂ�
//	�@Hoge(Array<int, 2>()); //�����[Array<int, 3>]����[Array<int, 3>]�ɈÖٓI�ɕϊ���Ă���ׁA�s�ƂȂ�
//	�@Hoge(Array<int, 3>(1)); ///�����[Array<int, 3>]�̃R���X�g���N�^��[int]�ŌĂяo�ׁA�ƂȂ�
//	}
template<class _Ty1, size_t N>
class Array :
	public N_Array::S_Storge<_Ty1,N>
{
public:

	using tuple = N_Tuple::U_Repeat_Multiple<_Ty1, N>;

	using N_Array::S_Storge<_Ty1, N>::S_Storge;

	using N_Array::S_Storge<_Ty1, N>::elems;
	
	//�d�l
	//�z��̃|�C���^���擾����
	constexpr _Ty1* data();

	//�d�l
	//[I]�Ԗڂ̔z��̗v�f���Q�ƂŎ擾����
	template<size_t I>
	constexpr _Ty1& get();

	//�d�l
	//[i]�Ԗڂ̔z��̗v�f���Q�ƂŎ擾����
	constexpr auto& operator[](const size_t& i);

	//�d�l
	//�P��̗v�f�Ŕz���S�Ė��ߐs����
	constexpr void operator=(const convertible_to<_Ty1> auto& copy);
							
};

template<class _Ty2, class ..._Ty3>
	requires (N_Array::args_size<_Ty2, _Ty3...> >= 0)
Array(_Ty2 t, _Ty3 ...ts) -> Array<_Ty2,N_Array::args_size<_Ty2, _Ty2,_Ty3...>>;


template<class _Ty1, size_t N>
inline constexpr _Ty1* Array<_Ty1, N>::data()
{
	return elems.data();
}

template<class _Ty1, size_t N>
template<size_t I>
inline constexpr _Ty1& Array<_Ty1, N>::get()
{
	return elems[I];
}


template<class _Ty1, size_t N>
inline constexpr auto& Array<_Ty1, N>::operator[](const size_t& i)
{
	return elems[i];
}


template<class _Ty1, size_t N>
inline constexpr void Array<_Ty1, N>::operator=(const convertible_to<_Ty1> auto& copy)
{
	elems.fill(static_cast<_Ty1>(copy));
}