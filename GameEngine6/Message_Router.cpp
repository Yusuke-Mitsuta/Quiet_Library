#include "Message_Router.h"

using namespace N_Message;

void Router::Send(N_Constexpr::String<Router::Message_Size> set_Address, N_Constexpr::String<Message_Size> set_Message)
{
	//Send(Message(set_Address, set_Message));
}

void Router::Send(Message set_Message)
{
	message_List.push_back(set_Message);
}