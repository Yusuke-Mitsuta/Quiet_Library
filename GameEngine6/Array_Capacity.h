#pragma once

//ファイル名
//Array_Capacity.h
//
//作成日
//2023/03/01
//
//製作者
//YUSUKE
//=================================================================

#include<concepts>
#include<optional>
#include <type_traits>

#include"Using_Type.h"

namespace N_Constexpr
{
	template<class T, Size_Type t_Size>
	class Array;
};


//仕様
//クラス[Array]の要素数の上限値に対して、引数にとる要素数が適正か判定する
//
//テンプレート
//remaining_Capacity::クラス[Array]の要素数
//T::Arrayの管理する型
//U::引数の一つ目型
//...V::引数の2つ目以降の型
//
//補足
//[Array_Capacity::Type]が判定の結果、可能なら[std::true_type],不可能なら[std::false_type]になる
//型TがArray型でなく、引数の型がArray型の時、Arrayが分解され、それぞれ一つの型として確認する
namespace N_Constexpr::N_Array
{
	template<class T, Size_Type t_Initial_Capacity, class U, class ...V>
	class Capacity
	{
	private:

		//仕様
		//構築可能か判定時のステート管理をする
		enum class E_State
		{
			T_CONVERTIBLE_U,
			ARRAY_DISASSEMBLY,
			END

		};

		//仕様
		//[U,V...]の時、ステートを選択する
		template<class U, class ...V>
		static constexpr E_State GetState()
		{
			if (std::convertible_to<U, T>)
			{
				return E_State::T_CONVERTIBLE_U;
			}
			else if (requires{typename U::Array; })
			{
				return E_State::ARRAY_DISASSEMBLY;
			}

			return E_State::END;

		}

		template<Size_Type remaining_Capacity, E_State t_State, class U, class ...V>
		class Calcu;

		//仕様
		//型[U]がArrayに格納な型か判定する
		template<Size_Type remaining_Capacity, class U, class ...V>
		class Calcu<remaining_Capacity, E_State::T_CONVERTIBLE_U, U, V...>
		{
		public:
			using Type = Calcu<remaining_Capacity - 1, GetState<V...>(), V...>::Type;

		};

		//仕様
		//型[U]がArray型かつ、型[T]がArray型でないか判定する
		template<Size_Type remaining_Capacity, class Array_T, Size_Type t_ArraySize, class ...V>
		class Calcu<remaining_Capacity, E_State::ARRAY_DISASSEMBLY, N_Constexpr::Array<Array_T, t_ArraySize>, V...>
		{
		public:
			using Type = Calcu<remaining_Capacity - t_ArraySize, GetState<V...>(), V...>::Type;
		};

		//仕様
		//Arrayに対して、[U,V...]の要素で構築時、構築可能かどうかの判定、可能ならば要素数の計算を行う
		//
		//補足
		//[Array_Capacity::Type]が判定の結果、可能なら[std::true_type],不可能なら[std::false_type]になる
		template<Size_Type remaining_Capacity, E_State t_State, class U, class ...V>
		class Calcu
		{
		private:

			//仕様
			//要素数が容量以内か判定する
			static constexpr bool Judge_Capacity()
			{
				if (remaining_Capacity >= 0)
				{
					return true;
				}

				return false;
			}
		public:

			//仕様
			//[U,V...]の要素で構築した時の計算結果にアクセス先
			using Type = Calcu<remaining_Capacity, E_State::END, U, V...>;

			//仕様
			//クラス[Array]の要素数の上限値に対して、引数にとる要素数が適正か判定した結果を返す
			//
			//補足
			//[Array_Capacity::Type]が判定の結果、可能なら[std::true_type],不可能なら[std::false_type]になる
			using Bool_Type = std::bool_constant<Judge_Capacity()>;

			//仕様
			//要素数を返す
			static constexpr Size_Type Size = t_Initial_Capacity - remaining_Capacity;
		};

		//仕様
		//クラス[Array]のに対して、[U,V...]の要素で構築した時の結果にアクセスする
		using Type = Calcu<t_Initial_Capacity, GetState<U, V...>(), U, V..., invalid_t>::Type;

	public:

		//仕様
		//クラス[Array]の要素数の上限値に対して、引数にとる要素数が適正か判定した結果を返す
		//
		//補足
		//[Array_Capacity::Type]が判定の結果、可能なら[std::true_type],不可能なら[std::false_type]になる
		using Bool_Type = Type::Bool_Type;

		//仕様
		//要素数を返す
		static constexpr Size_Type Size = Type::Size;

	};
};