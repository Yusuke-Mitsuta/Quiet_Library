#pragma once

#include"Core_Base.h"
#include"Core_Parentage.h"
#include"Message_Router.h"
#include<iostream>


template<>
class Core<"Core"> :
	public Core<"Base">
{
protected:

public:

	N_Core_Control::Parentage parentage;

	N_Messaege::Routur routur;

	N_Core_Control::Parentage* Get_Parentage()final;

	template<N_Constexpr::String str>
		requires requires
	{
		requires (N_Constexpr::String("Test") == str);
	}
	void Receive() 
	{
		C_OUT("ABV");
	}


};

inline N_Core_Control::Parentage* Core<"Core">::Get_Parentage()
{
	return &parentage;
}


