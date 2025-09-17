//
// Created by comardom on 25-9-16.
//
#include "cppSafeInput.h"
#define SQ_SIZE 100
namespace sequenceTable
{
	//应报告要求，使用C风格的typedef,而不是C++的泛型
	typedef int T;

	typedef struct {
		T *data;
		int length;
		int capacity;
	}Sqlist;


	void initList(Sqlist &sqlist);
	Sqlist* c_initList();
	void destroyList(Sqlist &sqlist);

	int main_SQ()
	{
		Sqlist *list_ptr = nullptr;
		for(;;)
		{
			std::cout<<"1.init 2.destroy 3.clear 4.is null 5.length 6.index->element "
		<<"7.element->index 8.previous 9.next 10.insert in index 11.delete in index "
		<<"12.delete for element 13.sort 14.print 15.merge"<<std::endl;
			switch(hd_input_s())
			{
				case 1:
					if(list_ptr)
					{
						std::cout<<"Plz destroy and recreat it."
						<<std::endl;
					}
					else
					{
						list_ptr = new Sqlist;
						initList(*list_ptr);
						//下面这个是C语言版本，默认使用C++版本
						// list_ptr = c_initList();
						std::cout<<"Init."<<std::endl;
					}
					break;
				case 2:
					if(list_ptr)
					{
						destroyList(*list_ptr);
						delete list_ptr;
						list_ptr = nullptr;
						std::cout<<"Destruction."<<std::endl;
					}
					else
					{
						std::cout<<"No creation."<<std::endl;
					}
					break;
				case 3:
					// TODO: 处理 case 3
					break;
				case 4:
					// TODO: 处理 case 4
					break;
				case 5:
					// TODO: 处理 case 5
					break;
				case 6:
					// TODO: 处理 case 6
					break;
				case 7:
					// TODO: 处理 case 7
					break;
				case 8:
					// TODO: 处理 case 8
					break;
				case 9:
					// TODO: 处理 case 9
					break;
				case 10:
					// TODO: 处理 case 10
					break;
				case 11:
					// TODO: 处理 case 11
					break;
				case 12:
					// TODO: 处理 case 12
					break;
				case 13:
					// TODO: 处理 case 13
					break;
				case 14:
					// TODO: 处理 case 14
					break;
				case 15:
					// TODO: 处理 case 15
					break;
				default:
					if(list_ptr)
					{
						destroyList(*list_ptr);
						delete list_ptr;
						list_ptr = nullptr;
						std::cout<<"Destruction."<<std::endl;
					}
					return 0;
			}
		}
	}

	//C++中使用引用
	void initList(Sqlist &sqlist)
	{
		// sqlist.data = static_cast<T *>(malloc(sizeof(T) * SQ_SIZE));
		//使用C++风格的new而不是malloc
		sqlist.data = new T[SQ_SIZE];
		if(!sqlist.data){exit(1);}
		sqlist.length = 0;
		sqlist.capacity = SQ_SIZE;
	}

	//这是C语言使用的
	Sqlist* c_initList()
	{
		auto *sqlist = (Sqlist*)malloc(sizeof(Sqlist));
		//上面是C++11的表达，以下为C++98写法
		// Sqlist *sqlist = (Sqlist*)malloc(sizeof(Sqlist));
		if(sqlist == NULL){return NULL;}
		sqlist->data = (T*)malloc(sizeof(T) * SQ_SIZE);
		if (sqlist->data == nullptr)
		{
			free(sqlist); // 如果数据分配失败，释放结构体内存
			return NULL;
		}
		sqlist->length = 0;
		sqlist->capacity = SQ_SIZE;
		return sqlist;
	}
	//以下代码默认使用引用，不再赘述

	void clearList(Sqlist &sqlist)
	{
		sqlist.length = 0; // 将长度设为0，表示顺序表为空
	}

	void destroyList(Sqlist &sqlist)
	{
		if(sqlist.data)
		{
			// free(sqlist.data);
			//使用C++风格的delete而不是free
			delete[] sqlist.data;
			sqlist.data = nullptr;
		}
		else
		{
			//主菜单提供了check功能，此处不再重复输出
			// std::cout<<"No creation."<<std::endl;
		}
		sqlist.length = 0;
		sqlist.capacity = 0;
	}

	int insert_non_decreasing_sort(Sqlist &sqlist, const T value)
	{
		// int tmp_index = 0;
		if(sqlist.length>=SQ_SIZE)
		{
			std::cout<<"SIZEERR"<<std::endl;
			return -1;
		}
		//初始元素插入
		if(sqlist.length==0)
		{
			sqlist.data[0] = value;
			sqlist.length++;
			return 0;
		}
		//寻找在哪里插入数据,默认寻找到结束
		for(int i=0;i<sqlist.length;i++)
		{
			if(sqlist.data[i]>=value)
			{
				// for(int j=0;j<(sqlist.length-i);j++);
				//上面这个不方便，因为是从最后一位开始挪
				//下面这个sqlist.length其实是sqlist.length-1再加了个一
				//为了保证索引在有数据的后一位（空位）
				//这样才有地方存数据
				for(int j=sqlist.length;j>i;j--)
				{
					//向后依次挪，保证非递减
					sqlist.data[j]=sqlist.data[j-1];
				}
				sqlist.data[i]=value;
				sqlist.length++;
				return 0;
			}
		}
		//如果循环结束，说明value比所有元素都大，插入到末尾
		//此处的length同理为length-1+1得到
		sqlist.data[sqlist.length] = value;
		sqlist.length++;
		return 0;
	}
}
