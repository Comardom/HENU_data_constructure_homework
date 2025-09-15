#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "cSafeInput.h"
//
// Created by comardom on 25-9-13.
//
namespace cDyLinkedList
{
	//这个链表是跟着ai写的
	//链表内部数据与连接
	typedef struct Node {
		int data;     // 存储数据元素
		Node* next;   // 指向下一个节点的指针
	};
	//链表本身
	typedef struct LinkedList {
		Node* head;
		int size;
	};

	int main_CDLL()
	{
		void init_list(LinkedList* list);
		void insert_sorted(LinkedList* list, int value);
		void print_list(const LinkedList* list);
		void free_list(LinkedList* list);
		void intersection_slow(const LinkedList* listA, const LinkedList* listB);
		void intersection_fast(const LinkedList* listA, const LinkedList* listB);
		void union_func(const LinkedList* listA, const LinkedList* listB);
		void difference(const LinkedList* listA, const LinkedList* listB);
		bool is_subset(const LinkedList* listA, const LinkedList* listB);

		LinkedList listA, listB;
		init_list(&listA);
		init_list(&listB);
		int countA, countB;
		int value;

		printf("In list A's size.\n");
		d_input(&countA);
		printf("In list A.\n");
		for (int i = 0; i < countA; i++)
		{
			printf("A[%d]: ", i);
			d_input(&value);
			insert_sorted(&listA, value);
		}
		printf("In list B's size.\n");
		d_input(&countB);
		printf("In list B.\n");
		for (int i = 0; i < countB; i++)
		{
			printf("B[%d]: ", i);
			d_input(&value);
			insert_sorted(&listB, value);
		}
		print_list(&listA);print_list(&listB);

		re_list_menu:;
		printf("Dynamic linked list.\n1. intersection_slow\n"
		"2. intersection_fast\n""3. union\n4.difference\n5.if A is sub of B\n"
						  "6.if B is sub of A\n");
		switch(hd_input())
		{
			case 1:
				intersection_slow(&listA, &listB);break;
			case 2:
				intersection_fast(&listA,&listB);break;
			case 3:
				union_func(&listA, &listB);break;
			case 4:
				difference(&listA,&listB);
			case 5:
				printf(is_subset(&listA,&listB)?"True\n":"False\n");break;
			case 6:
				printf(is_subset(&listB,&listA)?"True\n":"False\n");break;
			default: goto exit_list_menu;
		}
		goto re_list_menu;
		exit_list_menu:;
		free_list(&listA);
		free_list(&listB);

		return 0;
	}

	void init_list(LinkedList* list)
	{
		// ReSharper disable once CppZeroConstantCanBeReplacedWithNullptr
		list->head = NULL;
		list->size = 0;
	}

	void insert_sorted(LinkedList* list, const int value)
	{
		//分配一个新node,包含连接和数据
		Node* new_node = (Node*)malloc(sizeof(Node));
		if (new_node == NULL){printf("Memory error.\n");}
		//给node注入数据
		new_node->data = value;
		//注入连接
		new_node->next = NULL;
		//创建一个指向头的临时指针
		Node* current = list->head;
		//流转（遍历）使用的指针
		Node* previous = NULL;
		//如果如果如果 内存状态正常&&输入旳值比当前找到的值大
		while (current != NULL && value > current->data)
		{
			//向后挪一个
			previous = current;
			current = current->next;
		}
		//元素如果一样就删掉
		if (current != NULL && current->data == value)
		{
			free(new_node); // 释放重复节点的内存
			return;
		}
		//head是NULL,则如果前一个是NULL,代表挂在head上
		if (previous == NULL)
		{
			//插入到头部
			//先连接后面的
			new_node->next = list->head;
			//再重连
			list->head = new_node;
		}
		else
		{
			//插入到中间或尾部
			//先连接新节点
			new_node->next = previous->next;
			//再断开旧节点并且串起来
			previous->next = new_node;
		}
		//手动增加大小
		list->size++;
	}

	Node* get_node_at_index(const LinkedList* list, const int index)
	{
		if(index < 0 || index >= list->size)
		{
			printf("Error of index.\n");
			return NULL;
		}
		//临时指针
		Node* current = list->head;
		int count = 0;

		while(current)
		{
			//找到第i个节点，返回其指针
			if (count == index){return current;}
			// 移动到下一个节点
			current = current->next;
			count++;
		}
		return NULL; // 理论上不会执行到这里，除非链表大小错误
	}

	void print_list(const LinkedList* list)
	{
		//如果不存在
		if (!list->size)
		{
			printf("∅\n");
			return;
		}
		printf("{ ");
		//创建一个临时指针用于读取数据
		const Node* current = list->head;
		//只要存在就执行
		while(current)
		{
			//读取数据
			printf("%d ", current->data);
			//往后挪
			current = current->next;
		}
		printf("}\n");
	}

	void free_list(LinkedList* list)
	{
		//临时目击者
		Node* current = list->head;
		//大记忆恢复术！打不死就接着打
		while(current)
		{
			//先把头指针杀了就读不到后面的东西了，
			//所以给留一个后继
			Node* next_node = current->next;
			//弄死
			free(current);
			//攻守之势异也
			current = next_node;
		}
		//Reversio in nihilum
		list->head = NULL;
		list->size = 0;
	}


