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

	//Routur‚ÉˆÚİ—\’è
	//static std::list<Message_Core> message_List;

public:

	virtual void Execute() {}

};

template<N_Constexpr::String t_Address="", N_Constexpr::String t_Message ="">
class Message :
	public Message_Core
{
protected:
public:

	constexpr Message() {}

	void Execute()
	{

	}

	static constexpr decltype(t_Address) address = t_Address;

	static constexpr decltype(t_Message) message = t_Message;
};

