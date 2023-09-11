#pragma once

#include"Parameter.h"
#include"Parameter_convertible_to.h"
#include"Expand.h"

namespace N_Function
{


	template<class T_Request_Args,class T_Bind_Args>
	struct IS_Request_Args
	{
	//private:

		template<class T_Result_Request_Args, class T_Result_Bind_Args>
		struct S_Result
		{
			using Request_Args = T_Result_Request_Args;
			using Bind_Args = T_Result_Bind_Args;
		};


		template<int _Index, class T_Parameter,class T_Change = std::nullopt_t>
		struct IS_Zip_Expand
		{
			template<class T_Result, int _Index>
			struct S_Result
			{
				using Result = T_Result;
				static constexpr int Index = _Index;
				using Element = S_Result;
				using Change = S_Result;
			};

			template<class T_Result,int _Index, class T_Parameters>
			struct S_Zip_Expand;

			template<class ...T_Result,int _Index,class T_Flont_Parameter,class ...T_Parameter>
			struct S_Zip_Expand<S_Parameter<T_Result...>,_Index,S_Parameter<T_Flont_Parameter,T_Parameter...>>
			{
				using Type = S_Zip_Expand<S_Parameter<T_Result..., T_Flont_Parameter>, _Index - 1, S_Parameter<T_Parameter...>>;
				using Element = Type::Element;
				using Change = Type::Change;
			};


			//èIóπÉtÉâÉOÇÃâ¸ó«
			//operatorÇÃçÏê¨
			template<class ...T_Result, int _Index,class T_Flont_Parameter,class ...T_Parameter>
			struct S_Zip_Expand<S_Parameter<T_Result...>, _Index, S_Parameter<S_Zip<T_Flont_Parameter>, T_Parameter...>>
			{
				using Next = S_Zip_Expand<S_Parameter<S_Expand<T_Flont_Parameter>>,_Index, typename S_Expand<T_Flont_Parameter>::Type>;
				using Next_Change = typename Next::Change;
				using Next_Element =typename Next::Element;
				using Swap_Next = U_Swap_t1<Next_Element, Next_Change,not_is_nullopt<T_Change>>;
				using Type = S_Zip_Expand<S_Parameter<T_Result..., typename Swap_Next::Result>, Swap_Next::Index, S_Parameter<T_Parameter...>>;

				using Element = U_Swap_t1<Swap_Next, Type, Swap_Next::Index>::Element;
				using Change = U_Swap_t1<S_Result<S_Parameter<T_Result..., typename Swap_Next::Result, T_Parameter...>, Swap_Next::Index>,Type, Swap_Next::Index>::Change;

			};

			template<class ...T_Result, class T_Flont_Parameter, class ...T_Parameter>
			struct S_Zip_Expand<S_Parameter<T_Result...>, 0, S_Parameter<S_Zip<T_Flont_Parameter>, T_Parameter...>>
			{
				using Next = S_Zip_Expand<S_Parameter<S_Expand<T_Flont_Parameter>>, 0, typename S_Expand<T_Flont_Parameter>::Type>;
				using Next_Change = typename Next::Change;
				using Next_Element = typename Next::Element;
				using Swap_Next = U_Swap_t1<Next_Element, Next_Change, not_is_nullopt<T_Change>>;
				using Type = S_Zip_Expand<S_Parameter<T_Result..., typename Swap_Next::Result>, Swap_Next::Index, S_Parameter<T_Parameter...>>;

				using Element = U_Swap_t1<Swap_Next, Type, Swap_Next::Index>::Element;
				using Change = U_Swap_t1<S_Result<S_Parameter<T_Result..., typename Swap_Next::Result, T_Parameter...>, Swap_Next::Index>, Type, Swap_Next::Index>::Change;

			};

			template<class ...T_Result, int _Index,class T_Expand_Type,class... T_Expand_Parameter, class ...T_Parameter>
			struct S_Zip_Expand<S_Parameter<T_Result...>, _Index, S_Parameter<S_Parameter<S_Expand<T_Expand_Type>,T_Expand_Parameter...>, T_Parameter...>>
			{
				using Next = S_Zip_Expand<S_Parameter<S_Expand<T_Expand_Type>>, _Index, S_Parameter<T_Expand_Parameter...>>;
				using Next_Change = typename Next::Change;
				using Next_Element = typename Next::Element;
				using Swap_Next = U_Swap_t1<Next_Element, Next_Change, not_is_nullopt<T_Change>>;
				using Type = S_Zip_Expand<S_Parameter<T_Result..., typename Swap_Next::Result>, Swap_Next::Index, S_Parameter<T_Parameter...>>;

