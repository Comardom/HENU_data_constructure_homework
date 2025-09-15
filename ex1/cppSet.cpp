//
// Created by comardom on 25-9-13.
//
#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>
#include "cppSafeInput.h"
namespace cppSet
{
	int main_CppS()
	{
		void get_user_set(std::set<int>& my_set, const std::string& set_name);
		void print_set(const std::set<int>& my_set);

		std::set<int> setA, setB;
		get_user_set(setA, "A");
		get_user_set(setB, "B");
		print_set(setA);print_set(setB);

		re_set_menu:;
		printf("C++ set.\n1. intersection\n"
			"2. union\n3.difference\n4.if A is sub of B\n5.if B is sub of A\n");
		switch(hd_input_s())
		{
			case 1:
			{
				std::set<int> intersection;
				set_intersection(setA.begin(), setA.end(), setB.begin(), setB.end(),
								 inserter(intersection, intersection.begin()));
				print_set(intersection);break;
			}
			case 2:
			{
				std::set<int> union_set;
				set_union(setA.begin(), setA.end(), setB.begin(), setB.end(),
						  inserter(union_set, union_set.begin()));
				print_set(union_set);break;
			}
			case 3:
			{
				std::set<int> difference;
				set_difference(setA.begin(), setA.end(), setB.begin(), setB.end(),
							   inserter(difference, difference.begin()));
				print_set(difference);break;
			}
			case 4:
			{
				std::cout <<includes(setB.begin(), setB.end(),
									 setA.begin(), setA.end()) << std::endl;break;
			}
			case 5:
			{
				std::cout <<includes(setA.begin(), setA.end(),
									 setB.begin(), setB.end()) << std::endl;break;
			}
			default:{ goto exit_set_menu;}
		}
		goto re_set_menu;
		exit_set_menu:;
		return 0;
	}

	void get_user_set(std::set<int>& my_set, const std::string& set_name)
	{
		int count;
		std::cout << "Set in " << set_name << "'s size";
		num_input_s(count);

		std::cout << "Set in " << count << " nums for " << set_name << std::endl;
		int value;
		for (int i = 0; i < count; ++i)
		{
			std::cout << set_name << "[" << i << "]: ";
			num_input_s(value);
			my_set.insert(value);
		}
	}
	void print_set(const std::set<int>& my_set)
	{
		std::cout << "{ ";
		for (const int elem : my_set)
		{
			std::cout << elem << " ";
		}
		std::cout << "}" << std::endl;
	}
}