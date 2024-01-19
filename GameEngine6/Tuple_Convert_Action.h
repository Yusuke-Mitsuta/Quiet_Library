#pragma once

#include"Tuple_Declare.h"
#include"main.h"
template<is_invalid_not T_Front_Parts, class ...T_Parts>
class Function;

namespace N_Function
{
	template<class ...T_Parts>
	struct Function_Core;

	template<class T_Fn, class T_Set_Types>
	struct I_Function_Operator_Search;
};

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
	//実行は[::Convert(args...)]を呼び出す事
	//一対多の変換はコンストラクタを呼び出せる事、
	//多対一の変換は展開する変数のクラスに
	// [using tuple=tuple_t< ... >]、[auto& get<N>()]記述されている事。
	//
	// 一対多の変換時、変換後の[&],[*]は自動で補完されるが、
	// 変換後の変数と変換に用いた変数の関係は個別に定義されない限りコピーである。
	template<class T_Fn,class ...T_Set_Types>
	struct I_Convert_Action
	{
	//private:


		//仕様
		//関数オブジェクトの引数とポインターの型を取得する。
		// 関数オブジェクト内に関数オブジェクトが複数内包されている場合、
		// 　一番初めに引数と互換性があったものが呼ばれる。
		template<class T_Fn = T_Fn>
		struct S_Request
		{
			static constexpr bool class_create_fg = true;
			using args = tuple_t<T_Fn>;
			using pointer = invalid_t;
		};
		
		template<class T_Array,size_t N>
		struct S_Request<T_Array[N]>
		{
			static constexpr bool class_create_fg = false;
			using args = U_Repeat_Multiple<T_Array,N>;
			using pointer = invalid_t;
		};

		template<class T_Fn>
		struct S_Request<T_Fn&>:
			S_Request<T_Fn> 
		{};

		
		//仕様
		//関数オブジェクトの引数とポインターの型を取得する。
		// 関数オブジェクト内に関数オブジェクトが複数内包されている場合、
		// 　一番初めに引数と互換性があったものが呼ばれる。
		template<class T_Fn>
			requires requires
		{
			requires std::is_function_v<std::remove_pointer_t<T_Fn>> ||
		std::is_member_function_pointer_v<T_Fn>;
			requires is_reference_not<T_Fn>;
		}
		struct S_Request<T_Fn>
		{
			using fn_core = N_Function::Function_Core<T_Fn>;
			static constexpr bool class_create_fg = false;
			using args = fn_core::request_args;
			using pointer = fn_core::request_pointer;
		};

		template<class ...T_Parts>
		struct S_Request<Function<T_Parts...>>
		{
			using operator_search = N_Function::I_Function_Operator_Search<Function<T_Parts...>, tuple_t<T_Set_Types...>>::type;
			static constexpr bool class_create_fg = false;
			using args = U_Select<1, operator_search>::back;
			using pointer = U_Select<2, operator_search>;
		};

		//仕様
		//クラスを生成するか判断するフラグ
		static constexpr bool class_create_fg = S_Request<>::class_create_fg;


		//仕様
		//関数オブジェクトとポインターを取得し、
		//関数オブジェクトによって、適切にポインターを使用する。
		// 
		//補足
		//[T_Fn_Action]が
		//動的関数の場合：ポインターを使用し関数ポインターにアクセスする
		//Functionの場合：ポインターの要求の有無によって使用を判断する
		//静的関数の場合：ポインターを使用せず関数ポインターにアクセスする
		template<class T_Fn_Action,class T_pointer>
		struct S_Fn_Action
		{
			T_Fn_Action fn;

			T_pointer* p;

			constexpr S_Fn_Action(T_Fn_Action set_fn, T_pointer* set_pointer) :
				fn(set_fn), p(set_pointer) {}

			constexpr S_Fn_Action(T_Fn_Action set_fn , T_pointer set_pointer) :
				fn(set_fn), p(&invalid){}


			//ポインターを使用せず関数オブジェクトにアクセスする
			template<class MT_Fn = T_Fn_Action, is_invalid MT_pointer = T_pointer,class... T_Args>
			constexpr auto operator()(T_Args&&... args)
			{
				return fn(args...);
			}

			//ポインターを使用し関数オブジェクトにアクセスする
			template<class MT_Fn = T_Fn_Action, is_invalid_not MT_pointer = T_pointer, class... T_Args>
				requires requires
			{
				requires std::is_member_function_pointer_v<MT_Fn>;
			}
			constexpr auto operator()(T_Args&&... args)
			{
				return (p->*fn)(args...);
			}

			//ポインターを引数に追加し、[Function]にアクセスする
			template<class MT_Fn = T_Fn_Action, is_invalid_not MT_pointer = T_pointer, class... T_Args>
				requires requires
			{
				requires same_as_template_type<MT_Fn, Function>;
			}
			constexpr auto operator()(T_Args&&... args)
			{
				return fn(p,args...);
			}

		};

		//仕様
		//生成するクラス[T_Fn]型の変数を生成する。
		// [T_Fn*]の場合はインスタンス生成を実施する。
		template<class T_Fn>
		struct S_Class_Create
		{
			constexpr S_Class_Create() {}

			//クラスの生成
			template<class MT_Fn = T_Fn,class... T_Args>
			constexpr auto operator()(T_Args&&... args)
			{
				return T_Fn{args... };
			}

			//クラスのインスタンス生成
			template<class MT_Fn = T_Fn, class... T_Args>
				requires requires
			{
				requires is_pointer<MT_Fn>;
			}
			constexpr auto operator()(T_Args&&... args)
			{
				return new std::remove_pointer_t<T_Fn>{ args... };
			}

		};

		//仕様
		//配列に要素を追加する。
		template<class T,size_t t_dimension>
		struct S_Array_Create
		{
			T* array_p ;

			constexpr S_Array_Create(T* set_array_p) :
				array_p(set_array_p){}


			//配列への複数の要素を追加
			template<class T_Flont_Args, class... T_Args>
			constexpr void operator()(T_Flont_Args&& flont_Args, T_Args&&... args)
			{
				operator()(std::forward<T_Flont_Args>(flont_Args));
				++array_p;
				this->operator()(std::forward<T_Args>(args)...);
			}

			//配列への要素追加
			template<class T_Flont_Args>
			constexpr void operator()(T_Flont_Args&& flont_Args)
			{
				*array_p = static_cast<T>(flont_Args);
			}
		};


		//仕様
		//型の判定が終了する際に呼び出される
		template<class T_Request_Types = invalid_t,class ...Ts>
		struct S_Result
		{
			using chack = T_Request_Types;

			using convert = S_Result;

			template<class ...T_Args>
			static constexpr auto Convert(auto* fn, T_Args&&... args)
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
		struct S_Function_Args_Chack
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
			S_Function_Args_Chack<T_Request_Types_Tuple, T_Set_Types_Tuple,
			std::constructible_from<std::remove_reference_t<typename T_Request_Types_Tuple::type>, typename T_Set_Types_Tuple::type, T_Set_Types...> ||
			std::constructible_from<std::remove_pointer_t<typename T_Request_Types_Tuple::type>, typename T_Set_Types_Tuple::type, T_Set_Types...>,
			is_invalid_not<typename N_Tuple::S_Parameter<typename T_Set_Types_Tuple::type>::tuple>,
			typename T_Set_Types_Tuple::type, T_Set_Types...>;



		template<class T_Request_Types_Tuple,
			class T_Set_Types_Tuple,
			bool t_constructible_from,
			bool T_Set_Types_Expand>
			requires (is_invalid<typename T_Set_Types_Tuple::type>)
		struct S_Function_Args_Chack<T_Request_Types_Tuple, T_Set_Types_Tuple, t_constructible_from, T_Set_Types_Expand,
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
		struct S_Function_Args_Chack<T_Request_Types_Tuple, T_Set_Types_Tuple, false, false,
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
		struct S_Function_Args_Chack<T_Request_Types_Tuple, T_Set_Types_Tuple, true, T_Set_Types_Expand,
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
			template<class T = typename S_Function_Args_Chack<T_Request_Types_Tuple, T_Set_Types_Tuple, false, T_Set_Types_Expand,
				T_Set_Types...>::type::chack>
			struct S_last_args_chack
			{
				using type = typename S_Function_Args_Chack<T_Request_Types_Tuple, T_Set_Types_Tuple, false, T_Set_Types_Expand,
					T_Set_Types...>::type;
			};

			template<>
			struct S_last_args_chack<invalid_t>
			{
				using type = S_Function_Args_Chack;
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
				requires (sizeof...(T_Set_Types) > 1) && (!class_create_fg)
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
				static constexpr auto Convert(auto* fn, T_Converted&&... converted_args, T_Set_Types&&... args, T_back_args&&... back_args)
				{
					return next::convert::Convert(
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
				static constexpr auto Convert(auto* fn, T_Converted&&... converted_args, T_Set_Types&&... args, T_back_args&&... back_args)
				{

					//ポインターを返す為の一時オブジェクト
					std::remove_pointer_t<typename T_Request_Types_Tuple::type> temp(std::forward<T_Set_Types>(args)...);

					return next::convert::Convert(
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
		struct S_Function_Args_Chack<T_Request_Types_Tuple, T_Set_Types_Tuple, false, true,
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
			using type = S_Function_Args_Chack;

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
				static constexpr auto Convert(auto* fn,T_Converted&&... args, T_FronT_Set_Types&& change_args, T_back_args&&... back_args)
				{
					return Convert<typename T_expand_Numbers::remove>(
						fn,
						std::forward<T_Converted>(args)...,
						std::forward<T_FronT_Set_Types>(change_args),
						get<T_expand_Numbers::value>(std::forward<T_FronT_Set_Types>(change_args)),
						std::forward<T_back_args>(back_args)...);
				}

				//仕様
				//引数[change_args]の展開が終わった場合、次の工程に進める
				template<same_as<tuple_v<>> T_expand_Numbers = T_index_sequence, class ...T_back_args>
				static constexpr auto Convert(auto* fn,T_Converted&&... args, T_FronT_Set_Types&& change_args, T_back_args&&... back_args)
				{
					return next::convert::Convert(
						fn,
						std::forward<T_Converted>(args)...,
						std::forward<T_back_args>(back_args)...);
				}

			};

			using convert = S_Convert<>;
		};


		using next = U_Function_Args_Chack_Next<
			typename S_Request<>::args::reverse,
			typename tuple_t<T_Set_Types...>::reverse::create_p>::type;

		using chack = next::chack;

	public:

		using type = chack;

		//仕様
		//型[fn]に対して、要求するに[args...] を一対多、多対一の変換を行い、
		// [fn]のコンストラクタを実行する(生成する)。
		template<class T_Create_class = T_Fn, class ...T_Args>
			requires class_create_fg
		static constexpr auto Convert(T_Args&&... args)
		{
			S_Class_Create<T_Create_class> fn_action = {};
			return next::convert::Convert(&fn_action, std::forward<T_Args>(args)...);
		}

		//仕様
		//配列型のポインター[array_p]に[T_Fn]の0次元目の要素数を追加する。
		template<class T_Array, class ...T_Args>
			requires !class_create_fg
		static constexpr auto Convert(T_Array* array_p, T_Args&&... args)
		{
			S_Array_Create<T_Array, std::extent_v<T_Fn,0>> fn_action = { array_p };
			return next::convert::Convert(&fn_action, std::forward<T_Args>(args)...);
		}

		//仕様
		//関数[fn]に対して、要求するに[args...] を一対多、多対一の変換を行い、
		// [fn]を実行する
		template<class ...T_Args>
			requires !class_create_fg
		static constexpr auto Convert(T_Fn&& fn,T_Args&&... args)
		{
			S_Fn_Action fn_action(fn, &invalid);
			return next::convert::Convert(&fn_action,std::forward<T_Args>(args)...);
		
		}

		//仕様
		//関数[fn]に対して、要求するに[args...] を一対多、多対一の変換を行い、
		// ポインターを用いて[fn]を実行する
		template<class ...T_Args>
			requires !class_create_fg
		static constexpr auto Convert(T_Fn&& fn,S_Request<>::pointer* p,T_Args&&... args)
		{
			S_Fn_Action fn_action(fn, p);
			return next::convert::Convert(&fn_action,std::forward<T_Args>(args)...);
		}



	};




	//仕様
	//関数[fn]に対して、
	// [args...]の中身を適切に展開し、実行する
	template<class T_Fn, class ...T_Args>
		requires requires
	{
		requires is_invalid_not<typename I_Convert_Action<T_Fn, T_Args...>::type>;
		requires (!I_Convert_Action<T_Fn, T_Args...>::class_create_fg);
	}
	static constexpr auto Apply(T_Fn&& fn, T_Args&&... args)
	{
		return I_Convert_Action<T_Fn, T_Args...>::Convert(
			std::forward<T_Fn>(fn),
			std::forward<T_Args>(args)...);
	}


	//仕様
	//関数[fn]に対して、
	//ポインタ[p]を用いて、[args...]の中身を適切に展開し、実行する
	template<class T_Fn,class ...T_Args>
		requires requires
	{
		requires is_invalid_not<typename I_Convert_Action<T_Fn, T_Args...>::type>;
		requires (!I_Convert_Action<T_Fn, T_Args...>::class_create_fg);
	}
	static constexpr auto Apply(T_Fn&& fn, auto* p, T_Args&&... args)
	{
		return I_Convert_Action<T_Fn, T_Args...>::Convert(
			std::forward<T_Fn>(fn),
			p,
			std::forward<T_Args>(args)...);
	}


	//仕様
	//クラス[T]のコンストラクタに対して、
	//[args...]の中身を適切に展開し、実行する
	template<class T, class ...T_Args>
		requires requires
	{
		requires std::is_class_v<T>;
		requires is_invalid_not<typename I_Convert_Action<T, T_Args...>::type>;
		requires I_Convert_Action<T, T_Args...>::class_create_fg;
	}
	static constexpr auto Apply(T_Args&&... args)
	{
		return I_Convert_Action<T, T_Args...>::Convert(
			std::forward<T_Args>(args)...);
	};

	//仕様
	//クラス[T]のコンストラクタに対して、
	//[args...]の中身を適切に展開し、Newする
	template<class T, class ...T_Args>
		requires requires
	{
		requires is_pointer<T>;
		requires std::is_class_v<std::remove_pointer_t<T>>;
		requires is_invalid_not<typename I_Convert_Action<T, T_Args...>::type>;
		requires I_Convert_Action<T, T_Args...>::class_create_fg;
	}
	static constexpr auto Apply(T_Args&&... args)
	{
		return I_Convert_Action<T, T_Args...>::Convert(
			std::forward<T_Args>(args)...);
	}


	//仕様
	//配列型の参照に[array_ref]に[args...]の中身を適切に展開し、追加する。
	// 
	// 引数
	// [array_ref]：要素を格納する配列の参照
	// [args...]：tupleにより適切に変換され、配列に格納する変数
	template<class T_Array, size_t N, class ...T_Args>
		requires requires
	{
		requires is_invalid_not<typename I_Convert_Action<T_Array, T_Args...>::type>;
		requires !I_Convert_Action<T_Array, T_Args...>::class_create_fg;
	}
	static constexpr auto Apply(T_Array(&array_ref)[N], T_Args&&... args)
	{
		return I_Convert_Action<T_Array[N], T_Args...>::Convert(&array_ref,
			std::forward<T_Args>(args)...);
	}

	//仕様
	//特定の要素を指す、配列型のポインター[array_p]に[set_Num]の数だけ[args...]の中身を適切に展開し、追加する。
	//
	//テンプレート
	//[set_Num]：要素を追加する総数
	// 
	// 引数
	// [array_p]：配列の特定の要素を指すポインター
	// [args...]：tupleにより適切に変換され、配列に格納する変数
	// 
	//補足
	// [array_p] について
	// [int n[5] ]という配列がある時
	// [int* p = &n[2]; ]pが特定の要素数(二番目)を指す事になる。
	template<size_t set_Num,class T_Array,class ...T_Args>
		requires requires
	{
		requires is_invalid_not<typename I_Convert_Action<T_Array, T_Args...>::type>;
		requires !I_Convert_Action<T_Array, T_Args...>::class_create_fg;
	}
	static constexpr void Apply(T_Array* array_p, T_Args&&... args)
	{
		return I_Convert_Action<T_Array[set_Num], T_Args...>::Convert(array_p ,
			std::forward<T_Args>(args)...);
	}

}