#pragma once

#include"Concept.h"

#include"Array_Capacity.h"

namespace N_Constexpr::N_Array
{
	//仕様
	//[t_Size]を二進数で表した時の、最上位の立ってるビットが2の何乗になるかを調べる
	//
	//template
	//t_Size::最上位ビットを調べる値
	//
	//引数
	//two_index::指数を調べ始める最小値
	//
	//戻り値
	//最上位のビットの指数
	template<unsigned int t_Size>
	constexpr short Get_Binary_Digit(short two_index = 1)
	{
		if (t_Size <= (1 << two_index))
		{
			return two_index - 1;
		}

		return Get_Binary_Digit<t_Size>(two_index + 1);
	}

	//仕様
	//Accesのステート管理
	enum class E_AccesState
	{
		NORMAL,//通常
		END,//Dataにアクセスする
		NOT_Select_1//1は選択不可
	};

	//仕様
	//Accesのステート管理を行う
	// 
	//template
	//t_Size::要素の合計
	//t_Two_index::二進数で2の何乗にアクセスしているか
	//t_SelectNum::現在選択している数字(辿っているルート)
	//
	//戻り値
	//現在のステート
	template<unsigned int t_Size, short t_Two_index,unsigned int t_SelectNum>
	requires Fg<(t_Two_index>=0)>
	constexpr E_AccesState Get_State()
	{
		if (t_Size <= (t_SelectNum| (1 << t_Two_index)))
		{
			return E_AccesState::NOT_Select_1;
		}
		return E_AccesState::NORMAL;
	}

	template<unsigned int t_Size, short t_Two_index,unsigned int t_SelectNum>
	requires Fg<(t_Two_index<0)>
	constexpr E_AccesState Get_State()
	{
		return E_AccesState::END;

	}


	//仕様
	//Constexpr_Arrayの各要素を二進数で格納する
	//
	//template
	//T::要素の型
	//t_Size::要素の合計
	//t_Two_index::二進数で2の何乗にアクセスしているか
	//t_SelectNum::現在選択している数字(辿っているルート)
	//t_State::アクセスの状態管理
	template<class T,unsigned int t_Size,
		short  t_Two_index,
		unsigned int t_SelectNum = 0,
		E_AccesState t_State=Get_State<t_Size,t_Two_index,t_SelectNum>()>
	class Access
	{
	public:

		
		//仕様
		//二進数で[0]を選択する
		Access<T,t_Size,t_Two_index-1,t_SelectNum> _0;

		//仕様
		//二進数で[1]を選択する
		Access< T, t_Size, t_Two_index - 1,t_SelectNum | (1 << t_Two_index)> _1;

		//仕様
		//各要素にアクセスする
		//
		//引数
		//selectNum::アクセスする要素の番号
		//
		//戻り値
		//アクセスした要素の参照
		constexpr T& operator[](unsigned int selectNum)
		{
			if (selectNum < (1 <<t_Two_index))
			{
				return _0.operator[](selectNum);
			}
			return _1.operator[](selectNum - (1 << t_Two_index));
		}

	};
	//仕様
	//次に[_1]を選択すると要素数を超えてしまうとき、[_1]を選択肢から外す
	template<class T, unsigned int t_Size,short  t_Two_index, unsigned int t_SelectNum>
	class Access<T,t_Size,t_Two_index,t_SelectNum,E_AccesState::NOT_Select_1>
	{
	public:
		Access<T, t_Size, t_Two_index - 1, t_SelectNum> _0;

		constexpr T& operator[](unsigned int selectNum)
		{
			return _0.operator[](selectNum);
		}

	};

	//仕様
	//辿ってきたルートのアクセス先データ
	template<class T, unsigned int t_Size, int t_Two_index,unsigned int t_SelectNum>
	class Access<T, t_Size, t_Two_index, t_SelectNum, E_AccesState::END>
	{
	public:

		T Data;

		constexpr T& operator[](unsigned int selectNum)
		{
			return Data;
		}

	};
}

namespace N_Constexpr
{
	//仕様
	//Constexpr_Arrayの各要素を二進数で格納する
	//template
	//T::要素の型
	//t_Size::要素の合計
	template<class T,unsigned int t_Size>
	class Array
	{
	public:
		using T = T;
		//仕様
		//データの格納先で一回目に[_0]を選択する
		N_Array::Access<T, t_Size,N_Array::Get_Binary_Digit<t_Size>()-1 ,0> _0;

		//仕様
		//データの格納先で一回目に[_1]を選択する
		N_Array::Access<T, t_Size, N_Array::Get_Binary_Digit<t_Size>() - 1, (1 << N_Array::Get_Binary_Digit<t_Size>())> _1;

		//仕様
		//各要素にアクセスする
		//
		//引数
		//selectNum::アクセスする要素の番号
		//
		//戻り値
		//アクセスした要素の参照
		constexpr T& operator[](unsigned int selectNum)
		{

			if (selectNum < (1 << N_Array::Get_Binary_Digit<t_Size>()))
			{
				return _0.operator[](selectNum);
			}
			return _1.operator[](selectNum- (1 << N_Array::Get_Binary_Digit<t_Size>()));
		}

		
		template<size_t ref_Size = t_Size, class Array_T = T, class U, class ...V >
			requires std::same_as< std::true_type, typename Array_Capacity<ref_Size, Array_T, U, V...>::Type>
		Array(U u, V... v) {}


	};

	template<class T>
	class Array<T,1>
	{
	public:
		//仕様
		//データの格納先で一回目に[_0]を選択する
		N_Array::Access<T, 1, N_Array::Get_Binary_Digit<1>() - 1, 0> _0;

		constexpr T& operator[](unsigned int selectNum)
		{
			return _0.operator[](selectNum);
		}

	};

	template<class U, class ...V>
	Array(U, V...) -> Array<U, sizeof...(V) + 1>;
}

