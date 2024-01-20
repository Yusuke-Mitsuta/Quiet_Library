#pragma once

#include"Tuple_Declare.h"
#include"Tuple_Apply_Type.h"
#include"Tuple_Apply_Fn.h"
#include"Tuple_Apply_Array_Set.h"
#include"Tuple_Apply_Request.h"
#include"Tuple_Apply_Class_Create.h"

#include"main.h"

namespace N_Tuple
{



	//仕様
	//変数に対して、一対多、多対一、多対多の変換を行い、
	// 関数オブジェクト、クラスコンストラクタを実行する
	//
	//テンプレート
	// [T_Fn_Action]：変数を入れて実行する、[関数ポインター、Function、クラス]の型
	//[T_Set_Types...]：一対多、多対一、多対多の変換を伴う変数
	// 
	//補足
	//実行は[::Apply(args...)]を呼び出す事
	//一対多の変換はコンストラクタを呼び出せる事、
	//多対一の変換は展開する変数のクラスに
	// [using tuple=tuple_t< ... >]、[auto& get<N>()]記述されている事。
	//
	// 一対多の変換時、変換後の[&],[*]は自動で補完されるが、
	// 変換後の変数と変換に用いた変数の関係は個別に定義されない限りコピーである。
	template<class T_Fn,class ...T_Set_Types>
	struct I_Apply_Action
	{
	//private:

		using S_Request= N_Apply::I_Request<T_Fn, T_Set_Types...>;

		template<N_Apply::E_Type t_type>
		static constexpr bool is_apply_type= N_Apply::is_apply_type<T_Fn, t_type>;

		//仕様
		//型の判定が終了する際に呼び出される
		template<class T_Request_Types = invalid_t,class ...Ts>
		struct S_Result
		{
			using chack = T_Request_Types;

			using convert = S_Result;

			template<class ...T_Args>
			static constexpr auto Apply(auto* fn, T_Args&&... args)
			{
				return fn->operator()(std::forward<T_Args>(args)...);
			}

		};

		//仕様
		//要求する引数と指定した引数に互換性があるか判定する。
		//
		//テンプレート
		// [T_Request_Types_Tuple]：要求する引数を反転したtuple_tp
		// [T_Set_Types_Tuple]：指定する引数を反転したtuple_tp
		// [t_constructible_from]：要求している型に対して、[T_Set_Types...]型の変数で作れるか判定する。
		// [T_Set_Types_Expand]：指定する引数の型が展開出来るか判定する
		// [T_Set_Types...]：要求している型を作る型リスト
		//
		//補足
		//[T_Set_Types_Expand]の展開できるかは、[N_Tuple::S_Parameter::tuple]で定義されている
		template<class T_Request_Types_Tuple,
			class T_Set_Types_Tuple,
			bool t_constructible_from,
			bool T_Set_Types_Expand,
			class ...T_Set_Types>
		struct S_Apply_Args_Chack
		{
			using type = S_Result<>;
		};

		//仕様
		// [T_Set_Types]が[invalid_t]のみで、[T_Set_Types_Tuple]が最後まで判定しきると、
		//判定成功とする
		template<class T_Request_Types_Tuple,
			class T_Set_Types_Tuple,
			class ...T_Set_Types>
		using U_Function_Args_Chack_Next =
			S_Apply_Args_Chack<T_Request_Types_Tuple, T_Set_Types_Tuple,
			std::constructible_from<std::remove_reference_t<typename T_Request_Types_Tuple::type>, typename T_Set_Types_Tuple::type, T_Set_Types...> ||
			std::constructible_from<std::remove_pointer_t<typename T_Request_Types_Tuple::type>, typename T_Set_Types_Tuple::type, T_Set_Types...>,
			is_invalid_not<typename N_Tuple::S_Parameter<typename T_Set_Types_Tuple::type>::tuple>,
			typename T_Set_Types_Tuple::type, T_Set_Types...>;



