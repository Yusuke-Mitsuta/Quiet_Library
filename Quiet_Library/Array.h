/*!
 * Array.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include<array>
#include"Tuple.h"
#include"Tuple_Repeat_Multiple.h"
#include"Array_deduction_guide.h"

namespace quiet::N_Tuple
{
	template<class T, size_t N>
	struct S_Parameter<std::array<T, N>> :
		S_Parameter<U_Repeat_Multiple<T, N>>
	{};

}

namespace quiet
{

	//�d�l
	//[_Ty1[t_array_size] elems]�̔z��𐶐����A�Ǘ�����
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
		public std::array<_Ty1, N>
	{
	public:

		using tuple = quiet::N_Tuple::U_Repeat_Multiple<_Ty1, N>;

		using std::array<_Ty1, N>::operator[];

		template<size_t t_array_size_limit = N, class T_Base = _Ty1, class ..._Ty2>
			requires requires
		{
			requires sizeof...(_Ty2) == t_array_size_limit;
			requires convertible_from_and<T_Base, _Ty2...>;
		}
		constexpr Array(_Ty2... t)
			:std::array<_Ty1, N>({ static_cast<_Ty1>(t)... })
		{}

		//�d�l
		// [N_Tuple::Apply]��p���ēK�؂ɕϊ��̌��ʁA���������ꍇ
		template<size_t t_array_size_limit = N, class T_Base = _Ty1, class ..._Ty2>
			requires requires
		{
			requires N_Array::args_size<T_Base, _Ty2...> == t_array_size_limit;
			requires convertible_from_nand<T_Base, _Ty2...>;
		}
		constexpr Array(_Ty2... t)
			:std::array<_Ty1, N>({ N_Tuple::I_Apply_Action<std::array<_Ty1, N>, _Ty2...>::Apply(t...) })
		{}


		//�d�l
		// [N_Tuple::Apply]��p���ēK�؂ɕϊ��̌��ʁA
		// �v�f���s�����Ă���ꍇ�́A�f�t�H���g�ō\�z���s��
		template<size_t t_array_size_limit = N, class T_Base = _Ty1, class ..._Ty2>
			requires requires
		{
			requires !(N_Array::args_size<T_Base, _Ty2...> <= 0);
			requires !(N_Array::args_size<T_Base, _Ty2...> >= t_array_size_limit);
			_Ty1{};
		}
		explicit constexpr Array(_Ty2 ...t)
			:std::array<_Ty1, N>({ N_Tuple::I_Apply_Action<std::array<_Ty1, N>, _Ty2...>::Apply(t...) })
		{}

		template<size_t t_array_size_limit = N, class T_Base = _Ty1>
			requires requires
		{
			T_Base{};
		}
		constexpr Array() :
			std::array<_Ty1, N>({})
		{}


		//�d�l
		//�P��̗v�f�Ŕz���S�Ė��ߐs����
		constexpr void operator=(const convertible_to<_Ty1> auto& copy);

	};

	template<class ..._Ty2>
		requires (static_cast<bool>(N_Array::I_deduction_guide<_Ty2...>::size))
	Array(_Ty2 ...ts)->
		Array<typename N_Array::I_deduction_guide<_Ty2...>::type, 
		N_Array::I_deduction_guide<_Ty2...>::size>;



	template<class _Ty1, size_t N>
	inline constexpr void Array<_Ty1, N>::operator=(const convertible_to<_Ty1> auto& copy)
	{
		std::array<_Ty1, N>::fill(static_cast<_Ty1>(copy));
	}
}
