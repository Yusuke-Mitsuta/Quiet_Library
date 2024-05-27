#pragma once



namespace quiet::N_Template_Control
{
	template<class T_Old, template<class...> class T_New_Outer>
	static constexpr auto TemplateClass_Change()
	{
	}

	template<class T_Old, class T_New_Outer>
	struct S_TemplateClass_Change
	{

	};

	template<class T_Old, template<class...> class T_New_Outer>
	struct S_TemplateClass_Change
	{
	
	};


}