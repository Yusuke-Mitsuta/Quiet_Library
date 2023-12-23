#pragma once

#include"Core_Control_Tower.h"
#include<vector>


namespace N_Core_Control
{

	class Get_Origin
	{
		friend class Get_Origin;
	protected:
		
		static constexpr Size_Type Default_Level=999;

		static constexpr Size_Type Default_Max_HitNum=999;

		virtual constexpr Tower*& Get_Tower() = 0;

		Storge*& Get_Storge(E_Core_Type type);

		template<class T, Size_Type t_Level, Size_Type t_Max_HitNum>
		std::vector<T*>& Search();

		template<class T,Size_Type t_Level, Size_Type t_Max_HitNum>
		requires Fg<!(t_Level)>
		void Search(E_Core_Type type, std::vector<T*>* hit_List);

		template<class T, Size_Type t_Level, Size_Type t_Max_HitNum>
			requires Fg<(t_Level)>
		void Search(E_Core_Type type, std::vector<T*>* hit_List){};

	public:

		template<class T,Size_Type t_Level = Default_Level>
			requires derived_from<T, Base>&&
		same_as_not<T, Base>
		T* Get_Child();

		template<class T,Size_Type t_Level= Default_Level,Size_Type t_Max_HitNum =Default_Max_HitNum>
			requires derived_from<T, Base> &&
		same_as_not<T,Base>
		std::vector<T*>& Get_Childs();
	};

	template<class C_T>
	class Get :
		public Get_Origin {};

	template<class T,Size_Type t_Level, Size_Type t_Max_HitNum>
	inline std::vector<T*>& Get_Origin::Search()
	{
		std::vector<T*> hit_List;
		Search<T, t_Max_HitNum, t_Level>(Select_Core_Type<T>(), &hit_List);
		return hit_List;
	}

	template<class T,Size_Type t_Level, Size_Type t_Max_HitNum>
	requires Fg<!(t_Level)>
	inline void Get_Origin::Search(E_Core_Type type, std::vector<T*>* hit_List)
	{
		for (auto tower : Get_Storge(type)->Get_ChildList())
		{
			T* material = static_cast<T*>(tower->this_Core);

			if (material != nullptr)
			{
				hit_List->emplace_back(material);

				if (t_Max_HitNum==hit_List->size())
				{
					return;
				}
			}

			static_cast<Get_Origin*>(tower->this_Core->Get_Parentage())->Search<T,t_Level-1, t_Max_HitNum>(type, hit_List);

			if (t_Max_HitNum == hit_List->size())
			{
				return;
			}
		}
		return;
	}

	template<class T, Size_Type t_Level>
		requires derived_from<T, Base>&&
	same_as_not<T, Base>
	inline T* Get_Origin::Get_Child()
	{
		std::vector<T*>& hit = Search<T, t_Level, 1>();

		if (hit.empty())
		{
			return nullptr;
		}

		return hit.front();
	}

	template<class T, Size_Type t_Level, Size_Type t_Max_HitNum>
		requires derived_from<T, Base>&&
	same_as_not<T, Base>
	inline std::vector<T*>& Get_Origin::Get_Childs()
	{
		return Search<T,t_Level,t_Max_HitNum>();
	}
}