		template<class T_Request_Types_Tuple,
			class T_Set_Types_Tuple,
			bool t_constructible_from,
			bool T_Set_Types_Expand>
			requires (is_invalid<typename T_Set_Types_Tuple::type>)
		struct S_Apply_Args_Chack<T_Request_Types_Tuple, T_Set_Types_Tuple, t_constructible_from, T_Set_Types_Expand,
			invalid_t>
		{
			using type = S_Result<typename T_Request_Types_Tuple::reverse>;
		};


		//仕様
		//要求する引数の型に対して、[T_Set_Types...]の型で生成でき無い場合の動作
		// [T_Set_Types...]を引継ぎ、[T_Set_Types_Tuple]を次に進める
		//
		//補足
		//[U_Function_Args_Chack_Next]内で、引継いだ[T_Set_Types...]に対して、
		// [T_Set_Types_Tuple]を次に進めた際の選択中の型を追加する。
		template<class T_Request_Types_Tuple,
			class T_Set_Types_Tuple,
			class ...T_Set_Types>
			requires requires
		{
			requires is_invalid_not<typename T_Set_Types_Tuple::type>;
		}
		struct S_Apply_Args_Chack<T_Request_Types_Tuple, T_Set_Types_Tuple, false, false,
			T_Set_Types...>
		{
			using type = U_Function_Args_Chack_Next<T_Request_Types_Tuple,
				typename T_Set_Types_Tuple::next,
				T_Set_Types...>::type;
		};

