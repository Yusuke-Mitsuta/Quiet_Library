#pragma once

#include"Constexpr_String.h"
#include<list>

#define MESSAGE_RECEIVE(SelectMessage,...) \
template<class T> \
requires requires \
{\
	requires (T::message == N_Constexpr::String(SelectMessage));\
}\
	void Receive(__VA_ARGS__) \



class Message_Core
{
protected:
	constexpr Message_Core() {}

public:

	virtual void Execute() {}

};

template<N_Constexpr::String t_Address="", N_Constexpr::String t_Message ="">
class Message
{
protected:
public:

	static int Size_Type = 0;

	static std::list<Message> 

	constexpr Message() {}

	void Execute()
	{

	}

	static constexpr N_Constexpr::String address = t_Address;

	static constexpr N_Constexpr::String message = t_Message;
};

