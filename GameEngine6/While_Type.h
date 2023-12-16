#pragma once


//�d�l
//[T_Action::type]�̌��ʂ𔻒肵�A�����𖞂����Ȃ�A
// [T_Action]�̃e���v���[�g��[T_Action::type]���ʂƓ���ւ��A�ēx��������{����B
// �����𖞂����Ȃ��ꍇ�́A���ʂ��o�͂���
//
//�e���v���[�g
//[T_Action]::������[false]�ɂȂ�܂ŌJ��Ԃ��A�N�V����
//[T_is<...>]::�J��Ԃ������肷�����
//[T_is_Add_Types...]::[T_is<...>]�̔���ɒǉ��Őݒ肷��^
//
//�⑫
//[T_Action=T_Action_Outer< ... >]
// [T_is< T_Action::type , T_is_Add_Types...>::value]��[true]�ł���΁A
// [T_Action::type] �� [T_Action_Outer< T_Action::type >::type]�ɕύX���A�ēx������s��[false�ɂȂ�܂ő�����]
template<class T_Action, template<class...>class T_is, class ...T_is_Add_Types>
	requires requires
{
	typename T_is<typename T_Action::type, T_is_Add_Types...>::value;
}
struct while_type
{

	//�d�l
	//�J��Ԃ��̏I��
	template<class T_Action=T_Action,
		class T_Action_Type= typename T_Action::type,
		bool is_break_chack = T_is<T_Action_Type, T_Set_is_Types...>::value>
	struct S_While
	{
		using type = T_Action_Type;
	};

	//�d�l
	// [T_Action<T_Template_Types...>::type]�� [T_Action< T_Action<T_Template_Types...>::type >::type]�ɕύX���J��Ԃ�
	template<template<class...>class T_Action,
		class ...T_Template_Types,
		class T_Action_Type>
	struct S_While<T_Action<T_Template_Types...>,T_Action_Type,true>
	{
		using type = S_While<T_Action<T_Action_Type>>::type;
	};

	using type = S_While<>::type;

};


//�d�l
//[T_Action::type]�̌��ʂ𔻒肵�A�����𖞂����Ȃ�A
// [T_Action]�̃e���v���[�g��[T_Action::type]���ʂƓ���ւ��A�ēx��������{����B
// �����𖞂����Ȃ��ꍇ�́A���ʂ��o�͂���
//
//�e���v���[�g
//[T_Action]::������[false]�ɂȂ�܂ŌJ��Ԃ��A�N�V����
//[T_is<...>]::�J��Ԃ������肷�����
//[T_is_Add_Types...]::[T_is<...>]�̔���ɒǉ��Őݒ肷��^
//
//�⑫
//[T_Action=T_Action_Outer< ... >]
// [T_is< T_Action::type , T_is_Add_Types...>::value]��[true]�ł���΁A
// [T_Action::type] �� [T_Action_Outer< T_Action::type >::type]�ɕύX���A�ēx������s��[false�ɂȂ�܂ő�����]
template<class T_Action, template<class...>class T_is, class ...T_is_Add_Types>
	requires requires
{
	typename T_is<typename T_Action::type, T_is_Add_Types...>::value;
}
using while_type_t = typename while_type<T_Action, T_is, T_is_Add_Types...>::type;
