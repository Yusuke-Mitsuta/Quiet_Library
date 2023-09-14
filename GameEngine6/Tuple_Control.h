#pragma once

#include<tuple>
#include<optional>

#include"Tuple_Declare.h"
#include"Tuple_Pointer.h"
#include"Tuple_Next.h"
#include"Tuple_Prev.h"
#include"Tuple_Remove.h"

namespace N_Tuple
{
	template<class ..._Types>
	struct _Control;

	//�d�l
	//[Tuple_t]�̑I���ʒu�̑���A�폜�̎��{�A�y�ь^�̎擾
	template<class ...T_Head_Types, class T, class ...T_Tail_Types>
	struct _Control<_Head<T_Head_Types...>, T, _Tail<T_Tail_Types...>>
	{
	private:

		using Change_Tuple = _p<_Head<T_Head_Types...>, T, _Tail<T_Tail_Types...>>;

	public:

		//�I�𒆂̗v�f���O�ɂ���v�f��
		static constexpr size_t Size_Head = sizeof...(T_Head_Types);

		//�I�𒆂̗v�f�����ɂ���v�f��
		static constexpr size_t Size_Tail = sizeof...(T_Tail_Types);

		//�v�f��
		static constexpr size_t Size = Size_Head + Size_Tail + 1;

		//���̗v�f��I������
		using Next = typename _Next<Change_Tuple>::Type;

		//�O�̗v�f��I������
		using Prev = typename _Prev<Change_Tuple>::Type;

		//�I�����Ă���v�f���폜����
		using Remove = typename _Remove<Change_Tuple>::Type;

		//�擪�̗v�f��I������
		using Flnot = typename Pointer<0, Change_Tuple>::Type;

		//�Ō�̗v�f��I������
		using Back = typename Pointer<Size-1, Change_Tuple>::Type;

		//�I�����Ă���v�f�̌^��Ԃ�
		using Type = T;

	};

	template<>
	struct _Control<_Head<>,_Tail<>>
	{
		static constexpr size_t Size = 0;
		static constexpr size_t Size_Head = 0;
		static constexpr size_t Size_Tail = 0;
		using Flnot= std::nullopt_t;
		using Back = std::nullopt_t;
		using Next = std::nullopt_t;
		using Prev = std::nullopt_t;
		using Flnot= std::nullopt_t;
		using Back = std::nullopt_t;
		using Remove = std::nullopt_t;
		using Select = std::nullopt_t;
		using Type = _p<>;
	};

}