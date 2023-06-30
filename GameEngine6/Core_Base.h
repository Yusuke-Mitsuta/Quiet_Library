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

	template<N_Constexpr::String str>
	void Receive();

	template<>
	virtual void Receive<"Update">() {}

};

template<class T>
class Name
{
public:

};

