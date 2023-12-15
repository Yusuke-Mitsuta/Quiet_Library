#pragma once

#include"Tuple.h"
#include"Concept.h"

template<class T_Flont_Parts, class ...T_Parts>
class Function;

namespace N_Function
{
	template<class ...T_Parts>
	struct Function_Core;

	//�d�l
	//�֐��I�u�W�F�N�g�̌^�ɑ΂��āA���������̌^���L�������肷��B
	//
	//�e���v���[�g
	//[T_Fn_Parts...]::
	// �������͑������̌Ăяo���Ɏg�p����N���X�|�C���^�[�̌^�ł���B�N���X�|�C���^�[�̌^�𔻒肵�Ȃ��ꍇ�͎w��s�v�ł���B�ÓI���\�b�h�A�N���X�|�C���^�[�̌^���w��ς݁A�̏ꍇ�͎w��s�ł���B
	// �������͊֐��̌^�A�Ⴕ���́A������bind�����^[Function_Core],[Method_Core]�Ƃ���
	// ��O�����ȍ~�́A�������̊֐��I�u�W�F�N�g�̈����Ɏw�肷��^���X�g
	template<class ...T_Fn_Parts>
	struct I_Function_Base_Data
	{
		
		//�d�l
		//�֐��I�u�W�F�N�g��[T_Fn_Parts...]���ɑ��݂��Ȃ��ꍇ
		template<class ...T_Fn_Parts>
		struct S_Function_Data
		{
			using function = invalid_t;
			using bind_args = invalid_t;
			using pointer = invalid_t;
			using c_name = invalid_t;
			using r_type = invalid_t;

		};

		//�d�l
		//���ʂŎg�p����|�C���^�[�̌^���Z�b�g����
		template<class T_Dedicated_Point, class ...T_Fn_Parts>
			requires (std::is_class_v<T_Dedicated_Point>)
		struct S_Function_Data<T_Dedicated_Point*, T_Fn_Parts...> :
			S_Function_Data<T_Fn_Parts...>
		{
			using pointer = T_Dedicated_Point;
		};

		//�d�l
		//�����̌^���Z�b�g����
		template<class T_Fn, class ...T_Bind_Args>
		struct S_Function_Data<T_Fn,T_Bind_Args...> :
			S_Function_Data<T_Fn>
		{
			using bind_args = tuple_t<T_Bind_Args...>;
		};


		//�d�l
		//�N���X���\�b�h�̌^����A�e��p�����[�^���Z�b�g����
		template<class T_CName, class T_RType, class ...T_Args>
		struct S_Function_Data<T_RType(T_CName::*)(T_Args...)> :
			S_Function_Data<>
		{
			using function = T_RType(T_CName::*)(T_Args...);

			using c_name = T_CName;

			using r_type = T_RType;
		};

		//�d�l
		//�ÓI�֐��̌^����A�e��p�����[�^���Z�b�g����
		template<class T_RType, class ...T_Args>
		struct S_Function_Data<T_RType(*)(T_Args...)> :
			S_Function_Data<>
		{
			using function = T_RType(*)(T_Args...);

			using r_type = T_RType;
		};


