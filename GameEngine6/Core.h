#pragma once

#include"Core_Name.h"
#include"Message_Router.h"
#include<iostream>
#include<list>
#include<string>
#include<functional>
#include<concepts>



template<Core_Name t_ClassName = "Core", Core_Name ...t_Root>
class Core
{
protected:


public:

	template<Core_Name flont, Core_Name ...root>
	constexpr Core_Name Flont()
	{
		return flont;
	}

	Core_Name flont = Flont<t_Root...>();

	template<N_Constexpr::String t_Address = "", N_Constexpr::String t_message = "">
	class Message
	{
	protected:
		constexpr Message() {}
	public:

		decltype(t_Address) address = t_Address;

		decltype(t_message) message = t_message;
	};


	N_Message::Router Router;


	void Update()
	{
		std::cout << Router.message_List.front().address.Change_stdString();
	}

	template<N_Constexpr::String t_Str>
	void Hoge() {}



};

