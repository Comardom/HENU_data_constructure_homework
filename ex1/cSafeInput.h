//
// Created by comardom on 25-9-11.
//

#ifndef CSAFEINPUT_H
#define CSAFEINPUT_H
#include <limits.h>
#include <stdio.h>

inline void clear_stdin()
{//用于清空缓冲区
	int ch;
	// 循环读取输入流中的所有字符，直到换行符或 EOF
	while ((ch = getchar()) != '\n' && ch != EOF)
	{
		;// 什么都不做，仅用于清空缓冲区
	}
}
//简单说一下哈，就是所有的输入都用我自己写的函数代替了，里面包含了输入检查
//原生scanf容易把自己卡死，getchar说实话太累了
inline void d_input(int *n)
{
	int tmp=0;
	bool is_num = true;
	goto_d:;
	is_num=scanf("%d",&tmp);
	if(!is_num || tmp>INT_MAX || tmp<INT_MIN)
	{
		printf("Incorrect input! Plz enter again.\n");
		clear_stdin();
		goto goto_d;
	}
	*n=tmp;
}

inline void hd_input(short *n)
{
	short tmp=0;
	bool is_num = true;
	goto_hd:;
	is_num=scanf("%hd",&tmp);
	if(!is_num || tmp>SHRT_MAX || tmp<SHRT_MIN)
	{
		printf("Incorrect input! Plz enter again.\n");
		clear_stdin();
		goto goto_hd;
	}
	*n=tmp;
}

inline short hd_input()
{
	short tmp=0;
	bool is_num = true;
	goto_hd:;
	is_num=scanf("%hd",&tmp);
	if(!is_num || tmp>SHRT_MAX || tmp<SHRT_MIN)
	{
		printf("Incorrect input! Plz enter again.\n");
		clear_stdin();
		goto goto_hd;
	}
	return tmp;
}
#endif //CSAFEINPUT_H
