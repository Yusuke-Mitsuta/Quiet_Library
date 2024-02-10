#pragma once

#include"Tuple_Declare.h"
#include"SwapType.h"

namespace N_Tuple
{
	//�d�l
	//[T_Tuple]��[t_Point_1]��[t_Point_2]�̊Ԃ̗v�f���擾����
	//[t_Point2]���ݒ肳��Ȃ��ꍇ�A���݂̑I���ʒu���w�肷��
	template<class T_Tuple,size_t t_Point_1, size_t t_Point_2= S_Parameter<T_Tuple>::head_size>
	struct I_Range
	{
	private:

		using Swap_v = U_Swap_v<t_Point_1, t_Point_2, (t_Point_2 < t_Point_1)>;

		static constexpr int min = Swap_v::_1;
		static constexpr int max = Swap_v::_2;

		template<class T_Base, int t_Count = 0, class T_Center = tuple_t<>>
		struct S_Range
		{
			using type = T_Base;
		};

		//�d�l
		//[t_Swap_Num_1]�Ԗڂ�[t_Swap_Num_2]�Ԗڂ������l���w���Ƃ�
		template<class ...T_Types, int t_Count>
			requires (min == max)
		struct S_Range< tuple_t<T_Types...>, t_Count,tuple_t<>>
		{
			using type = tuple_t<>;
		};

		//�d�l
		//[mix]�̒l�ɂȂ�܂ŃJ�E���g��i�߂�
		template<class T_Next_Type, class ...T_Types, int t_Count>
			requires (min > t_Count) && (min != max)
		struct S_Range<tuple_t<T_Next_Type, T_Types...>, t_Count , tuple_t<>>
		{
			using type =typename S_Range<tuple_t<T_Types...>, t_Count + 1>::type;
		};

		//�d�l
		//[mix]~[max]�̏ꍇ�l�𔲂��o��
		template< class T_Next_Type, class ...T_Types, int t_Count,  class ...T_Center_Types>
			requires (min <= t_Count) && (max > t_Count) && (min != max)
		struct S_Range<tuple_t<T_Next_Type, T_Types...>, t_Count
			, tuple_t<T_Center_Types...>>
		{
			using type = typename S_Range<tuple_t<T_Types...>, t_Count + 1, tuple_t<T_Center_Types..., T_Next_Type>>::type;
		};

		template< class ...T_Types, int t_Count, class ...T_Center_Types>
			requires (max <= t_Count) && (min != max)
		struct S_Range<tuple_t<T_Types...>, t_Count
			,tuple_t<T_Center_Types...>>
		{
			using type = tuple_t<T_Center_Types...>;
		};

		template<class T_Tuple>
		struct S_Action
		{
			using type = 
				S_Range<T_Tuple>::type;
		};

	public:

		using type = S_Tuple_t_Change_Action<S_Action, T_Tuple>::Return_not_p;
	};

}