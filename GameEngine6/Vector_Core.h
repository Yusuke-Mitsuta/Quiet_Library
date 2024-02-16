#pragma once

#include"Constexpr_Array.h"

#include"Vector_Storge.h"

namespace N_Vector
{

	//�d�l
	//Vector�̎����암��
	//
	//�⑫
	//�R���X�g���N�^�̈����ɑ΂��āA
	// [N_Tuple::Apply]��p���ēK�؂ɕϊ��̌��ʁA
	//	�v�f�����s�����Ă���ꍇ�A
	// �f�t�H���g�Ō^���\�z�\�ȏꍇ���A
	// �ÖٓI�ȕϊ��łȂ��ꍇ�͕s�������f�t�H���g�ō\�z����
	// 
	//	void Hoge(S_Core<int, 3>�@);
	//	
	//	void main()
	//	{
	//		Hoge(1); //�����[int]����[S_Core<int, 3>]�ɈÖٓI�ɕϊ�����Ă���ׁA�s�ƂȂ�
	//		Hoge(S_Core<int, 2>()); //�����[S_Core<int, 3>]����[S_Core<int, 3>]�ɈÖٓI�ɕϊ�����Ă���ׁA�s�ƂȂ�
	//		Hoge(S_Core<int, 3>(1)); ////�����[S_Core<int, 3>]�̃R���X�g���N�^��[int]�ŌĂяo���ׁA�ƂȂ�
	//	}
	template<class T,size_t t_vec>
	struct S_Core :
		S_Storge<T, t_vec>
	{
		using tuple = N_Tuple::U_Repeat_Multiple<T, t_vec>;


		//�d�l
		// [N_Tuple::Apply]��p���ēK�؂ɕϊ��̌��ʁA���������ꍇ
		template<size_t N = t_vec, class T = T, class ...Ts>
			requires requires
		{
			requires N_Array::args_size<T, Ts...> == N;
		}
		constexpr S_Core(Ts... ts) :
			S_Storge<T, t_vec>({N_Tuple::I_Apply_Action<Array<T, N>,Ts...>::Apply(ts...)}) {}

		//�d�l
		// [N_Tuple::Apply]��p���ēK�؂ɕϊ��̌��ʁA
		// �v�f���s�����Ă���ꍇ�́A�f�t�H���g�ō\�z���s��
		template<size_t N = t_vec,class T=T, class ...Ts>
			requires requires
		{
			requires !(N_Array::args_size<T, Ts...> < 1);
			requires !(N_Array::args_size<T, Ts...> >= N);
			T{};
		}
		explicit constexpr S_Core(Ts... ts) :
			S_Storge<T, t_vec>({ N_Tuple::I_Apply_Action<Array<T, N>,Ts...>::Apply(ts...) }) {}

		//�d�l
		//�������[���A���f�t�H���g�ō\�z�\�ȏꍇ
		template<size_t N = t_vec, class T = T>
			requires requires
		{
			T{};
		}
		explicit constexpr S_Core()
			:S_Storge<T, t_vec>({}) {}

		//�d�l
		//[I]�Ԗڂ̔z��̗v�f���Q�ƂŎ擾����
		template<size_t I>
		constexpr T& get();

		//�d�l
		//[i]�Ԗڂ̔z��̗v�f���Q�ƂŎ擾����
		constexpr T& operator[](const size_t& i);

		//�d�l
		//�P��̗v�f�Ŕz���S�Ė��ߐs����
		constexpr void operator=(const convertible_to<T> auto& copy);
	};

	template<class T, size_t t_vec>
	template<size_t I>
	inline constexpr T& S_Core<T, t_vec>::get()
	{
		return S_Storge<T, t_vec>::elems[I];
	}

	template<class T, size_t t_vec>
	inline constexpr T& S_Core<T, t_vec>::operator[](const size_t& i)
	{
		return S_Storge<T, t_vec>::elems[i];
	}
	template<class T, size_t t_vec>
	inline constexpr void S_Core<T, t_vec>::operator=(const convertible_to<T> auto& copy)
	{
		S_Storge<T, t_vec>::elems = copy;
	}
}
