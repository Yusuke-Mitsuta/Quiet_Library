#pragma once

#include"Tuple.h"
#include"Expand.h"

namespace N_Function
{

	template<class T_Request_Args, class T_Bind_Args>
	struct I_Function_Args_Convert
	{
	public:
		template<class T_Request_Args = invalid_t>
		struct S_Result
		{
			using chack = T_Request_Args;

			using convert = S_Result;

			static constexpr auto Convert(auto fn,auto... args)
			{
				return fn(args...);
			}

			template<class T_Fn>
			requires requires
			{
				requires std::is_member_function_pointer_v<T_Fn>;
			}
			static constexpr auto Convert(T_Fn fn,auto* p, auto... args)
			{
				return (p->*fn)(args...);
			}

		};


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
			std::constructible_from<typename T_Request_Args_Tuple::type, typename T_Bind_Args_Tuple::type, T_Bind_Args...>,
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
				static constexpr auto Convert(T_Converted... converted_args, T_Bind_Args... args, auto... back_args)
				{
					next::convert::Convert(converted_args..., T_Request_Args_Tuple::type(args...), back_args...);
				}

			};

			using t = T_Bind_Args_Tuple;
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

			using expand = N_Tuple::S_Parameter<T_Front_Bind_Args>::tuple::reverse;

			using insert_bind_args = N_Tuple::U_Insert_tuple_expand<typename T_Bind_Args_Tuple::remove, expand>;

			using next = U_Function_Args_Chack_Next<
				T_Request_Args_Tuple,
				insert_bind_args,
				T_Bind_Args...>::type;

			using type = S_Function_Args_Chack;

			using chack = next::chack;

			template<class T_Converted =typename T_Bind_Args_Tuple::tail::reverse,
				class T_index_sequence = N_Tuple::U_index_sequence<expand::size>>
			struct S_Convert;

			template<class ...T_Converted,size_t ...t_expand_number>
			struct S_Convert<tuple_t<T_Converted...>, tuple_v<t_expand_number...>>
			{

				static constexpr auto Convert(T_Converted... args, T_Front_Bind_Args change_args,auto... back_args)
				{
					next::convert::Convert(args..., std::get<t_expand_number>(change_args)...,back_args...);
				}

			};

			using convert = S_Convert<>;


		};

		
	//private:
		using next = U_Function_Args_Chack_Next<typename T_Request_Args::reverse,
			typename T_Bind_Args::reverse::create_p>::type;

		using chack = next::chack;

	public:

		using type = chack;

		static constexpr auto Convert(auto... args)
		{
			return next::convert::Convert(args...);
		}


	};


}