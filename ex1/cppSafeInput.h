//
// Created by Comardom on 25-9-6.
//

#ifndef NUM_UND_STR_SAFE_INPUT_H
#define NUM_UND_STR_SAFE_INPUT_H

#include <iostream>
#include <limits>
#include <string>

// 清空输入缓冲区
void clear_stdin();

// 数字输入函数模板
template <typename T>
void num_input_s(T& n);

// 字符串输入函数
void string_input_s(std::string& s);

// --- 以下是函数的完整实现 ---

inline void clear_stdin()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template <typename T>
void num_input_s(T &n)
{
	goto_re_input:;
	std::cin.clear();
	std::cin >> n;

	if (std::cin.good() && n >= std::numeric_limits<T>::min() && n <= std::numeric_limits<T>::max())
	{
		clear_stdin();
	}
	else
	{
		std::cout << "Error. Plz enter again." << std::endl;
		std::cin.clear();
		clear_stdin();
		goto goto_re_input;
	}
}

inline short hd_input_s()
{
	goto_re_input:;
	std::cin.clear();
	short tmp = 0;
	std::cin >> tmp;

	if (std::cin.good() && tmp >= std::numeric_limits<short>::min() && tmp <= std::numeric_limits<short>::max())
	{
		clear_stdin();
	}
	else
	{
		std::cout << "Error. Plz enter again." << std::endl;
		std::cin.clear();
		clear_stdin();
		goto goto_re_input;
	}
	return tmp;
}

inline void string_input_s(std::string &s)
{
	std::cin.clear();
	clear_stdin();
	std::getline(std::cin, s);
}

#endif // NUM_UND_STR_SAFE_INPUT_H