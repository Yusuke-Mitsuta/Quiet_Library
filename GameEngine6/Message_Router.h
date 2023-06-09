#pragma once

#include"Message.h"
#include"main.h"
#include<list>

namespace N_Message
{

	
	class Router
	{
	private:
		static const unsigned int Message_Size = 1;

		using Message = int;

	public:
		std::list<Message> message_List;

		Router() {}

		DONT_COPY(Router)


		void Send(N_Constexpr::String<Message_Size> set_Address, N_Constexpr::String<Message_Size> set_Message);

		void Send(Message set_Message);


	};
}