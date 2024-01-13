#pragma once

#include"Tuple.h"
#include"Expand.h"

namespace N_Function
{

	template<class T_Request_Args, class T_Bind_Args>
	struct I_Function_Args_Convert
	{
	private:
		template<class T_Request_Args = invalid_t>
		struct S_Result
		{
			using chack = T_Request_Args;

			using convert = S_Result;

			template<class T_Fn,class ...T_Args>
			static constexpr auto Convert(T_Fn&& fn,T_Args&&... args)
			{
				return std::forward<T_Fn>(fn)(args...);
			}

			template<class T_Fn,class ...T_Args>
			requires requires
			{
				requires std::is_member_function_pointer_v<std::remove_reference_t<T_Fn>> ;
			}
			static constexpr auto Convert(T_Fn&& fn,auto* p, T_Args... args)
			{
				return (p->*std::forward<T_Fn>(fn))(args...);
			}

		};

		//仕様
		//要求する引数と指定した引数に互換性があるか判定する。
		//
		//テンプレート
		// [T_Request_Args_Tuple]：要求する引数を反転したtuple_tp
		// [T_Bind_Args_Tuple]：指定する引数を反転したtuple_tp
		// [t_constructible_from]：要求している型に対して、[T_Bind_Args...]型の変数で作れるか判定する。
		// [t_Bind_Args_Expand]：指定する引数の型が展開出来るか判定する
		// [T_Bind_Args...]：要求している型を作る型リスト
		//
		//補足
		//[t_Bind_Args_Expand]の展開できるかは、[N_Tuple::S_Parameter::tuple]で定義されている
		template<class T_Request_Args_Tuple,
			class T_Bind_Args_Tuple,
			bool t_constructible_from,
			bool t_Bind_Args_Expand,
			class ...T_Bind_Args>
		struct S_Function_Args_Chack;
		



		//仕様
		// [T_Bind_Args]が[invalid_t]のみで、[T_Bind_Args_Tuple]が最後まで判定しきると、
		//判定成功とする
		template<class T_Request_Args_Tuple,
			class T_Bind_Args_Tuple,
			class ...T_Bind_Args>
		using U_Function_Args_Chack_Next =
			S_Function_Args_Chack<T_Request_Args_Tuple, T_Bind_Args_Tuple,
			std::constructible_from<std::remove_reference_t<typename T_Request_Args_Tuple::type>, typename T_Bind_Args_Tuple::type, T_Bind_Args...> ||
			std::constructible_from<std::remove_pointer_t<typename T_Request_Args_Tuple::type>, typename T_Bind_Args_Tuple::type, T_Bind_Args...> ,
			is_invalid_not<typename N_Tuple::S_Parameter<typename T_Bind_Args_Tuple::type>::tuple>,
			typename T_Bind_Args_Tuple::type, T_Bind_Args...>;



		template<class T_Request_Args_Tuple,
			class T_Bind_Args_Tuple,
			bool t_constructible_from,
			bool t_Bind_Args_Expand>
			requires (is_invalid<typename T_Bind_Args_Tuple::type>)
		struct S_Function_Args_Chack<T_Request_Args_Tuple, T_Bind_Args_Tuple, t_constructible_from, t_Bind_Args_Expand,
			 invalid_t>
		{
			using type = S_Result<
				typename T_Request_Args_Tuple::reverse>;
		};


		//仕様
		// [T_Bind_Args]が残っている状態で[T_Bind_Args_Tuple]が最後まで判定しきると、
		//判定失敗とする
		template<class T_Request_Args_Tuple,
			class T_Bind_Args_Tuple,
			bool t_constructible_from,
			bool t_Bind_Args_Expand,
			class ...T_Bind_Args>
			requires requires
		{
			requires is_invalid<typename T_Bind_Args_Tuple::type>;
			requires (sizeof...(T_Bind_Args) > 0);
		}
		struct S_Function_Args_Chack<T_Request_Args_Tuple, T_Bind_Args_Tuple, t_constructible_from, t_Bind_Args_Expand,
			invalid_t, T_Bind_Args...>
		{
			using type = S_Result<>;

		};


