//
// Created by comardom on 25-9-11.
//
//通过键盘，分别输入集合A和B中的数据元素，要求数据元素类型为整数类型，输出两个集合的交、并、差、是否是子集。

#include <stdlib.h>
#include "constData.h"
#include "cSafeInput.h"

namespace cFixedArray
{
	int main_CFA()
	{
		void init_array(int *arr, int name, bool use_const_data);
		void remove_duplicates(int *arr, int *n);
		void print_array(const int *arr);
		void bubble_sort(int *arr, int n);
		void selection_sort(int *arr, int n);
		void print_arrOut(int *arrOut, int digits, short purpose);
		void intersection_slow(const int *arrA,const int *arrB);
		void intersection_fast(const int *arrA, int sizeA, const int *arrB, int sizeB);
		void union_func(const int *arrA, int sizeA, const int *arrB, int sizeB);
		void choose_sort(int *arrA, int *arrB, int sizeA, int sizeB, short howSort);
		void difference(const int *arrA, int sizeA, const int *arrB, int sizeB, bool isA_minus_B);
		bool is_subset(const int *arrA, int sizeA, const int *arrB, int sizeB);
		void init_array2(int *arr, int name);

		//这是普通const
		// int arrA[ARR_SIZE], arrB[ARR_SIZE];
		// int sizeA = ARR_SIZE, sizeB = ARR_SIZE;
		// init_array(arrA, 0,true);
		// init_array(arrB, 1,true);

		//这是子集const
		int arrA[ARR_SIZE/2], arrB[ARR_SIZE];
		int sizeA = ARR_SIZE/2, sizeB = ARR_SIZE;
		init_array2(arrA,0);
		init_array2(arrB,1);

		choose_sort(arrA, arrB,sizeA,sizeB, 2);
		remove_duplicates(arrA, &sizeA);
		remove_duplicates(arrB, &sizeB);
		re_menu:;
		printf("Fixed array.\n1. intersection_slow\n"
			"2. intersection_fast\n""3. union\n4.difference\n5.if A is sub of B\n6.if B is sub of A\n");
		switch(hd_input())
		{
			case 1:
				intersection_slow(arrA, arrB);break;
			case 2:
				intersection_fast(arrA,sizeA,arrB,sizeB);break;
			case 3:
				union_func(arrA, sizeA, arrB, sizeB);break;
			case 4:
				difference(arrA, sizeA, arrB, sizeB, true);
			case 5:
				printf(is_subset(arrA, sizeA, arrB, sizeB)?"True\n":"False\n");break;
			case 6:
				printf(is_subset(arrB, sizeB, arrA, sizeA)?"True\n":"False\n");break;
			default: goto exit_menu;
		}
		goto re_menu;
		exit_menu:;
		return 0;
	}

	// 负责初始化数组，只进行输入，不去重
	void init_array(int *arr, int name, bool use_const_data)
	{
		const char* setName = (name == 0) ? "A" : "B";

		if (use_const_data)
		{
			const int* constArr = (name == 0) ? TEST_INT_ARR_A : TEST_INT_ARR_B;
			for (int i = 0; i < ARR_SIZE; i++)
			{
				arr[i] = constArr[i];
			}
			printf("Static %s.\n", setName);
		}
		else
		{
			printf("In %d nums to %s.\n", ARR_SIZE, setName);
			for (int i = 0; i < ARR_SIZE; i++)
			{
				d_input(arr + i);
			}
		}
	}

	void init_array2(int *arr, int name)
	{
		const char* setName = (name == 0) ? "SON" : "FATHER";
		const int* constArr = (name == 0) ? TEST_INT_SON: TEST_INT_FATHER;
		if (name == 0)
		{
			for (int i = 0; i < ARR_SIZE/2; i++)
			{
				arr[i] = constArr[i];
			}
		}
		else
		{
			for (int i = 0; i < ARR_SIZE; i++)
			{
				arr[i] = constArr[i];
			}
		}
		printf("Static %s.\n", setName);
	}

