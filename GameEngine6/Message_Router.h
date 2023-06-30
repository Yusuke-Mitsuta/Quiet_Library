#pragma once

#include"Message.h"
#include"main.h"

namespace N_Messaege
{

	class Routur
	{
	protected:

		static std::list<Message_Origin*> message_List;

		Core<"Core">* ref_Core_P;

	public:

		void First_Update();

		template<N_Constexpr::String t_Address = "", N_Constexpr::String t_Message = "">
		void Send_Child() 
		{
			message_List.emplace_back(new Message<t_Address, t_Message>(ref_Core_P));
		}

	};



};