		//仕様
		//要求する引数の型に対して、[T_Set_Types...]の型で生成できる場合の動作
		// [T_Set_Types...]をリセットし、[T_Request_Types_Tuple][T_Set_Types_Tuple]を次の判定に進める、
		template<class T_Request_Types_Tuple,
			class T_Set_Types_Tuple,
			bool T_Set_Types_Expand,
			class ...T_Set_Types>
			requires requires
		{
			requires is_invalid_not<typename T_Set_Types_Tuple::type>;
			
		}
		struct S_Apply_Args_Chack<T_Request_Types_Tuple, T_Set_Types_Tuple, true, T_Set_Types_Expand,
			T_Set_Types...>
		{

			//仕様
			//次以降の変数を[T_Set_Types...]追加しても[T_Request_Types_Tuple::type]が生成出来るか判定する
			// その結果が
			//　　有効値であれば、次以降の変数を追加する。
			//　　無効値であれば、[T_Set_Types...]の変数で[T_Request_Types_Tuple::type]を生成する
			//
			//補足
			//次以降の引数を加え、エラーになる場合、最後の引数を取得したと判定する。
			template<class T = typename S_Apply_Args_Chack<T_Request_Types_Tuple, T_Set_Types_Tuple, false, T_Set_Types_Expand,
				T_Set_Types...>::type::chack>
			struct S_last_args_chack
			{
				using type = typename S_Apply_Args_Chack<T_Request_Types_Tuple, T_Set_Types_Tuple, false, T_Set_Types_Expand,
					T_Set_Types...>::type;
			};

			template<>
			struct S_last_args_chack<invalid_t>
			{
				using type = S_Apply_Args_Chack;
			};

			using type = S_last_args_chack<>::type;

			using next = U_Function_Args_Chack_Next<
				typename T_Request_Types_Tuple::next,
				typename T_Set_Types_Tuple::next>::type;

			using chack = next::chack;


			template<class T_Converted = typename T_Set_Types_Tuple::tail::reverse>
			struct S_Convert
			{
				using convert = next::convert;

			};

			template<class ...T_Converted>
				requires (sizeof...(T_Set_Types) > 1) &&
				((!is_apply_type<N_Apply::E_Type::CLASS>) ||
				(is_apply_type<N_Apply::E_Type::CLASS> &&
				is_invalid_not <typename S_Parameter<T_Fn>::tuple >))
			struct S_Convert<tuple_t<T_Converted...>>
			{
				using convert = S_Convert;


				//仕様
				//[T_Request_Type]型を[args...]から作り、その実体を返す
				//
				//補足
				//ここで生成される変数は、変数[args...]を元に生成されるだけであり、、変数に[&][*]が付与されていた場合も、
				// 生成するクラス内で個別に置換しない場合、生成されるクラスから、変数[args...]にはアクセスされない。
				template<class ...T_back_args>
				static constexpr auto Apply(auto* fn, T_Converted&&... converted_args, T_Set_Types&&... args, T_back_args&&... back_args)
				{
					return next::convert::Apply(
						fn,
						std::forward<T_Converted>(converted_args)...,
						std::remove_reference_t<typename T_Request_Types_Tuple::type>(std::forward<T_Set_Types>(args)...),
						std::forward<T_back_args>(back_args)...);
				}


				//仕様
				//[T_Request_Type]型を[args...]から作り、そのポインターを返す
				//
				//補足
				//ここで生成される変数は、変数[args...]を元に生成されるだけであり、変数に[&][*]が付与されていた場合も、
				// 生成するクラス内で個別に置換しない場合、生成されるクラスから、変数[args...]にはアクセスされない。
				// 
				//[T_Request_Type]型を[args...]から作り、そのポインターを返す
				template<class ...T_back_args>
					requires requires
				{
					requires is_pointer<typename T_Request_Types_Tuple::type>;
				}
				static constexpr auto Apply(auto* fn, T_Converted&&... converted_args, T_Set_Types&&... args, T_back_args&&... back_args)
				{

					//ポインターを返す為の一時オブジェクト
					std::remove_pointer_t<typename T_Request_Types_Tuple::type> temp(std::forward<T_Set_Types>(args)...);

					return next::convert::Apply(
						fn,
						std::forward<T_Converted>(converted_args)...,
						&temp,
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
		template<class T_Request_Types_Tuple,
			class T_Set_Types_Tuple,
			class T_FronT_Set_Types,
			class ...T_Set_Types>
			requires requires
		{
			requires is_invalid_not<typename T_Set_Types_Tuple::type>;
		}
		struct S_Apply_Args_Chack<T_Request_Types_Tuple, T_Set_Types_Tuple, false, true,
			T_FronT_Set_Types, T_Set_Types...>
		{
			//仕様
			//互換性のある型に展開する
			// [using tuple}にて定義される型
			using expand = N_Tuple::S_Parameter<T_FronT_Set_Types>::tuple;

			//仕様
			//既存の引数の型リストから選択中の型を[expand]で定義された型に変更する
			using inserT_Set_Types = N_Tuple::U_Insert_tuple_expand<typename T_Set_Types_Tuple::remove, typename expand::reverse>;

			//仕様
			//次の処理を行うクラス
			using next = U_Function_Args_Chack_Next<
				T_Request_Types_Tuple,
				inserT_Set_Types,
				T_Set_Types...>::type;

			//仕様
			//[next]の終着場合
			using type = S_Apply_Args_Chack;

			//仕様
			//引数の互換性を確かめる
			using chack = next::chack;

			//仕様
			//引数を互換性のある型に展開する
			template<class T_Converted = typename T_Set_Types_Tuple::tail::reverse,
				class T_index_sequence = typename N_Tuple::U_index_sequence<expand::size>::reverse>
			struct S_Convert;


			template<class ...T_Converted, class T_index_sequence>
			struct S_Convert<tuple_t<T_Converted...>, T_index_sequence>
			{
				template<size_t t_select_number>
				using select_type = N_Tuple::U_Element_t<t_select_number, expand>;

				//仕様
				//[change_args]の[t_select_number]番目の変数を取得する
				template<size_t t_select_number>
				static constexpr auto get(T_FronT_Set_Types&& change_args)
				{
					return std::get<t_select_number>(std::forward<T_FronT_Set_Types>(change_args));
				}

				//仕様
				//[change_args]の[t_select_number]番目の変数を参照で取得する
				template<size_t t_select_number>
					requires is_reference<select_type<t_select_number>>
				static constexpr auto& get(T_FronT_Set_Types change_args)
				{
					return std::get<t_select_number>(std::forward<T_FronT_Set_Types>(change_args));
				}

				//仕様
				//[change_args]の[t_select_number]番目の変数をポインターで取得する
				template<size_t t_select_number>
					requires is_pointer<select_type<t_select_number>>
				static constexpr auto* get(T_FronT_Set_Types&& change_args)
				{
					return &std::get<t_select_number>(std::forward<T_FronT_Set_Types>(change_args));
				}

				//仕様
				//引数[change_args]を後ろから順番に展開して行く
				//
				//テンプレート
				//[T_expand_Numbers]：[change_args]の展開する要素数の番号を後ろから並べた物
				//  
				//補足
				//[change_args]が、5つの要素数に展開される場合、[T_expand_Numbers = tuple_v<4,3,2,1,0> ]となる
				template<class T_expand_Numbers = T_index_sequence, class ...T_back_args>
				static constexpr auto Apply(auto* fn,T_Converted&&... args, T_FronT_Set_Types&& change_args, T_back_args&&... back_args)
				{
					return Apply<typename T_expand_Numbers::remove>(
						fn,
						std::forward<T_Converted>(args)...,
						std::forward<T_FronT_Set_Types>(change_args),
						get<T_expand_Numbers::value>(std::forward<T_FronT_Set_Types>(change_args)),
						std::forward<T_back_args>(back_args)...);
				}

				//仕様
				//引数[change_args]の展開が終わった場合、次の工程に進める
				template<same_as<tuple_v<>> T_expand_Numbers = T_index_sequence, class ...T_back_args>
				static constexpr auto Apply(auto* fn,T_Converted&&... args, T_FronT_Set_Types&& change_args, T_back_args&&... back_args)
				{
					return next::convert::Apply(
						fn,
						std::forward<T_Converted>(args)...,
						std::forward<T_back_args>(back_args)...);
				}

			};

			using convert = S_Convert<>;
		};


		using next = U_Function_Args_Chack_Next<
			typename S_Request::args::reverse,
			typename tuple_t<T_Set_Types...>::reverse::create_p>::type;

		using chack = next::chack;

	public:

		using type = chack;

		//仕様
		//型[fn]に対して、要求するに[args...] を一対多、多対一の変換を行い、
		// [fn]のコンストラクタを実行する(生成する)。
		template<class T_Create_class = T_Fn, class ...T_Args>
			requires (N_Apply::is_apply_type<T_Create_class, N_Apply::E_Type::CLASS> ||
					  N_Apply::is_apply_type<T_Create_class, N_Apply::E_Type::CLASS_NEW>)
		static constexpr auto Apply(T_Args&&... args)
		{
			N_Apply::S_Class_Create<T_Create_class> fn_action = {};
			return next::convert::Apply(&fn_action, std::forward<T_Args>(args)...);
		}

		//仕様
		//配列型のポインター[array_p]に[T_Fn]の0次元目の要素数を追加する。
		template<class T_Array, class ...T_Args>
			requires N_Apply::is_apply_type<T_Fn, N_Apply::E_Type::ARRAY>
		static constexpr auto Apply(T_Array* array_p, T_Args&&... args)
		{
			N_Apply::S_Array_Create fn_action = { array_p };
			return next::convert::Apply(&fn_action, std::forward<T_Args>(args)...);
		}

		//仕様
		//関数[fn]に対して、要求するに[args...] を一対多、多対一の変換を行い、
		// [fn]を実行する
		template<class ...T_Args>
			requires N_Apply::is_apply_type<T_Fn, N_Apply::E_Type::FN>
		static constexpr auto Apply(T_Fn&& fn,T_Args&&... args)
		{
			N_Apply::S_Fn_Action fn_action(fn, &invalid);
			return next::convert::Apply(&fn_action,std::forward<T_Args>(args)...);
		
		}

		//仕様
		//関数[fn]に対して、要求するに[args...] を一対多、多対一の変換を行い、
		// ポインターを用いて[fn]を実行する
		template<class ...T_Args>
			requires N_Apply::is_apply_type<T_Fn, N_Apply::E_Type::FN>
		static constexpr auto Apply(T_Fn&& fn,S_Request::pointer* p,T_Args&&... args)
		{
			N_Apply::S_Fn_Action fn_action(fn, p);
			return next::convert::Apply(&fn_action,std::forward<T_Args>(args)...);
		}
	};

}