	// 这是一个新的辅助函数，用于在排序后去重
	void remove_duplicates(int *arr, int *n)
	{
		if(*n <= 1){return;}
		int j = 0;
		for(int i = 1; i < *n; i++)
		{
			if(arr[i] != arr[j])
			{
				j++;
				arr[j] = arr[i];
			}
		}
		*n = j + 1; // 更新数组的有效大小
	}


	void print_array(const int *arr)
	{
		for(int i=0;i<ARR_SIZE;i++)
		{
			if(i==0)
			{
				printf("This: \n");
			}
			printf("%d ",*(arr+i));
			if(i==ARR_SIZE-1)
			{
				printf("\b\n");
			}
		}
	}


	void bubble_sort(int *arr, const int n)
	{
		int tmp=0;
		for (int i=0;i<n-1;i++)
		{
			for (int j=0;j<n-i-1;j++)
			{
				if (*(arr+j)>*(arr+j+1))
				{
					tmp=*(arr+j);
					*(arr+j)=*(arr+j+1);
					*(arr+j+1)=tmp;
				}
			}
		}
	}


	void selection_sort(int *arr, int n)
	{//选择排序真的很复杂
		int temp = 0;
		for (int i = 0; i < n - 1; i++)
		{
			// 找到未排序部分的最小元素的索引
			int min_idx = i;
			for (int j = i + 1; j < n; j++)
			{
				if (arr[j] < arr[min_idx])
				{
					min_idx = j;
				}
			}
			// 将找到的最小元素与当前位置的元素交换
			temp = arr[min_idx];
			arr[min_idx] = arr[i];
			arr[i] = temp;
		}
	}


	int compare_ints(const void *a, const void *b)
	{
		// ReSharper disable once CppCStyleCast
		const int arg1 = *(const int*)a;
		// ReSharper disable once CppCStyleCast
		const int arg2 = *(const int*)b;
		return (arg1 - arg2);
	}
	//上下两个函数绑定，用于qsort,不如模板
	void stdlib_q_int_sort(void *base, size_t num, size_t size)
	{
		qsort(base, num, size, compare_ints);
	}


	void print_arrOut(const int *arrOut, const int digits, const short purpose)
	{
		if(digits)
		{
			switch(purpose)
			{
				case 0:printf("The intersection is: \n{ ");break;
				case 1:printf("The union is: \n{ ");break;
				case 2:printf("The difference is: \n{ ");
				default:;
			}

			for(int i=0;i<digits;i++)
			{
				printf("%d, ",*(arrOut+i));
			}
			printf("\b\b }\n");
		}
		else
		{
			printf("∅\n");
		}
	}


	void intersection_slow(const int *arrA,const int *arrB)
	{
		int arrOut[ARR_SIZE]={0};
		short digits = 0;
		for(int i=0;i<ARR_SIZE;i++)
		{
			for(int j=0;j<ARR_SIZE;j++)
			{
				if(*(arrA+i)==*(arrB+j))
				{
					arrOut[digits]=*(arrA+i);
					digits++;
				}
			}
		}
		print_arrOut(arrOut,digits,0);
	}


	void choose_sort(int *arrA, int *arrB, int sizeA, int sizeB, short howSort)
	{
		switch(howSort)
		{
			case 0:
				bubble_sort(arrA, sizeA);
				bubble_sort(arrB, sizeB);
				break;
			case 1:
				selection_sort(arrA, sizeA);
				selection_sort(arrB, sizeB);
				break;
			case 2:
				stdlib_q_int_sort((void*)arrA, sizeA, sizeof(int));
				stdlib_q_int_sort((void*)arrB, sizeB, sizeof(int));
				break; // Don't forget this break
			default:
				// It's good practice to handle invalid input
				// You could print an error message or do nothing
				break;
		}
	}