		//仕様
		//要求する引数の型に対して、[T_Bind_Args...]の型で生成でき無い場合の動作
		// [T_Bind_Args...]を引継ぎ、[T_Bind_Args_Tuple]を次に進める
		//
		//補足
		//[U_Function_Args_Chack_Next]内で、引継いだ[T_Bind_Args...]に対して、
		// [T_Bind_Args_Tuple]を次に進めた際の選択中の型を追加する。
		template<class T_Request_Args_Tuple,
			class T_Bind_Args_Tuple,
			class ...T_Bind_Args>
			requires requires
		{
			requires is_invalid_not<typename T_Bind_Args_Tuple::type>;
		}
		struct S_Function_Args_Chack<T_Request_Args_Tuple, T_Bind_Args_Tuple, false, false,
			T_Bind_Args...>
		{
			using type = U_Function_Args_Chack_Next<T_Request_Args_Tuple,
				typename T_Bind_Args_Tuple::next,
				T_Bind_Args...>::type;
		};

		//仕様
		//要求する引数の型に対して、[T_Bind_Args...]の型で生成できる場合の動作
		// [T_Bind_Args...]をリセットし、[T_Request_Args_Tuple][T_Bind_Args_Tuple]を次の判定に進める、
		template<class T_Request_Args_Tuple,
			class T_Bind_Args_Tuple,
			bool t_Bind_Args_Expand,
			class ...T_Bind_Args>
			requires requires
		{
			requires is_invalid_not<typename T_Bind_Args_Tuple::type>;
		}
		struct S_Function_Args_Chack<T_Request_Args_Tuple, T_Bind_Args_Tuple, true, t_Bind_Args_Expand,
			T_Bind_Args...>
		{

			using next = U_Function_Args_Chack_Next<
				typename T_Request_Args_Tuple::next,
				typename T_Bind_Args_Tuple::next>::type;

			using type = S_Function_Args_Chack;

			using chack = next::chack;

			template<class T_Converted = typename T_Bind_Args_Tuple::tail::reverse>
			struct S_Convert
			{
				using convert = next::convert;
			};

			template<class ...T_Converted>
				requires (sizeof...(T_Bind_Args) > 1)
			struct S_Convert<tuple_t<T_Converted...>>
			{
				using convert = S_Convert;

				//using request_type = T_Request_Args_Tuple::type;

				using create_type = T_Request_Args_Tuple::type;

				//仕様
				//[T_Request_Type]型を[args...]から作る
				template<class T_Request_Type = T_Request_Args_Tuple::type>
				static constexpr auto Constructor(T_Bind_Args&&... args)
				{
					return T_Request_Type(args...);
				}

				//仕様
				//[T_Request_Type]型を[args...]から作り、そのポインターを返す
				//
				//補足
				// ここで生成される変数のポインターは見せかけの為、
				// 生成するクラス内で[args...]との互換性を各自、定義を行う
				// 
				//	行わない場合は、関数にポインターとして渡されるが[args...]には一切干渉出来ない
				template<class T_Request_Type = T_Request_Args_Tuple::type>
					requires requires
				{
					requires is_pointer<T_Request_Type>;
				}
				static constexpr auto* Constructor(T_Bind_Args&&... args)
				{
					std::remove_pointer_t<T_Request_Type> aba(args...);
					return &aba;
				}

				//仕様
				//[T_Request_Type]型を[args...]から作り、その参照を返す
				//
				//補足
				// ここで生成される変数の参照は見せかけの為、
				// 生成するクラス内で[args&...]との互換性を各自、定義を行う
				// 
				//	行わない場合は、関数に参照として渡されるが[args...]には一切干渉出来ない
				template<class T_Request_Type = T_Request_Args_Tuple::type>
					requires requires
				{
					requires is_reference<T_Request_Type>;
				}
				static constexpr auto Constructor(T_Bind_Args&&... args)
				{
					return std::remove_reference_t<T_Request_Type>(args...);
				}

				template<class ...T_back_args>
				static constexpr auto Convert(T_Converted&&... converted_args, T_Bind_Args&&... args, T_back_args&&... back_args)
				{
					return next::convert::Convert(
						std::forward<T_Converted>(converted_args)...,
						Constructor(std::forward<T_Bind_Args>(args)...),
						//std::remove_reference_t<typename T_Request_Args_Tuple::type>(std::forward<T_Bind_Args>(args)...),
						std::forward<T_back_args>(back_args)...);
				}

			};

			using convert = S_Convert<>::convert;


		};

