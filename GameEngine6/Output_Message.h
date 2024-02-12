#pragma once

#include<concepts>
#include<typeinfo>
#include<iostream>
#include<string>
#include<vector>

std::string getLastPathComponent(std::string path);

std::string Type_id_change_String(std::string path);

std::string Type_id_delete_head_class_struct(std::string path);

std::vector<std::string> Type_id_template_separate(std::string path);

#define Constant static constexpr auto \

#define HOGE(Name)\
void Hoge() \
{ \
C_OUT(Name) \
} \

#define SIZE_OF(className) \
C_OUT(sizeof(className));\

//#define TYPE_ID(...) \
//Type_id_delete_head_class_struct(Type_id_change_String(typeid(__VA_ARGS__).name())); \


namespace OUTPUT_MESSAGE
{
	static void C_Out_Single(auto front,auto ...ts) 
	{
		std::cout << front << std::endl;
	}

	template<size_t N = 0>
	static void C_Out()
	{}

	template<size_t N = 0>
	static void C_Out(auto t,auto... ts)
	{
		std::cout << "  " << N << " : " << t << std::endl;
		C_Out<N + 1>(ts...);
	}

	
	static void Action_C_Out(auto... ts)
	{
		switch (sizeof...(ts))
		{
		case 0:
			std::cout<< std::endl;
			break;
		case 1:
			std::cout << " << ";
			C_Out_Single(ts...);
			break;
		default:
			std::cout << std::endl;
			C_Out<0>(ts...);
			break;
		}
	}




	template<class ...Ts>
		requires(sizeof...(Ts) == 0)
	static void Type_Name_Single() {}

	//êÊì™ÇÃå^ÇÃñºëOÇèoóÕÇ∑ÇÈ
	template<class T, class ...Ts>
	static std::string Type_Name_Single()
	{
		return Type_id_delete_head_class_struct(Type_id_change_String(typeid(T).name()));
	};

	template<class ...Ts>
		requires(sizeof...(Ts) == 0)
	static void Type_Name_Output()
	{};

	template<class ...Ts>
	static void Type_Name_Output()
	{
		std::cout << Type_Name_Single<Ts...>();
	};

	struct S_Directory_Tree
	{
		enum class Tree_Type
		{
			VERTICAL,// [    ]
			VERTICAL_RIGHT,// [    ]
			LEFT_UNDER// [    ]
		};

		std::vector<Tree_Type> directory_tree = {};

		S_Directory_Tree() {}

		void Add(Tree_Type type);

		void Change(Tree_Type type);

		void Remove();

		void Output();

	};

	template<size_t dimension_Limit, class ...Ts>
	struct I_Type_Name
	{
		static void Action(S_Directory_Tree& directory_tree, int& dimension_Num, std::string& type_name)
		{
			std::vector<std::string> type_name_list = Type_id_template_separate(type_name);

			if (dimension_Num < dimension_Limit-1 && !type_name_list.empty())
			{
				std::cout << type_name_list[0] << std::endl;
				type_name_list.erase(type_name_list.begin());
				dimension_Num++;
				Action(directory_tree,dimension_Num, type_name_list);
			}
			else
			{
				std::cout << type_name << std::endl;
			}
		}

		static void Action(
			S_Directory_Tree& directory_tree,
			int& dimension_Num,
			std::vector<std::string>& type_name_list)
		{
			if (dimension_Num)
			{
				directory_tree.Add(S_Directory_Tree::Tree_Type::VERTICAL_RIGHT);
			}

			for (int i = 0; i < type_name_list.size(); i++)
			{
				if ((i == type_name_list.size() - 1) && dimension_Num)
				{
					directory_tree.Change(S_Directory_Tree::Tree_Type::LEFT_UNDER);
				}

				directory_tree.Output();
				std::cout << i << " : ";
				Action(directory_tree,dimension_Num, type_name_list[i]);
			}

			directory_tree.Remove();
			dimension_Num--;
		};

		static void Action()
		{
			S_Directory_Tree directory_tree = {};
			int dimension_Number = 0;
			std::vector<std::string> type_name_list = { Type_Name_Single<Ts>()... };

			Action(directory_tree, dimension_Number, type_name_list);
		}

	};

	template<size_t dimension_Limit,class ...Ts>
	static void Action_Type_Name()
	{
		switch (static_cast<int>(sizeof...(Ts)) * dimension_Limit)
		{
		case 0:
			std::cout << std::endl;
			break;
		case 1:
			std::cout << " << ";
			Type_Name_Output<Ts...>();
			std::cout << std::endl;
			break;
		default:
			std::cout << std::endl;
			I_Type_Name<dimension_Limit, Ts...>::Action();
			break;
		}
	};

	template<class ...Ts>
	static void Action_Type_Name()
	{
		Action_Type_Name<1, Ts...>();
	};

}
#define HEADER \
std::cout << getLastPathComponent(__FILE__) << " : " << __LINE__;\


#define C_OUT(...) \
HEADER;OUTPUT_MESSAGE::Action_C_Out(__VA_ARGS__);


#define TYPE_ID(...) \
HEADER;OUTPUT_MESSAGE::Action_Type_Name<__VA_ARGS__>();\