	void intersection_fast(const int *arrA, const int sizeA, const int *arrB, const int sizeB)
	{
		int arrOut[ARR_SIZE] = {0};
		// 假设 arrA 和 arrB 已经排序且去重
		int i = 0, j = 0, k = 0;int digits = 0;
		while (i < sizeA && j < sizeB)
		{
			if (arrA[i] < arrB[j])
			{
				i++;
			}
			else if(arrA[i] > arrB[j])
			{
				j++;
			}
			else
			{
				arrOut[k++] = arrA[i++];
				j++;
			}
		}
		print_arrOut(arrOut,digits,0);
	}


	void union_func(const int *arrA, const int sizeA, const int *arrB, const int sizeB)
	{
		int arrOut[ARR_SIZE * 2] = {0};
		int i = 0, j = 0, digits = 0;
		while (i < sizeA && j < sizeB)
		{
			if (arrA[i] < arrB[j])
			{
				arrOut[digits++] = arrA[i++];
			}
			else if(arrA[i] > arrB[j])
			{
				arrOut[digits++] = arrB[j++];
			}
			else
			{
				arrOut[digits++] = arrA[i++];
				j++;
			}
		}
		while (i < sizeA) {arrOut[digits++] = arrA[i++];}
		while (j < sizeB) {arrOut[digits++] = arrB[j++];}

		print_arrOut(arrOut, digits, 1);
	}



	void difference(const int *arrA, const int sizeA, const int *arrB, const int sizeB, bool isA_minus_B)
	{
		int arrOut[ARR_SIZE] = {0}; // 静态数组
		int i = 0, j = 0, digits = 0;

		// 确定基准数组和比较数组
		const int *base_arr = isA_minus_B ? arrA : arrB;
		const int *compare_arr = isA_minus_B ? arrB : arrA;
		const int base_size = isA_minus_B ? sizeA : sizeB;
		const int compare_size = isA_minus_B ? sizeB : sizeA;

		while (i < base_size && j < compare_size)
		{
			if (base_arr[i] < compare_arr[j])
			{
				// 基准数组的当前元素是独有的，添加到差集
				arrOut[digits++] = base_arr[i++];
			}
			else if (base_arr[i] > compare_arr[j])
			{
				// 比较数组的当前元素不是我们需要的，跳过
				j++;
			}
			else
			{
				// 找到共同元素，跳过
				i++;
				j++;
			}
		}

		// 将基准数组中剩余的独有元素全部添加到差集
		while (i < base_size)
		{
			arrOut[digits++] = base_arr[i++];
		}

		print_arrOut(arrOut, digits, 2);
	}


	bool is_subset(const int *arrA, const int sizeA, const int *arrB, const int sizeB)
	{
		//ai帮我重写的，确实没有那么绕远了
		// 如果 A 的大小大于 B 的大小，那么 A 不可能是 B 的子集
		if (sizeA > sizeB)
		{
			return false;
		}

		int i = 0; // arrA 的指针
		int j = 0; // arrB 的指针

		// 假设 arrA 和 arrB 已经排序且去重
		while (i < sizeA && j < sizeB)
		{
			if (arrA[i] < arrB[j])
			{
				// 如果 A 的当前元素小于 B 的当前元素，说明 A 的这个元素在 B 中不存在。
				// 因为数组已经排序，所以 arrA[i] 永远找不到匹配了。
				return false;
			}
			else if (arrA[i] > arrB[j])
			{
				// B 的当前元素比 A 的小，继续在 B 中寻找下一个元素。
				j++;
			}
			else // arrA[i] == arrB[j]
			{
				// 找到匹配，同时移动两个指针。
				i++;
				j++;
			}
		}

		// 循环结束后，如果 i 等于 sizeA，说明 A 的所有元素都在 B 中找到了匹配。
		return (i == sizeA);
	}
}