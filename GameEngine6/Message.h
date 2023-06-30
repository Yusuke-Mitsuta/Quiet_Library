#pragma once

#include"Constexpr_String.h"
#include"Core_Base.h"
#include<list>


//#define RECEIVE(SelectMessage) \
//template<N_Constexpr::String t_Address = "", N_Constexpr::String t_Message = "">\
//requires requires \
//{\
//	requires (t_Message == N_Constexpr::String(#SelectMessage));\
//	requires derived_from<Core<t_Address>,Core>;\
//}\
//	void Receive() \
//

class Message_Origin
{

protected:
	Message_Origin() {}
public:

	virtual void Execute() = 0;

};

template<N_Constexpr::String t_Address = "", N_Constexpr::String t_Message = "">
class Message:
	public Message_Origin
{
protected:

	Core<"Core">* target_Core;

public:

	Message(Core<"Core">* set_Target_P) :
		target_Core(set_Target_P) {}

	void Execute()
	{
		
	}

	static constexpr N_Constexpr::String address = t_Address;

	static constexpr N_Constexpr::String message = t_Message;

};
