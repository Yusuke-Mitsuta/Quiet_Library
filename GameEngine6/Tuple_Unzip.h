#pragma once
#include<tuple>
#include"Concept.h"
#include"tuple_Helper.h"

//�d�l
//[...T_Tuple]���̑S�Ă�Tuple�𕪉����A1��Tuple�Ɋi�[����
//
//template
//...T_Tuple::���Tuple�Ɋi�[����^
//
//�⑫
//[using Type]�Ŋi�[����Tuple�̌^���擾����
//[Type tuple]�Ŋi�[����Tuple�̕ϐ����擾����
template<class ...T_Tuple>
struct IS_TupleUnzip
{
	template<int t_Number,class T_Flont_Type, class ...T_Tuple>
	struct S_TupleUnzip
	{
		using Type = S_TupleUnzip<t_Number+1,T_Tuple..., T_Flont_Type>::Type;

		//�d�l
		//[flont]�̒l��[set_Tuple]�Ɋi�[����
		//
		//����
		//set_Tuple::������̒l���i�[����Tuple
		//flont::�i�[����l
		//tuple::��ڈȍ~�̒l
		template<class MT_FlontType,class ...MT_Tuple>
		static constexpr void TupleUnzip(auto& set_Tuple, MT_FlontType& flont, MT_Tuple&... tuple)
		{
			std::get<t_Number>(set_Tuple) = flont;
			S_TupleUnzip<t_Number+1,T_Tuple..., T_Flont_Type>::TupleUnzip(set_Tuple,tuple...);
		}
	};

	template<int t_Number,class ...T_TupleInside, class ...T_Tuple>
	struct S_TupleUnzip<t_Number,std::tuple<T_TupleInside...>, T_Tuple...>
	{
	private:
		//�d�l
		//[flont_Tuple]�̒l�𕪉����A[set_Tuple]�Ɋi�[����
		//
		//����
		//set_Tuple::������̒l���i�[����Tuple
		//flont_Tuple::��������tuple�̒l
		//tuple::��ڈȍ~�̒l
		template<size_t ...N, class MT_FlontType, class ...MT_Tuple>
		static constexpr void TupleUnzip(auto& set_Tuple, std::integer_sequence<size_t, N...>, MT_FlontType& flont_Tuple, MT_Tuple&... tuple)
		{
			S_TupleUnzip<t_Number, T_TupleInside..., T_Tuple...>::TupleUnzip(set_Tuple, std::get<N>(flont_Tuple)..., tuple...);
		}

	public:
		using Type = S_TupleUnzip<t_Number+1,T_TupleInside..., T_Tuple...>::Type;
		
		//�d�l
		//[flont_Tuple]�̒l�𕪉���������
		//
		//����
		//set_Tuple::������̒l���i�[����Tuple
		//flont_Tuple::��������tuple�̒l
		//tuple::��ڈȍ~�̒l
		template<class MT_FlontType, class ...MT_Tuple>
		static constexpr void TupleUnzip(auto& set_Tuple, MT_FlontType& flont_Tuple, MT_Tuple&... tuple)
		{
			S_TupleUnzip<t_Number, std::tuple<T_TupleInside...>,T_Tuple...>::TupleUnzip(set_Tuple,std::make_index_sequence<sizeof...(T_TupleInside)>(),flont_Tuple,tuple...);
		}
	};

	template<int t_Number,class ...T_Tuple>
	struct S_TupleUnzip<t_Number, std::nullopt_t, T_Tuple...>
	{
		//�d�l
		//[...T_Tuple]���̑S�Ă�Tuple�𕪉����A1��Tuple�Ɋi�[�����^
		using Type = std::tuple<T_Tuple...>;

		//�d�l
		//[set_Tuple]�̒l�̊i�[���I������
		static constexpr void TupleUnzip(auto& set_Tuple){}
	};
public:
	//�d�l
	//[...T_Tuple]���̑S�Ă�Tuple�𕪉����A1��Tuple�Ɋi�[�����^
	using Type = S_TupleUnzip<0,T_Tuple..., std::nullopt_t>::Type;

	//�d�l
	//�������A�i�[����Tuple�̕ϐ����擾����
	Type tuple;

private:

	//�d�l
	//[set_Tuple...]����Tuple�𕪉����A1��Tuple�ɂ܂Ƃ߂��l��Ԃ�
	//
	//����
	//set_Tuple::��������Tuple
	template<size_t ...N>
	constexpr auto TupleUnzip(std::index_sequence<N...>, T_Tuple&... set_Tuple)
	{
		typename S_EnvelopOptional<Type>::Type optionalTuple;
		S_TupleUnzip<0, T_Tuple..., std::nullopt_t>::TupleUnzip(optionalTuple, set_Tuple...);
		Type tuple(std::get<N>(optionalTuple).value()...);
		return tuple;
	}
public:

	//�d�l
	//[...set_Tuple]���̑S�Ă�Tuple�𕪉����A1��Tuple�Ɋi�[����
	constexpr IS_TupleUnzip(T_Tuple&... set_Tuple)
		:tuple(TupleUnzip(std::make_index_sequence<std::tuple_size_v<Type>>(), set_Tuple...)){}

	constexpr operator Type()
	{
		return tuple;
	}

};


