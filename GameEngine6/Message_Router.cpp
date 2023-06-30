#include "Message_Router.h"

using namespace N_Messaege;

std::list<Message_Origin*> Routur::message_List;

void Routur::First_Update()
{
	for (auto message : message_List)
	{
		message->Execute();
		message_List.remove(message);
		delete message;
	}
}