		//仕様
		//互換性のある型の定義がされている場合、その形に変換を実施する
		// 
		//補足
		// 互換性のある型の定義は、[N_Tuple::S_Parameter]の特殊化にて定義を行う
		template<class T_Request_Args_Tuple,
			class T_Bind_Args_Tuple,
			class T_Front_Bind_Args,
			class ...T_Bind_Args>
			requires requires
		{
			requires is_invalid_not<typename T_Bind_Args_Tuple::type>;
		}
		struct S_Function_Args_Chack<T_Request_Args_Tuple, T_Bind_Args_Tuple, false, true,
			T_Front_Bind_Args, T_Bind_Args...>
		{
			//仕様
			//互換性のある型に展開する
			// [using tuple}にて定義される型
			using expand = N_Tuple::S_Parameter<T_Front_Bind_Args>::tuple;

			//仕様
			//既存の引数の型リストから選択中の型を[expand]で定義された型に変更する
			using insert_bind_args = N_Tuple::U_Insert_tuple_expand<typename T_Bind_Args_Tuple::remove, typename expand::reverse>;
			
			//仕様
			//次の処理を行うクラス
			using next = U_Function_Args_Chack_Next<
				T_Request_Args_Tuple,
				insert_bind_args,
				T_Bind_Args...>::type;

			//仕様
			//[next]の終着場合
			using type = S_Function_Args_Chack;

			//仕様
			//引数の互換性を確かめる
			using chack = next::chack;

			//仕様
			//引数を互換性のある型に展開する
			template<class T_Converted =typename T_Bind_Args_Tuple::tail::reverse,
				class T_index_sequence = N_Tuple::U_index_sequence<expand::size>>
			struct S_Convert;


			template<class ...T_Converted,size_t ...t_expand_number>
			struct S_Convert<tuple_t<T_Converted...>, tuple_v<t_expand_number...>>
			{
				template<size_t t_select_number>
				using select_type = N_Tuple::U_Element_t<t_select_number, expand>;

				//仕様
				//[change_args]の[t_select_number]番目の変数を取得する
				template<size_t t_select_number>
					static constexpr auto get(T_Front_Bind_Args&& change_args)
				{
					return std::get<t_select_number>(std::forward<T_Front_Bind_Args>(change_args));
				}

				//仕様
				//[change_args]の[t_select_number]番目の変数を参照で取得する
				template<size_t t_select_number>
					requires is_reference<select_type<t_select_number>>
				static constexpr auto& get(T_Front_Bind_Args&& change_args)
				{
					return std::get<t_select_number>(std::forward<T_Front_Bind_Args>(change_args));
				}

				//仕様
				//[change_args]の[t_select_number]番目の変数をポインターで取得する
				template<size_t t_select_number>
					requires is_pointer<select_type<t_select_number>>
				static constexpr auto* get(T_Front_Bind_Args&& change_args)
				{
					return &std::get<t_select_number>(std::forward<T_Front_Bind_Args>(change_args));
				}

				//仕様
				//引数を互換性のある型に展開する
				template<class ...T_back_args>
				static constexpr auto Convert(T_Converted&&... args, T_Front_Bind_Args&& change_args, T_back_args&&... back_args)
				{
					return next::convert::Convert(
						std::forward<T_Converted>(args)...,
						get<t_expand_number>(std::forward<T_Front_Bind_Args>(change_args))...,
						std::forward<T_back_args>(back_args)...);
				}

			};

			using convert = S_Convert<>;
		};

		using next = U_Function_Args_Chack_Next<typename T_Request_Args::reverse,
			typename T_Bind_Args::reverse::create_p>::type;

		using chack = next::chack;

	public:

		using type = chack;

		template<class ...T_Args>
		static constexpr auto Convert(T_Args&&... args)
		{
			return next::convert::Convert(std::forward<T_Args>(args)...);
		}


	};


}