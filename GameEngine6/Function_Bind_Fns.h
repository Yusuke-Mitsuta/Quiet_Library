#pragma once
//#include"Function_BindFn.h"
#include"tuple_convertible_to.h"
#include"Tuple_Unzip.h"
#include"Function.h"
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
	struct IS_BindFns
	{
		friend struct IS_BindFns;
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
		struct S_BoundFns
		{
			template<class T_Args, int t_NextNumber, class ...T_NewSetArgs>
			struct S_BindFns
			{
				using Type = S_BindFns<tuple_element<t_NextNumber - 1>, t_NextNumber - 1, T_Args, T_NewSetArgs...>::Type;

				static auto Bind(T_Fn_Args&& t_Fn_Args)
				{
					C_OUT("TEST")
					return 0;
				}
			};

			//�d�l
			//�֐��|�C���^�[�ɑ΂��Ĉ������Z�b�g����
			template<class C_Name, class R_Type, class ...T_Args, int t_NextNumber, class ...T_NewSetArgs>
			struct S_BindFns<R_Type(C_Name::*)(T_Args...), t_NextNumber, T_NewSetArgs...>
			{
				using T_Fn = R_Type(C_Name::*)(T_Args...);
				//�d�l
				//�����������v���邩���肷��
				using Fn = IS_BindFn<Function<T_Fn, T_NewSetArgs...>>::Type;
				//�d�l
				//�����������v���Ȃ��A�Ⴕ���͍Ō�̊֐��Ȃ�i�[���I���Ɉڍs����
				//��v����Ȃ�A�i�[���p������

				using Type = S_BoundFns<t_NextNumber* Fn::Judge::value, t_NextNumber,Fn::FnType,T_Bounds...>::Type;

			};

			//�d�l
			//S_Address�ɑ΂��Ĉ������Z�b�g����
			template<class ...T_Fn, int t_NextNumber, class ...T_NewSetArgs>
			struct S_BindFns<Function<T_Fn...>, t_NextNumber, T_NewSetArgs...>
			{	
				//�d�l
				//�����������v���邩���肷��
				using Fn = IS_BindFn<Function<T_Fn...,T_NewSetArgs...>>::Type;

				//�d�l
				//�����������v���Ȃ��A�Ⴕ���͍Ō�̊֐��Ȃ�i�[���I���Ɉڍs����
				//��v����Ȃ�A�i�[���p������
				using Type = S_BoundFns<t_NextNumber* Fn::Judge::value,t_NextNumber,Fn::FnType,T_Bounds...>::Type;
			};


		public:
			//�d�l
			//�������W�߁A�֐��|�C���^�[�Ɋi�[����
			using Type = S_BindFns<tuple_element<t_MethodNumber - 1>, t_MethodNumber - 1>::Type;


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
		struct S_BoundFns<0,t_RemainingAmount,T_Bounds...>
		{
			using Type = S_BoundFns;

			//�d�l
			//�i�[���ꂽS_Address��tuple��Ԃ�
			using Fns = std::tuple<T_Bounds...>;

			//�d�l
			//Fns������Ɋi�[���ꂽ����Ԃ�
			using Judge = std::bool_constant<!(t_RemainingAmount)>;
		};

		using BoundFns = S_BoundFns<std::tuple_size<T_Fn_Args>::value>;

		//�d�l
		//�֐��|�C���^�[�ɑ΂��āA�����̒l�����������A�����v�Ŕ��肷
		using Type = BoundFns::Type;


	};



	//template<class ...MT_Fns>
	//IS_BindFns(MT_Fns... fns)
	


}