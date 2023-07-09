#pragma once
#include"Function_BindFn.h"
#include"tuple_convertible_to.h"
#include"Tuple_Unzip.h"
#include<tuple>
#include<optional>

namespace N_Function
{
	//�d�l
	//�֐��|�C���^�[�ɑ΂��āA�����̒l�����������A�����v�Ŕ��肷��
	//
	//�e���v���[�g
	//T_Fn_Args::�֐��|�C���^�[�A�w�肷������A��Tuple
	//
	//�⑫
	//T_Fn_Args�͊֐��|�C���^�[�A����Ɏw�肷������A���̊֐��|�C���^�[�A�ƂȂ�悤�ɂ��鎖
	template<class T_Fn_Args>
	struct IS_BindArgs
	{
		friend class IS_BindArgs;
	private:

		template<int _Index>
		using tuple_element = std::tuple_element<(std::tuple_size<T_Fn_Args>::value + _Index) % std::tuple_size<T_Fn_Args>::value, T_Fn_Args>::type;

		//�d�l
		//�����̃o�C���h�ς݊֐��|�C���^�[���i�[���A�Ō�̊֐��Ȃ�i�[�������I������
		//
		//�e���v���[�g
		//t_MethodNumber::���݊i�[�����֐��̔ԍ�
		//t_RemainingAmount::�c���T_Fn_Args�̐�
		//...T_Bounds::�����̃o�C���h�ς݊֐��|�C���^�[
		//�⑫
		//T_Fn_Args����납��m�F���A���Ƀo�C���h�ς݊֐��̑O�Ɋi�[���Ă䂭
		template<int t_MethodNumber,int t_RemainingAmount = t_MethodNumber,class ...T_Bounds>
		struct S_BoundArgs
		{
			template<class T_Args, int t_NextNumber, class ...T_NewSetArgs>
			struct S_BindArgs
			{
				using Type = S_BindArgs<tuple_element<t_NextNumber - 1>, t_NextNumber - 1, T_Args, T_NewSetArgs...>::Type;

				static auto Bind(T_Fn_Args&& t_Fn_Args)
				{
					C_OUT("TEST");
					return 0;
				}
			};

			//�d�l
			//�֐��|�C���^�[�ɑ΂��Ĉ������Z�b�g����
			template<class C_Name, class R_Type, class ...T_Args, int t_NextNumber, class ...T_NewSetArgs>
			struct S_BindArgs<R_Type(C_Name::*)(T_Args...), t_NextNumber, T_NewSetArgs...>
			{
				//�d�l
				//�����������v���邩���肷��
				static constexpr bool Judge = tuple_back_part_convertible_to<std::tuple<T_NewSetArgs...>, std::tuple<T_Args...>>;

				//�d�l
				//�����������v���Ȃ��A�Ⴕ���͍Ō�̊֐��Ȃ�i�[���I���Ɉڍs����
				//��v����Ȃ�A�i�[���p������
				using Type = S_BoundArgs<t_NextNumber*Judge, t_NextNumber,S_Address<R_Type(C_Name::*)(T_Args...), std::tuple<T_NewSetArgs...>>,T_Bounds...>::Type;
			};

			//�d�l
			//S_Address�ɑ΂��Ĉ������Z�b�g����
			template<class C_Name, class R_Type, class ...T_Args, class ...T_DefaultSetArgs, int t_NextNumber, class ...T_NewSetArgs>
			struct S_BindArgs<S_Address<R_Type(C_Name::*)(T_Args...), std::tuple<T_DefaultSetArgs...>>, t_NextNumber, T_NewSetArgs...>
			{	
				//�d�l
				//�����������v���邩���肷��
				static constexpr bool Judge = tuple_back_part_convertible_to<std::tuple<T_NewSetArgs..., T_DefaultSetArgs...>, std::tuple<T_Args...>>;

				//�d�l
				//�����������v���Ȃ��A�Ⴕ���͍Ō�̊֐��Ȃ�i�[���I���Ɉڍs����
				//��v����Ȃ�A�i�[���p������
				using Type = S_BoundArgs<t_NextNumber*Judge,t_NextNumber,S_Address<R_Type(C_Name::*)(T_Args...), std::tuple<T_NewSetArgs...,T_DefaultSetArgs...>>, T_Bounds...>::Type;
			};


		public:
			//�d�l
			//�������W�߁A�֐��|�C���^�[�Ɋi�[����
			using Type = S_BindArgs<tuple_element<t_MethodNumber - 1>, t_MethodNumber - 1>::Type;


			static auto Bind(T_Fn_Args&& t_Fn_Args)
			{
				C_OUT("TEST");
				return 0;
			}


		};

	public:

		//�d�l
		//�i�[�̌��ʂ�����
		template<int t_RemainingAmount ,class ...T_Bounds>
		struct S_BoundArgs<0,t_RemainingAmount,T_Bounds...>
		{
			using Type = S_BoundArgs;

			//�d�l
			//�i�[���ꂽS_Address��tuple��Ԃ�
			using Fns = std::tuple<T_Bounds...>;

			//�d�l
			//Fns������Ɋi�[���ꂽ����Ԃ�
			using Judge = std::bool_constant<!(t_RemainingAmount)>;
		};

		using BoundArgs = S_BoundArgs<std::tuple_size<T_Fn_Args>::value>;

		//�d�l
		//�֐��|�C���^�[�ɑ΂��āA�����̒l�����������A�����v�Ŕ��肷��
		using Type = BoundArgs::Type;

		//T_Fn_Args fns;

		template<class MT_Fn_Args>
		constexpr IS_BindArgs(MT_Fn_Args& t_Fn_Args)
		{
			auto a= IS_BindArgs<MT_Fn_Args>::S_BoundArgs<std::tuple_size<MT_Fn_Args>::value>::Bind(std::forward<MT_Fn_Args>(t_Fn_Args));
		}
	};

	template<class MT_Fn_Args>
	IS_BindArgs(MT_Fn_Args& t_Fn_Args) -> IS_BindArgs<typename IS_BindArgs<typename IS_TupleUnzip<MT_Fn_Args>::Type>::Type::Fns>;
	


}