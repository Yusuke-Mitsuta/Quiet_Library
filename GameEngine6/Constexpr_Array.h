#pragma once

#include<initializer_list>
#include<compare>
#include"Concept.h"
#include"Using_Type.h"
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
	template<size_t t_Size>
	constexpr size_t Get_Binary_Digit(size_t two_index = 1)
	{
		if (t_Size <= (static_cast<size_t>(1) << two_index))
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
	template<size_t t_Size, short t_Two_index, size_t t_SelectNum>
		requires Fg<(t_Two_index >= 0)>
	constexpr E_AccesState Get_State()
	{
		if (t_Size <= (t_SelectNum | (1 << t_Two_index)))
		{
			return E_AccesState::NOT_Select_1;
		}
		return E_AccesState::NORMAL;
	}

	template<size_t t_Size, short t_Two_index, size_t t_SelectNum>
		requires Fg<(t_Two_index < 0)>
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
	template<class T, size_t t_Size,
		short t_Two_index,
		size_t t_SelectNum = 0,
		E_AccesState t_State = Get_State<t_Size, t_Two_index, t_SelectNum>()>
	class Access
	{
	public:


		//仕様
		//二進数で[0]を選択する
		Access<T, t_Size, t_Two_index - 1, t_SelectNum> _0;

		//仕様
		//二進数で[1]を選択する
		Access< T, t_Size, t_Two_index - 1,( t_SelectNum | (size_t(1) << t_Two_index))> _1;

		//仕様
		//各要素にアクセスする
		//
		//引数
		//selectNum::アクセスする要素の番号
		//
		//戻り値
		//アクセスした要素の参照
		constexpr T& operator[](size_t selectNum)
		{
			if (selectNum < (1 << t_Two_index))
			{
				return _0.operator[](selectNum);
			}
			return _1.operator[](selectNum - (1 << t_Two_index));
		}
		
	};

	//仕様
	//次に[_1]を選択すると要素数を超えてしまうとき、[_1]を選択肢から外す
	template<class T, size_t t_Size, short t_Two_index, size_t t_SelectNum>
	class Access<T, t_Size, t_Two_index, t_SelectNum, E_AccesState::NOT_Select_1>
	{
	public:
		Access<T, t_Size, t_Two_index - 1, t_SelectNum> _0;

		constexpr T& operator[](size_t selectNum)
		{
			return _0.operator[](selectNum);
		}

	};

	//仕様
	//辿ってきたルートのアクセス先データ
	template<class T, size_t t_Size, short t_Two_index, size_t t_SelectNum>
	class Access<T, t_Size, t_Two_index, t_SelectNum, E_AccesState::END>
	{
	public:

		T Data = T();

		constexpr T& operator[](size_t selectNum)
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
	template<class T, size_t t_Size>
	class Array
	{
	private:
		//仕様
		//[u]を[t_Number]に格納する
		//
		//template
		//t_Number::保存する要素番号
		template<size_t t_Number, class U, class ...V>
		constexpr void Set(U u, V ...v);

		template<size_t t_Number, class U, size_t t_Array_Size, class ...V>
		constexpr void Set(Array<U, t_Array_Size> u, V ...v);


		template<size_t t_Number, class U, class ...V>
		constexpr void Set(invalid_t nullopt, V ...v) {}

	public:
		//仕様
		//データの格納先で一回目に[_0]を選択する
		N_Array::Access<T, t_Size, N_Array::Get_Binary_Digit<t_Size>() - 1, 0> _0;

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
		constexpr T& operator[](size_t selectNum)
		{

			if (selectNum < (size_t(1) << N_Array::Get_Binary_Digit<t_Size>()))
			{
				return _0.operator[](selectNum);
			}
			return _1.operator[](selectNum - (size_t(1)<< N_Array::Get_Binary_Digit<t_Size>()));
		}


		template< class U, class ...V >
			requires N_Array::chack_C<T, t_Size, U, V...>
		constexpr Array(U u, V... v);

		constexpr Array() {}

		template<std::same_as<Array<T,t_Size>> T_2>
		constexpr bool operator==(T_2 t)
		{
			for (int i = 0; i < t_Size; i++)
			{
				if (this->operator[](i) != t[i])
				{
					return false;
				}
			}
			return true;
		}



	};

	template<class T>
	class Array<T, 1>
	{
	public:
		//仕様
		//データの格納先で一回目に[_0]を選択する
		N_Array::Access<T, 1,static_cast<short>(N_Array::Get_Binary_Digit<1>() -1), 0> _0;

		constexpr T& operator[](size_t selectNum)
		{
			return _0.operator[](selectNum);
		}

	};

	template<class U, class ...V>
	Array(U, V...) -> Array<U, N_Array::Capacity<U, 0, U, V...>::Size>;


	template<class T, size_t t_Size>
	template<size_t t_Number, class U, class ...V>
	inline constexpr void Array<T, t_Size>::Set(U u, V ...v)
	{
		this->operator[](t_Number) = static_cast<T>(u);
		Set<t_Number + 1, V...>(v...);
	}

	template<class T,size_t t_Size>
	template<size_t t_Number, class U, size_t t_Array_Size, class ...V>
	inline constexpr void Array<T, t_Size>::Set(Array<U, t_Array_Size> u, V ...v)
	{
		int i = 0;
		for (i = 0; i < t_Array_Size; i++)
		{
			this->operator[](t_Number + i) = static_cast<T>(u[i]);
		}
		Set<t_Number + i, V...>(v...);
	}

	template<class T, size_t t_Size>
	template<class U, class ...V>
		requires N_Array::chack_C<T, t_Size, U, V...>
	inline constexpr Array<T, t_Size>::Array(U u, V ...v)
	{
		Set<0, U, V...>(u, v..., invalid);
	}

}

