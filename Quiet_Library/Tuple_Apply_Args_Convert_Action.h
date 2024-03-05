/*!
 * Tuple_Apply_Args_Convert_Action.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Output_Message.h"

#include"Tuple_Declare.h"
#include"Tuple_Apply_Type_Chack.h"

namespace quiet::N_Tuple::N_Apply
{

	template<class T_Expand, size_t t_point>
	struct S_Conversion_Expand
	{
		using type = T_Expand;

		static constexpr size_t point = t_point;
		static constexpr size_t expand_size = S_Parameter<T_Expand>::size;
	};

	template<class T_Zip, size_t t_point>
	struct S_Conversion_Zip
	{
		using type = T_Zip;

		static constexpr size_t point = t_point;

		static constexpr size_t zip_size = S_Parameter<T_Zip>::size;
	};


	template<class T_Request_Types_Tuple,
		class T_Set_Types_Tuple>
	struct I_Convert_Order;

	//仕様
	//供給する型のリストから、要求する型のリストに、型の展開を伴い変換を出来るか判定する。
	//
	//補足
	// 型の判定は後ろから実施する。
	template<class T_Request_Types_Tuple,
		class T_Args_Types_Tuple>
	struct I_Args_Convert_Action
	{
	private:

		using conversion = I_Convert_Order<
			typename S_Infinite_Args_Conversion<T_Request_Types_Tuple, T_Args_Types_Tuple>::type,T_Args_Types_Tuple>::type;

		using conversion_expand_list = conversion::conversion_expand_list;

		using conversion_zip_list = conversion::conversion_zip_list;


		template<class T_Args_Types_list,
			class T_Args_Zip_Order_List = conversion_zip_list>
		struct I_Args_Zip;


		template<
			class T_Args_Types_list = T_Args_Types_Tuple,
			class T_Args_Expand_Order_List = conversion_expand_list>
		struct I_Args_Expand
		{

			//仕様
			//互換性のある型に展開する
			// [using tuple}にて定義される型
			template<class T_Tuple>
			using expand = N_Tuple::S_Parameter<T_Tuple>::tuple;

			//仕様
			//選択中のタイプを展開する
			template<class T_Types_Tuple>
			using select_type_expand = N_Tuple::U_Insert_tuple_expand<
				typename T_Types_Tuple::remove,
				expand<typename T_Types_Tuple::type>>;

			using convert_order = T_Args_Expand_Order_List::type;

			using expand_type_select = U_Select<T_Args_Types_list::size - convert_order::point, T_Args_Types_list>;

			template<class T_expand_Numbers = U_index_sequence<convert_order::expand_size>,
				class T_Expand_Type_Select = expand_type_select>
			struct S_Args_Expand;

			template<
				size_t... t_Expand_Number,
				class ...T_Flont_Args_Types, class T_Args, class ...T_Back_Args_Types>
				requires(T_Args_Types_list::size >= 0)
			struct S_Args_Expand<
				tuple_v<t_Expand_Number...>,
				tuple_tp<tuple_t<T_Flont_Args_Types...>, T_Args, tuple_t<T_Back_Args_Types...>> >
			{
				using type = I_Args_Expand<
					select_type_expand<expand_type_select>,
					typename T_Args_Expand_Order_List::remove>::type;

				template<size_t t_select_number>
				using select_type = N_Tuple::U_Element_t<t_select_number, T_Args_Types_list>;

				//仕様
				//[change_args]の[t_select_number]番目の変数をユニバーサル参照で取得する
				template<size_t t_select_number>
				static constexpr auto&& get(auto& change_args)
				{
					return std::get<t_select_number>(change_args);
				}

				//仕様
				//[change_args]の[t_select_number]番目の変数をポインターで取得する
				template<size_t t_select_number>
					requires is_pointer<select_type<t_select_number>>
				static constexpr auto* get(auto& change_args)
				{
					return &std::get<t_select_number>(change_args);
				}

				static constexpr auto Apply(auto* fn,
					T_Flont_Args_Types&&... front_args,
					T_Args&& args,
					T_Back_Args_Types&&... back_args)
				{
					return type::Apply(fn,
						std::forward<T_Flont_Args_Types>(front_args)...,
						std::move(get<t_Expand_Number>(args))...,
						std::forward<T_Back_Args_Types>(back_args)...);
				}


			};

			using type = S_Args_Expand<>;

		};

		template<class T_Args_Types_list, class T_Args_Expand_Order_List>
			requires requires
		{
			requires same_as< T_Args_Expand_Order_List, tuple_t<>>;
		}
		struct I_Args_Expand<T_Args_Types_list, T_Args_Expand_Order_List>
		{
			using type = I_Args_Zip<T_Args_Types_list>::type;
		};

		template<class T_Args_Types_list,
			class T_Args_Zip_Order_List>
		struct I_Args_Zip
		{
			template<class T_Args_Zip_Order_List = T_Args_Zip_Order_List>
			struct I_Zip_Order_Part_Division
			{

				using zip_order = T_Args_Zip_Order_List::type;

				template<class T_Args_Zip_Order_List, size_t t_end_back_args_point, class ...T_Division_Args_Zip_Order>
				struct S_Zip_Order_Part_Division
				{
					using type = S_Zip_Order_Part_Division;

					using first_order_part = tuple_t<T_Division_Args_Zip_Order...>;

					using rest_order_part = T_Args_Zip_Order_List;

				};

				template<class T_Front_Args_Zip_Order, class ...T_Args_Zip_Order, size_t t_end_back_args_point, class ...T_Division_Args_Zip_Order>
					requires requires
				{
					requires T_Front_Args_Zip_Order::point < t_end_back_args_point;
				}
				struct S_Zip_Order_Part_Division<tuple_t<T_Front_Args_Zip_Order, T_Args_Zip_Order...>, t_end_back_args_point, T_Division_Args_Zip_Order...>
				{
					using type = S_Zip_Order_Part_Division<tuple_t<	T_Args_Zip_Order...>,
						t_end_back_args_point + T_Front_Args_Zip_Order::zip_size - 1,
						T_Front_Args_Zip_Order,
						T_Division_Args_Zip_Order...>::type;
				};

				using zip_order = T_Args_Zip_Order_List::type;

				using type = S_Zip_Order_Part_Division<typename T_Args_Zip_Order_List::remove,
					zip_order::point + zip_order::zip_size, zip_order>::type;
			};



			using first_order = T_Args_Zip_Order_List::type;

			template<
				class T_Flont_Args_Number = U_index_sequence<T_Args_Types_list::size - (first_order::point + first_order::zip_size - 1)>,
				class T_Zip_Args_Numebr = U_Template_Calculate_plus<U_index_sequence<first_order::zip_size>, T_Args_Types_list::size - (first_order::point + first_order::zip_size - 1)>,

				class T_Back_Args_Number = U_Template_Calculate_plus <U_index_sequence <first_order::point - 1>
				, T_Flont_Args_Number::size + T_Zip_Args_Numebr::size>, 

				class T_Zip_Args = typename S_Parameter<typename first_order::type>::tuple
			>
			struct S_Args_Zip;


			template<size_t ...t_Flont_Args_Number,
				size_t ...t_Zip_Args_Number,
				size_t ...t_Back_Args_Number,
				class ...T_Zip_Args
			>
			struct S_Args_Zip<tuple_v<t_Flont_Args_Number...>, tuple_v<t_Zip_Args_Number...>, tuple_v<t_Back_Args_Number...>, tuple_t<T_Zip_Args...>>
			{
				using type = I_Args_Zip<
					tuple_t<
					U_Element_t<t_Flont_Args_Number, T_Args_Types_list>...,
					typename first_order::type,
					U_Element_t<t_Back_Args_Number, T_Args_Types_list>...>,
					typename T_Args_Zip_Order_List::remove>::type;

				//仕様
				//[T_Request_Type]型を[args...]から作り、そのポインターを返す
				//
				//補足
				//ここで生成される変数は、変数[args...]を元に生成されるだけであり、変数に[&][*]が付与されていた場合も、
				// 生成するクラス内で個別に置換しない場合、生成されるクラスから、変数[args...]にはアクセスされない。
				//[T_Request_Type]型を[args...]から作り、そのポインターを返す
				template<class T_Order_Type = typename first_order::type>
					requires requires
				{
					requires is_pointer<T_Order_Type>;
				}
				static constexpr auto Apply(auto* fn,
					U_Element_t<t_Flont_Args_Number, T_Args_Types_list>&&... front_args,
					U_Element_t<t_Zip_Args_Number, T_Args_Types_list> &&... zip_args,
					U_Element_t<t_Back_Args_Number, T_Args_Types_list>&&... back_args)
				{

					//ポインターを返す為の一時オブジェクト
					std::remove_pointer_t<typename first_order::type> temp{ static_cast<T_Zip_Args>(std::forward<U_Element_t<t_Zip_Args_Number, T_Args_Types_list>>(zip_args))... };

					return type::Apply(fn,
						std::forward<U_Element_t<t_Flont_Args_Number, T_Args_Types_list>>(front_args)...,
						&temp,
						std::forward<U_Element_t<t_Back_Args_Number, T_Args_Types_list>>(back_args)...);
				}


				//仕様
				//[T_Request_Type]型を[args...]から作り、その参照を返す
				//
				//補足
				//ここで生成される変数は、変数[args...]を元に生成されるだけであり、変数に[&][*]が付与されていた場合も、
				// 生成するクラス内で個別に置換しない場合、生成されるクラスから、変数[args...]にはアクセスされない。
				//[T_Request_Type]型を[args...]から作り、その実体を返す
				template<class T_Order_Type = typename first_order::type>
					requires requires
				{
					requires is_reference<T_Order_Type>;
				}
				static constexpr auto Apply(auto* fn,
					U_Element_t<t_Flont_Args_Number, T_Args_Types_list>&&... front_args,
					U_Element_t<t_Zip_Args_Number, T_Args_Types_list>&&... zip_args,
					U_Element_t<t_Back_Args_Number, T_Args_Types_list>&&... back_args)
				{
					//参照を返す為の一時オブジェクト
					std::remove_pointer_t<typename first_order::type> temp{ static_cast<T_Zip_Args>(std::forward<U_Element_t<t_Zip_Args_Number, T_Args_Types_list>>(zip_args))... };

					return type::Apply(fn,
						std::forward<U_Element_t<t_Flont_Args_Number, T_Args_Types_list>>(front_args)...,
						&temp,
						std::forward<U_Element_t<t_Back_Args_Number, T_Args_Types_list>>(back_args)...);
				}

				//仕様
				//[T_Request_Type]型を[args...]から作り、その実体を返す
				static constexpr auto Apply(auto* fn,
					U_Element_t<t_Flont_Args_Number, T_Args_Types_list>&&... front_args,
					U_Element_t<t_Zip_Args_Number, T_Args_Types_list>&& ... zip_args,
					U_Element_t<t_Back_Args_Number, T_Args_Types_list>&&... back_args)
				{
					//C_OUT(t_Flont_Args_Number...);
					//C_OUT(t_Zip_Args_Number...);
					//C_OUT(t_Back_Args_Number...);
					//TYPE_ID(2, tuple_v< t_Flont_Args_Number...>);
					//TYPE_ID(2, tuple_v< t_Zip_Args_Number...>);
					//TYPE_ID(2, tuple_v< t_Back_Args_Number...>);
					//TYPE_ID(2,T_Args_Types_list);
					//std::cout << std::endl;

					return type::Apply(fn,
						std::forward<U_Element_t<t_Flont_Args_Number, T_Args_Types_list>>(front_args)...,
						typename first_order::type{ static_cast<T_Zip_Args>(std::forward<U_Element_t<t_Zip_Args_Number, T_Args_Types_list>>(zip_args))... },
						std::forward<U_Element_t<t_Back_Args_Number, T_Args_Types_list>>(back_args)...);
				
				}

			};


			using type = S_Args_Zip<>;

		};

		template<class T_Args_Types_list>
		struct I_Args_Zip<T_Args_Types_list, tuple_t<>>
		{
			using type = I_Args_Zip;

			template<class ...T_Args>
			static constexpr auto Apply(auto* fn, T_Args&&... args)
			{
				return fn->Apply(std::forward<T_Args>(args)...);
			}

		};

	public:

		using type = I_Args_Expand<>::type;

	};

}




