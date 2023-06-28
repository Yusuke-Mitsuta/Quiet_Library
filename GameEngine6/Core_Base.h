#pragma once
#include"Core_Name.h"

namespace N_Core_Control
{
	class Parentage;
}


template<Core_Name className="Base">
class Core
{
protected:

public:

	virtual N_Core_Control::Parentage* Get_Parentage()=0;



};