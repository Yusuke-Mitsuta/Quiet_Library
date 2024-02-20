#include"Output_Message.h"

#include<compare>
#include<initializer_list>
#include<iostream>

#include"Array.h"
#include"Function.h"
#include"Tuple.h"

std::string getLastPathComponent(std::string path) {
	std::string r;
	size_t p = 0;
	for (size_t i = path.size() - 1; i > 0; i--)
	{
		if (path[i] == '\\')
		{

			p = i;
			break;
		}
	}
	for (int i = static_cast<int>(p) + 1; i < path.size(); i++)
		r.push_back(path[i]);
	return r;
}

std::string Type_id_change_String(std::string path)
{

	size_t start_point = path.find("class N_Constexpr::String");

	if (start_point == std::string::npos)
	{
		return path;
	}


	std::string subString = path.substr(start_point);

	size_t char_start_point = subString.find("{char{") + 6;

	size_t end_point = subString.find("}}");

	std::string char_number;

	char_number += 32;
	char_number += 34;

	for (size_t i = char_start_point; i < end_point; i++)
	{
		std::string char_number_chip;

		for (i; !(',' == subString[i] || '}' == subString[i]); i++)
		{
			char_number_chip += subString[i];
		}

		char_number += static_cast<char>(std::stoi(char_number_chip));
	}
	char_number += 34;
	char_number += 32;

	path.replace(start_point, end_point + 2, char_number);

	return Type_id_change_String(path);

}

std::string Type_id_delete_head_class_struct(std::string path)
{
	size_t delete_p = path.find("class ");

	while (delete_p != std::string::npos)
	{
		path = path.erase(delete_p, 6);
		delete_p = path.find("class ");
	}

	delete_p = path.find("struct ");

	while (delete_p != std::string::npos)
	{
		path = path.erase(delete_p, 7);
		delete_p = path.find("struct ");
	}

	return path;
}



std::vector<std::string> Type_id_template_separate(std::string path)
{
	int template_not_separate_fg = 0;

	size_t separate_start_point = path.find("<");

	std::vector<std::string> template_type_name_separate;

	if (separate_start_point != std::string::npos)
	{
		template_type_name_separate.push_back(
			(path.substr(0, separate_start_point) + "< ... >"));
	}

	for (size_t i = separate_start_point+1; i < path.size(); i++)
	{
		switch (path[i])
		{
		case ',':
			if (!template_not_separate_fg)
			{
				template_type_name_separate.push_back(
					path.substr(separate_start_point+1,i- separate_start_point - 1));
				separate_start_point =i;
			}
			break;
		case '<':
			template_not_separate_fg += 1;
			break;
		case '>':

			if (!template_not_separate_fg)
			{
				template_type_name_separate.push_back(
					path.substr(separate_start_point + 1,i- separate_start_point-1));
				separate_start_point = path.find("<");
				break;
			}

			template_not_separate_fg -= 1;
			break;
		default:
			break;
		}

	}

	return template_type_name_separate;
}

void OUTPUT_MESSAGE::S_Directory_Tree::Add(Tree_Type type)
{
	directory_tree.push_back(type);
}

void OUTPUT_MESSAGE::S_Directory_Tree::Change(Tree_Type type)
{
	directory_tree.back() = type;
}

void OUTPUT_MESSAGE::S_Directory_Tree::Remove()
{
	if (directory_tree.size() > 1)
	{
		directory_tree.pop_back();
	}
	else
	{
		directory_tree.clear();
	}
}

void OUTPUT_MESSAGE::S_Directory_Tree::Output()
{
	std::string result = {"  "};

	if (directory_tree.empty())
	{
		result += " ";
	}
	else
	{
		for (int i = 0; i < directory_tree.size() - 1; i++)
		{
			if (Tree_Type::VERTICAL == directory_tree[i])
			{
				result += "  ";
			}
			result += "  ";
		}

		if (directory_tree.back() == Tree_Type::VERTICAL_RIGHT)
		{
			result += "  ";
		}
		else if (directory_tree.back() == Tree_Type::LEFT_UNDER)
		{
			result += "  ";
		}

		result += "  ";
	}
	std::cout << result;

}