	void intersection_slow(const LinkedList* listA, const LinkedList* listB)
	{
		int sizeA = listA->size;
		int sizeB = listB->size;
		LinkedList listOut;
		init_list(&listOut);
		int i = 0, j = 0, k = 0;int digits = 0;
		while (i < sizeA && j < sizeB)
		{
			if(get_node_at_index(listA,i)->data < get_node_at_index(listB,j)->data)
			{
				i++;
			}
			else if(get_node_at_index(listA,i)->data > get_node_at_index(listB,j)->data)
			{
				j++;
			}
			else
			{
				insert_sorted(&listOut,get_node_at_index(listA,i)->data);
				i++;j++;k++;
			}
		}
		printf("Intersection:\n");
		print_list(&listOut);
		free_list(&listOut);
	}

	void intersection_fast(const LinkedList* listA, const LinkedList* listB)
	{
		const Node* ptrA = listA->head;
		const Node* ptrB = listB->head;
		LinkedList listOut;
		init_list(&listOut);
		while (ptrA && ptrB)
		{
			if (ptrA->data < ptrB->data)
			{
				// A 的元素较小，移动 A 的指针
				ptrA = ptrA->next;
			}
			else if (ptrA->data > ptrB->data)
			{
				// B 的元素较小，移动 B 的指针
				ptrB = ptrB->next;
			}
			else
			{
				// 找到相同元素，插入到结果链表
				insert_sorted(&listOut, ptrA->data);
				// 同时移动两个指针
				ptrA = ptrA->next;
				ptrB = ptrB->next;
			}
		}
		printf("Intersection:\n");
		print_list(&listOut);
		free_list(&listOut);
	}

	void union_func(const LinkedList* listA, const LinkedList* listB)
	{
		const Node* ptrA = listA->head;
		const Node* ptrB = listB->head;
		LinkedList listOut;
		init_list(&listOut);
		while (ptrA && ptrB)
		{
			if (ptrA->data < ptrB->data)
			{
				insert_sorted(&listOut, ptrA->data);
				// A 的元素较小，移动 A 的指针
				ptrA = ptrA->next;
			}
			else if (ptrA->data > ptrB->data)
			{
				insert_sorted(&listOut, ptrB->data);
				// B 的元素较小，移动 B 的指针
				ptrB = ptrB->next;
			}
			else
			{
				// 找到相同元素，插入到结果链表
				insert_sorted(&listOut, ptrA->data);
				// 同时移动两个指针
				ptrA = ptrA->next;
				ptrB = ptrB->next;
			}
		}

		//以下为ai修复内容
		// 修复点1: 处理 listA 中剩余的元素
		while (ptrA)
		{
			insert_sorted(&listOut, ptrA->data);
			ptrA = ptrA->next;
		}

		// 修复点2: 处理 listB 中剩余的元素
		while (ptrB)
		{
			insert_sorted(&listOut, ptrB->data);
			ptrB = ptrB->next;
		}

		printf("Union:\n");
		print_list(&listOut);
		free_list(&listOut);
	}

	void difference(const LinkedList* listA, const LinkedList* listB)
	{
		const Node* ptrA = listA->head;
		const Node* ptrB = listB->head;
		LinkedList listOut;
		init_list(&listOut);
		while (ptrA && ptrB)
		{
			if (ptrA->data < ptrB->data)
			{
				insert_sorted(&listOut, ptrA->data);
				// A 的元素较小，移动 A 的指针
				ptrA = ptrA->next;
			}
			else if (ptrA->data > ptrB->data)
			{
				// B 的元素较小，移动 B 的指针
				ptrB = ptrB->next;
			}
			else
			{
				ptrA = ptrA->next;
				ptrB = ptrB->next;
			}
		}

		//ai修复
		// 修复点: 处理 listA 中剩余的元素
		// 这些元素肯定是 A 独有的，因为 listB 已经遍历完了
		while (ptrA)
		{
			insert_sorted(&listOut, ptrA->data);
			ptrA = ptrA->next;
		}

		printf("Difference:\n");
		print_list(&listOut);
		free_list(&listOut);
	}

	bool is_subset(const LinkedList* listA, const LinkedList* listB)
	{
		int sizeA = listA->size;
		int sizeB = listB->size;
		LinkedList listOut;
		init_list(&listOut);
		// 如果 A 的大小大于 B 的大小，那么 A 不可能是 B 的子集
		if (sizeA > sizeB)
		{
			return false;
		}

		const Node* ptrA = listA->head;
		const Node* ptrB = listB->head;

		while (ptrA && ptrB)
		{
			if (ptrA->data < ptrB->data)
			{
				// 如果 A 的当前元素小于 B 的当前元素，说明 A 的这个元素在 B 中不存在。
				// 因为已经排序，所以 arrA[i] 永远找不到匹配了。
				return false;
			}
			else if (ptrA->data > ptrB->data)
			{
				// B 的当前元素比 A 的小，继续在 B 中寻找下一个元素。
				ptrB = ptrB->next;
			}
			else
			{
				ptrA = ptrA->next;
				ptrB = ptrB->next;
			}
		}
		// 如果 ptrA 已经遍历到末尾，说明 A 的所有元素都在 B 中找到了匹配
		return (ptrA == NULL);
	}
}
