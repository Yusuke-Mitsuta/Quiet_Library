#pragma once

//�d�l
//�����l�̌^������
struct invalid_t
{
	constexpr invalid_t() {}

	using type = invalid_t;

};

//�d�l
//�����l������
inline constexpr invalid_t invalid = invalid_t{};


//�d�l
//[T_Main::type]�����s���A���ʂ������l[invalid_t]�Ȃ�
// [T_alternative...]�̐擪��[::type]�����s����A�Ȍ�J��Ԃ�
// 
//�e���v���[�g
//[T_Main]::[T_Main::type]�����s����
//[T_alternative...]::[T_Main::type]�������l[invalid_t]�Ȃ���{����^
template<class T_Main,class ...T_alternative>
struct action_type
{
	template<class T_chack,class ...T_alternative>
	struct invalid_chack
	{
		using type = T_chack;
	};

	template<class T_next_alternative, class ...T_alternative>
	struct invalid_chack<invalid_t,T_next_alternative,T_alternative...>
	{
		using type = invalid_chack<typename T_next_alternative::type,T_alternative...>::type;
	};

	//template<convertible_to<int> T>
	//constexpr operator T()
	//{
	//	return 0;
	//}

	using type = invalid_chack<typename T_Main::type, T_alternative...>::type;

};

//�d�l
//[T_Main::type]�����s���A���ʂ������l[invalid_t]�Ȃ�
// [T_alternative...]�̐擪��[::type]�����s����A�Ȍ�J��Ԃ�
// 
//�e���v���[�g
//[T_Main]::[T_Main::type]�����s����
//[T_alternative...]::[T_Main::type]�������l[invalid_t]�Ȃ���{����^
template<class T_Main, class ...T_alternative>
using type_t = typename action_type<T_Main, T_alternative...>::type;
