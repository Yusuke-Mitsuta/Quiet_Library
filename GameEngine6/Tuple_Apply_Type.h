#pragma once


#include"Tuple_Declare.h"

template<is_invalid_not T_Front_Parts, class ...T_Parts>
class Function;

template<class _Ty1, size_t N>
class Array;

namespace N_Tuple::N_Apply
{
	enum class E_Type
	{
		NONE,
		FN,
		ARRAY,
		CLASS,
		CLASS_NEW,
	};

	//�d�l
	//Apply�̓���^�C�v���^[T]���画�肷��
	template<class T>
	struct S_Select_Type :
		integral_constant<E_Type::NONE>
	{};

	//�d�l
	//Apply���N���X�^[T]�̐��������{����B
	template<class T>
		requires requires
	{
		requires is_class<T>;
	}
	struct S_Select_Type<T> :
		integral_constant<E_Type::CLASS>
	{};

	//�d�l
	//Apply���N���X�^[T]��New���������{����B
	template<is_class T>
	struct S_Select_Type<T*> :
		integral_constant<E_Type::CLASS_NEW>
	{};

	template<class T>
	struct S_Select_Type<T&> :
		S_Select_Type<T>
	{};


	//�d�l
	//Apply���z��[ T[N] ]�ɗv�f���i�[����B
	template<class T, size_t N>
	struct S_Select_Type<T[N]> :
		integral_constant<E_Type::ARRAY>
	{};

	//�d�l
	//Apply���֐��^[T]�����s����
	template<class T>
		requires requires
	{
		requires is_function_pointer<T>;
	}
	struct S_Select_Type<T> :
		integral_constant<E_Type::FN>
	{};

	//�d�l
	//Apply���֐��I�u�W�F�N�g[T]�����s����
	template<class ...T_Parts>
	struct S_Select_Type<Function<T_Parts...>> :
		integral_constant<E_Type::FN>
	{};

	template<class T>
	static constexpr E_Type Select_Type_v = S_Select_Type<T>::value;

	template<class T, E_Type t_type>
	concept is_apply_type = (t_type == S_Select_Type<T>::value);
}
