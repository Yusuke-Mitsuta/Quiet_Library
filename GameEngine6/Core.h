#pragma once

#include"Core_Base.h"
#include"Core_Parentage.h"
#include<iostream>


template<>
class Core<"Core"> :
	public Core<>
{
protected:


public:

	N_Core_Control::Parentage parentage;


	virtual N_Core_Control::Parentage* Get_Parentage()final;


};

inline N_Core_Control::Parentage* Core<"Core">::Get_Parentage()
{
	return &parentage;
}