				using Element = U_Swap_t1<Swap_Next, Type, Swap_Next::Index>::Element;
				using Change = U_Swap_t1<S_Result<S_Parameter<T_Result..., typename Swap_Next::Result, T_Parameter...>, Swap_Next::Index>, Type, Swap_Next::Index>::Change;

			};

			template<class ...T_Result,class T_Expand_Type, class... T_Expand_Parameter, class ...T_Parameter>
			struct S_Zip_Expand<S_Parameter<T_Result...>, 0, S_Parameter<S_Parameter<S_Expand<T_Expand_Type>, T_Expand_Parameter...>, T_Parameter...>>
			{
				using Next = S_Zip_Expand<S_Parameter<S_Expand<T_Expand_Type>>, 0, S_Parameter<T_Expand_Parameter...>>;
				using Next_Change = typename Next::Change;
				using Next_Element = typename Next::Element;
				using Swap_Next = U_Swap_t1<Next_Element, Next_Change, not_is_nullopt<T_Change>>;
				using Type = S_Zip_Expand<S_Parameter<T_Result..., typename Swap_Next::Result>, Swap_Next::Index, S_Parameter<T_Parameter...>>;

				using Element = U_Swap_t1<Swap_Next, Type, Swap_Next::Index>::Element;
				using Change = U_Swap_t1<S_Result<S_Parameter<T_Result..., typename Swap_Next::Result, T_Parameter...>, Swap_Next::Index>, Type, Swap_Next::Index>::Change;

			};


			template<class T_Result,int _Index>
			struct S_Zip_Expand<T_Result, _Index, S_Parameter<>>
			{
				using Element = S_Result<T_Result,_Index>;
				using Change = S_Result<T_Result, _Index>;
			};

			template<class ...T_Result,class T_Flont_Parameter, class ...T_Parameter>
				//requires !same_as_template_class<T_Flont_Parameter,S_Zip>
			struct S_Zip_Expand<S_Parameter<T_Result...>,0,S_Parameter<T_Flont_Parameter, T_Parameter...>>
			{
				using Element = S_Result<T_Flont_Parameter,0>;

				using Change = S_Result<S_Parameter<T_Result..., T_Change, T_Parameter...>, 0>;
			};

			using Type = S_Zip_Expand<S_Parameter<>, _Index, T_Parameter>;

			using Element_R = typename S_Zip_Expand<S_Parameter<>, _Index, T_Parameter>::Element;

			using Change_R = typename S_Zip_Expand<S_Parameter<>, _Index, T_Parameter>::Change;
		public:

			using Element = Element_R::Result;

			using Change = Change_R::Result;

		};


		template<int _Index, class T_Parameters>
		using Zip_Expand_Element = IS_Zip_Expand<_Index, T_Parameters>::Element;

		template<int t_Change_Point, class T_Parameters,class T_Change>
		using Zip_Expand_Change = IS_Zip_Expand<t_Change_Point, T_Parameters,T_Change>::Change;

		template<
			class TP_Request_Args = T_Request_Args,
			class TP_Bind_Args = T_Bind_Args,
			int t_Request_Args_Number = T_Request_Args::Size - 1,
			int t_Bind_Args_Number = T_Bind_Args::Size - 1,
			class T_Request_Args_Part = Zip_Expand_Element<t_Request_Args_Number, TP_Request_Args>,
			class T_Bind_Args_Part = Zip_Expand_Element<t_Bind_Args_Number, TP_Bind_Args>,
			bool t_Loop_Fg = static_cast<bool>(t_Bind_Args_Number)>
		struct S_Request_Args
		{
			using Type = S_Result<std::nullopt_t, std::nullopt_t>;
		};


