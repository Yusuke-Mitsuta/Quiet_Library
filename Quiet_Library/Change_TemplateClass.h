#pragma once



namespace quiet
{

	template<class T_Change_Type, template<class...>class TT_Target_Type_Outer>
	struct I_Change_TemplateClass
	{
		template<class T_Change_Type, template<class...>class TT_Target_Type_Outer>
		struct S_Change_TemplateClass
		{

		};

	};


}