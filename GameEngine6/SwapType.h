#pragma once

#include<optional>
#include"Concept.h"

//�d�l
//[T_1],[T_2]��[t_Order]�ɂ���ē���ւ���
//
//template
//T_1::�^�C�v1
//T_2::�^�C�v2
//t_Order::true�Ȃ�[T_1],[T_2]�����ւ���
template<class T_1, class T_2,long long t_Order>
struct IS_Swap_Type
{
	template<bool t_Order>
	struct S_SwapType
	{
		using Type = T_1;
	};

	template<>
	struct S_SwapType<true>
	{
		using Type = T_2;
	};

	using Type_1 = S_SwapType<static_cast<bool>(t_Order)>::Type;
	using Type_2 = S_SwapType<!static_cast<bool>(t_Order)>::Type;
};

//�d�l
//[t_Order]��0�Ȃ�[T_1],0�ȊO�Ȃ�[T_2]��Ԃ�
//
//template
//T_1::�^�C�v1
//T_2::�^�C�v2
//t_Order::true�Ȃ�[T_1],[T_2]�����ւ���
template<class T_1, class T_2, long long t_Order>
using U_Swap_t1 = typename IS_Swap_Type<T_1, T_2, t_Order>::Type_1;

//�d�l
//[t_Order]��0�Ȃ�[T_2],0�ȊO�Ȃ�[T_1]��Ԃ�
//
//template
//T_1::�^�C�v1
//T_2::�^�C�v2
//t_Order::true�Ȃ�[T_1],[T_2]�����ւ���
template<class T_1, class T_2, long long t_Order>
using U_Swap_t2 = typename IS_Swap_Type<T_1, T_2, t_Order>::Type_2;

//�d�l
//[T],[std::nullopt_t]��[IS_Swap_Type]���쐬����
//
//template
//T::�^�C�v
//t_Order::true�Ȃ�[Type1 = T],false�Ȃ�[Type1 = std::nullopt_t]
template<class T, long long t_Order>
using U_Judge = IS_Swap_Type<std::nullopt_t, T, t_Order>;

//�d�l
//[t_Order]��0�Ȃ�[std::nullopt_t],0�ȊO�Ȃ�[T]��Ԃ�
//
//template
//T::�^�C�v
//t_Order::�t���O
template<class T, long long t_Order>
using U_Judge_t = typename U_Judge<T, t_Order>::Type_1;

//�d�l
//Judge�̔���ɃR���Z�v�g���g�p����
//
//template
//_Ty1::����̌���true�Ȃ�[::Type_1 = _Ty1]
//_Ty2::_Ty1�Ƃ̔���Ɏg�p����^
//T_Concept::Concept���N���X���^
// 
//�⑫
//[T_Concept]�̓e���v���[�g�����A�萔[Concept]������
template<class _Ty1, class _Ty2, template<class...>class T_Concept>
	requires is_Concept<T_Concept>
using U_Judge_concept = U_Judge<_Ty1, T_Concept<_Ty1, _Ty2>::Concept>;

//�d�l
//Judge�̔����[T_Concept]���g�p���A���̌��ʂ�true�Ȃ�[_Ty1],false�Ȃ�[std::nullopt_t]
//
//template
//_Ty1::����̌���true�Ȃ�[::Type_1 = _Ty1]
//_Ty2::_Ty1�Ƃ̔���Ɏg�p����^
//T_Concept::Concept���N���X���^
// 
//�⑫
//[T_Concept]�̓e���v���[�g�����A�萔[Concept]������
template<class _Ty1, class _Ty2, template<class...>class T_Concept>
	requires is_Concept<T_Concept>
using U_Judge_concept_t = U_Judge_concept<_Ty1, _Ty2, T_Concept>::Type_1;

//�d�l
//[same_as<_Ty1,_Ty2>]�̌��ʂ�true�Ȃ�[_Ty1],false�Ȃ�[std::nullopt_t]
//
//template
//_Ty1::����̌���true�Ȃ�Ԃ�^�C�v
//_Ty2::_Ty1�Ƃ̔���Ɏg�p����^
template <class _Ty1, class _Ty2>
using U_Judge_same_as_t = U_Judge_concept_t<_Ty1, _Ty2, same_as_S>;

//�d�l
//[not_same_as<_Ty1,_Ty2>]�̌��ʂ�true�Ȃ�[_Ty1],false�Ȃ�[std::nullopt_t]
//
//template
//_Ty1::����̌���true�Ȃ�Ԃ�^�C�v
//_Ty2::_Ty1�Ƃ̔���Ɏg�p����^
template <class _Ty1, class _Ty2>
using U_Judge_not_same_as_t = U_Judge_concept_t<_Ty1, _Ty2, not_same_as_S>;

//�d�l
//[convertible_to<_From, _To>]�̌��ʂ�true�Ȃ�[_From],false�Ȃ�[std::nullopt_t]
//
//template
//_From::����̌���true�Ȃ�Ԃ�^�C�v
//_To::_From�Ƃ̔���Ɏg�p����^
template <class _From, class _To>
using U_Judge_convertible_to_t = U_Judge_concept_t<_From,_To, convertible_to_S>;

//�d�l
//[not_convertible_to<_From, _To>]�̌��ʂ�true�Ȃ�[_From],false�Ȃ�[std::nullopt_t]
//
//template
//_From::����̌���true�Ȃ�Ԃ�^�C�v
//_To::_From�Ƃ̔���Ɏg�p����^
template <class _From, class _To>
using U_Judge_not_convertible_to_t = U_Judge_concept_t<_From, _To, not_convertible_to_S>;

//�d�l
//[t_1],[t_2]��[t_Order]�ɂ���ē���ւ���
//
//template
//T_1::�ϐ��P
//T_2::�ϐ��P
//t_Order::true�Ȃ�[T_1],[T_2]�����ւ���
template<auto t_1, auto t_2, int t_Order>
struct IS_Swap_Variable
{
	template<bool t_Order>
	struct S_SwapType
	{
		static constexpr auto Variable = t_1;
	};

	template<>
	struct S_SwapType<true>
	{
		static constexpr auto Variable = t_2;
	};

	static constexpr auto _1 = S_SwapType<static_cast<bool>(t_Order)>::Variable;
	static constexpr auto _2 = S_SwapType<!static_cast<bool>(t_Order)>::Variable;
};

template<auto t_1, auto t_2, int t_Order>
using U_Swap_v= IS_Swap_Variable<t_1, t_2, t_Order>;

template<auto t_1, auto t_2, int t_Order>
static constexpr auto U_Swap_v1 = IS_Swap_Variable<t_1, t_2, t_Order>::_1;

template<auto t_1, auto t_2, int t_Order>
static constexpr auto U_Swap_v2 = IS_Swap_Variable<t_1, t_2, t_Order>::_2;