		//�d�l
		//�e�ƂȂ�֐��I�u�W�F�N�g�̌^���Z�b�g����
		template<class ...T_Parts>
		struct S_Function_Data<Function<T_Parts...>> :
			S_Function_Data<typename I_Function_Multiple_Helper<T_Parts...>::type>
		{


			template<class T_Tuple_Parts =tuple_t<T_Parts...>,
				class T_Access_Numbers = typename I_Function_Multiple_Helper<T_Parts...>::access_number, 
				class T_Result =tuple_t<>>
			struct S_Fn_Search
			{
				using type = invalid_t;
			};

			template<class T_Access_Number, class ...T_Result>
			struct S_Fn_Search<tuple_t<>, T_Access_Number, tuple_t<T_Result...>>
			{
				using type = Function_Core<T_Result...>;
			};

			template<class T_Flont_Parts, class ...T_Parts, class T_Access_Number, class ...T_Result>
				requires requires
			{
				requires T_Access_Number::size == 0;
			} ||
				(requires
			{
				requires T_Access_Number::type::value < sizeof...(T_Result);
				requires T_Access_Number::type::value != 0;
			} || 
				requires
			{
				requires T_Access_Number::type::next_v < sizeof...(T_Result);
				requires T_Access_Number::type::value == 0;
			})
			struct S_Fn_Search<tuple_t<T_Flont_Parts, T_Parts...>, T_Access_Number, tuple_t<T_Result...>>

			{
				using type = S_Fn_Search<tuple_t<T_Parts...>, T_Access_Number, tuple_t<T_Result..., T_Flont_Parts>>::type;
			};


			template<class T_Flont_Parts, class ...T_Parts, class T_Flont_Access_Number, class ...T_Access_Numbers, class ...T_Result>
				requires requires
			{
				requires T_Flont_Access_Number::value == sizeof...(T_Result);
			}
			struct S_Fn_Search<tuple_t<T_Flont_Parts, T_Parts...>, tuple_t<T_Flont_Access_Number, T_Access_Numbers...>, tuple_t<T_Result...>>

			{
				using type = S_Fn_Search<tuple_t<T_Parts...>, tuple_t<T_Access_Numbers...>, tuple_t<T_Result..., T_Flont_Parts>>::type;
			};


			template<class ...T_Flont_Parts, class ...T_Parts, class T_Flont_Access_Number, class ...T_Access_Numbers, class ...T_Result>
				requires requires
			{
				requires  std::is_pointer_v<typename tuple_t<T_Result...>::back_t>;
				requires T_Flont_Access_Number::next_v == sizeof...(T_Result);
			} ||
				requires
			{
				requires T_Flont_Access_Number::value == sizeof...(T_Result);
			}
			struct S_Fn_Search<tuple_t<Function<T_Flont_Parts...>, T_Parts...>, tuple_t<T_Flont_Access_Number, T_Access_Numbers...>, tuple_t<T_Result...>>

			{
				using type = S_Fn_Search<tuple_t<T_Parts...>, tuple_t<T_Access_Numbers...>,
					tuple_t<T_Result..., typename S_Function_Data<Function<T_Flont_Parts...>>::function>>::type;
			};

			//using function = S_Fn_Search<>::type;

		};


		//�d�l
		//�e�ƂȂ�֐��I�u�W�F�N�g�̌^���Z�b�g����
		template<class ...T_Parts>
		struct S_Function_Data<Function_Core<T_Parts...>> :
			S_Function_Data<>
		{
			using function = Function_Core<T_Parts...>;
		};

		template<class ...T_Fns>
		struct S_Function_Data<tuple_t<T_Fns...>> :
			S_Function_Data<>
		{
			using function = tuple_t<T_Fns...>;
		
		};

		//�d�l
		//�֐��I�u�W�F�N�g�̌^�łȂ��ꍇ�A�Z�b�g���Ȃ�
		template<class T_Fn>
		struct S_Function_Data<T_Fn> :
			S_Function_Data<>
		{};

	public:
		
		using type = S_Function_Data<T_Fn_Parts...>;

protected:

		struct I_Core_Molding
		{
			template<class T_Core, class T_Add>
			struct S_Add_p
			{
				using type = T_Core;
			};

			template<class ...T_Parts, not_is_invalid T_Add>
			struct S_Add_p<Function_Core<T_Parts...>, T_Add>
			{
				using type = Function_Core<T_Add, T_Parts...>;
			};

			template<class T_Core, class T_Add>
			struct S_Add_fn
			{
				using type = T_Core;
			};

			template<class ...T_Parts,not_is_invalid T_Add>
			struct S_Add_fn<Function_Core<T_Parts...>,T_Add>
			{
				using type = Function_Core<T_Add,T_Parts...>;
			};

			template<class T_Bind_Args = typename type::bind_args>
			struct S_Add_bind_args
			{
				using type = Function_Core<>;
			};

			template<class ...T_Bind_Args >
			struct S_Add_bind_args<tuple_t<T_Bind_Args...>>
			{
				using type = Function_Core<T_Bind_Args...>;
			};

			using type = S_Add_p<typename S_Add_fn<typename S_Add_bind_args<>::type,
				typename type::function>::type,typename type::pointer>::type;


		};

	public:

		using core = I_Core_Molding::type;

	};

}

