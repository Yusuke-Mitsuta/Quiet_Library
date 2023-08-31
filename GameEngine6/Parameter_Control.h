#pragma once

#include"Concept.h"

template<class ...T_Parameters>
struct S_Parameter;

template<same_as_template_class<S_Parameter> T_Parameter,int ..._Remove_Indexs>
struct IS_Remove_Parameters
{

};