		template<
			class TP_Request_Args, class TP_Bind_Args,
			int t_Request_Args_Number, int t_Bind_Args_Number,
			class T_Request_Args_Part, class T_Bind_Args_Part>
			requires convertible_to<T_Bind_Args_Part, T_Request_Args_Part>
		struct S_Request_Args<TP_Request_Args, TP_Bind_Args, t_Request_Args_Number, t_Bind_Args_Number,
			T_Request_Args_Part, T_Bind_Args_Part, true>
		{
			using Type = S_Request_Args<TP_Request_Args, TP_Bind_Args, t_Request_Args_Number - 1, t_Bind_Args_Number - 1>::Type;
		};

		template<
			class TP_Request_Args, class TP_Bind_Args,
			int t_Request_Args_Number, int t_Bind_Args_Number,
			class T_Request_Args_Part, class T_Bind_Args_Part>
			requires not_convertible_to<T_Bind_Args_Part, T_Request_Args_Part>&&
		is_expand<T_Request_Args_Part>
			struct S_Request_Args<TP_Request_Args, TP_Bind_Args, t_Request_Args_Number, t_Bind_Args_Number,
			T_Request_Args_Part, T_Bind_Args_Part, true>
		{
			using Remove = U_Remove_Element_t<TP_Request_Args,t_Request_Args_Number>;

			using Expand = S_Expand<T_Request_Args_Part>::Type;

			using Request_Args = Zip_Expand_Change<t_Request_Args_Number, TP_Request_Args, S_Zip<T_Request_Args_Part>>;

			using Type = S_Request_Args<Request_Args, TP_Bind_Args, t_Request_Args_Number + Expand::Size - 1, t_Bind_Args_Number>::Type;

		};

		template<
			class TP_Request_Args, class TP_Bind_Args,
			int t_Request_Args_Number,int t_Bind_Args_Number,
			class T_Request_Args_Part, class T_Bind_Args_Part>
			requires not_convertible_to<T_Bind_Args_Part, T_Request_Args_Part> &&
		!is_expand<T_Request_Args_Part> && is_expand<T_Bind_Args_Part>
			struct S_Request_Args<TP_Request_Args,TP_Bind_Args, t_Request_Args_Number, t_Bind_Args_Number,
			T_Request_Args_Part, T_Bind_Args_Part, true>
		{
			using Remove = U_Remove_Element_t<TP_Bind_Args,t_Bind_Args_Number>;

			using Expand =S_Expand<T_Bind_Args_Part>::Type;

			using Bind_Args = U_Insert_Element_P_t<Remove, t_Bind_Args_Number,Expand>;

			using Type = S_Request_Args<TP_Request_Args,Bind_Args,t_Request_Args_Number, t_Bind_Args_Number + Expand::Size - 1>::Type;

		};

		template<
			class TP_Request_Args, class TP_Bind_Args,
			int t_Request_Args_Number, int t_Bind_Args_Number,
			class T_Request_Args_Part, class T_Bind_Args_Part>
			requires convertible_to<T_Bind_Args_Part, T_Request_Args_Part>
		struct S_Request_Args<TP_Request_Args, TP_Bind_Args, t_Request_Args_Number, t_Bind_Args_Number,
			T_Request_Args_Part, T_Bind_Args_Part, false>
		{
			using Request_Args = U_Range_Element_t<TP_Request_Args, 0, t_Request_Args_Number>;

			using Type= S_Result<Request_Args,TP_Bind_Args>;
		};

		template<class T_Request_Args=T_Request_Args, class T_Bind_Args=T_Bind_Args>
		struct S_Args_Empty_Judge 
		{
			using Type = S_Request_Args<>::Type;
		};

		template<class T_Bind_Args>
			requires (static_cast<bool>(T_Bind_Args::Size))
		struct S_Args_Empty_Judge<S_Parameter<>,T_Bind_Args>
		{
			using Type = S_Result<std::nullopt_t, std::nullopt_t>;
		};
		template<class T_Request_Args>
		struct S_Args_Empty_Judge<T_Request_Args, S_Parameter<>>
		{
			using Type = S_Result<T_Request_Args, S_Parameter<>>;
		};

		using Type = S_Args_Empty_Judge<>::Type;
	public:

		using Request_Args = Type::Request_Args;
		using Bind_Args = Type::Bind_Args;

	};




}
