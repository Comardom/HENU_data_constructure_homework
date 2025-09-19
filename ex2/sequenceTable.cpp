//
// Created by comardom on 25-9-16.
//
#include <algorithm>

#include "cppSafeInput.h"
#include <random>
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


	static const int demoA[100] = {1,1,2,3,4,5,6,6,6,7,8,10,51,66,852,6666};
	static const int demoB[100] = {2,6,7,7,7,8,15,21,66,888,889,8899,10035};

	void initList(Sqlist &sqlist);
	Sqlist* c_initList();
	void destroyList(Sqlist &sqlist);
	void clearList(Sqlist &sqlist);
	int insert_for_index(Sqlist &sqlist, int index, T value);
	void print_list(const Sqlist &sqlist);
	int insert_non_decreasing_sort(Sqlist &sqlist, T value);
	void find_index_of_value(const Sqlist &sqlist, const T &value);
	T find_previous(const Sqlist &sqlist, const T &value);
	T find_next(const Sqlist &sqlist, const T &value);
	void delete_for_index(Sqlist &sqlist, int index);
	void delete_for_element(Sqlist &sqlist, const T &value);
	void sortList(Sqlist &sqlist);
	void merge(const Sqlist &sqlist1, const Sqlist &sqlist2, Sqlist &sqlist3);

	int main_SQ()
	{
		Sqlist *list_ptrA = nullptr;
		Sqlist *list_ptrB = nullptr;
		Sqlist *list_ptrC = nullptr;
		for(;;)
		{
			std::cout<<"1.init 2.destroy 3.clear 4.is null 5.length 6.index->element "
			<<"7.element->index 8.previous 9.next 10.insert in index 11.delete in index "
			<<"12.delete for element 13.sort 14.print 15.merge"<<std::endl;
			switch(hd_input_s())
			{
				case 1:
					if(list_ptrA)
					{
						std::cout<<"Plz destroy and recreat it."
						<<std::endl;
					}
					else
					{
						list_ptrA = new Sqlist;
						initList(*list_ptrA);

						std::cout << "Init. use demoA to populate? (1 for Yes, 0 for No)"
						<< std::endl;
						if (hd_input_s())
						{
							for(int i = 0; i < 16; i++)
							{
								insert_for_index(*list_ptrA, i, demoA[i]);
							}
							list_ptrA->length = 16;
							std::cout << "List populated with demoA." << std::endl;
						}
						std::cout << "Init." << std::endl;
					}
					break;
				case 2:
					if(list_ptrA)
					{
						destroyList(*list_ptrA);
						delete list_ptrA;
						list_ptrA = nullptr;
						std::cout<<"Destruction."<<std::endl;
					}
					else
					{
						std::cout<<"No creation."<<std::endl;
					}
					break;
				case 3:
					if(list_ptrA)
					{
						clearList(*list_ptrA);
					}
					else
					{
						std::cout<<"No creation."<<std::endl;
					}
					break;
				case 4:
					std::cout << (list_ptrA?"False":"True") << std::endl;
					break;
				case 5:
					if(list_ptrA)
					{
						std::cout << list_ptrA->length << std::endl;
					}
					else
					{
						std::cout<<"No creation."<<std::endl;
					}
					break;
				case 6:
					if(list_ptrA)
					{
						std::cout << "index." << std::endl;
						int index = 0;
						num_input_s(index);
						std::cout << list_ptrA->data[index] << std::endl;
					}
					else
					{
						std::cout<<"No creation."<<std::endl;
					}
					break;
				case 7:
					std::cout << "default all to find." << std::endl;
					if(list_ptrA)
					{
						std::cout << "what index?" << std::endl;
						int tmp_index;
						num_input_s(tmp_index);
						find_index_of_value(*list_ptrA, tmp_index);
					}
					else
					{
						std::cout<<"No creation."<<std::endl;
					}
					break;
				case 8:
					if(list_ptrA)
					{
						std::cout << "what element?" << std::endl;
						int tmp_index;
						num_input_s(tmp_index);
						std::cout <<find_previous(*list_ptrA, tmp_index)<< std::endl;
					}
					else
					{
						std::cout<<"No creation."<<std::endl;
					}
					break;
				case 9:
					if(list_ptrA)
					{
						std::cout << "what element?" << std::endl;
						int tmp_index;
						num_input_s(tmp_index);
						std::cout <<find_next(*list_ptrA, tmp_index)<< std::endl;
					}
					else
					{
						std::cout<<"No creation."<<std::endl;
					}
					break;
				case 10:
					std::cout << "index? why not sorted? 1 to sorted, 0 to index.";
					if(hd_input_s())
					{
						if(list_ptrA)
						{
							T tmp_value;
							num_input_s(tmp_value);
							insert_non_decreasing_sort(*list_ptrA, tmp_value);
							std::cout << "Insert(sort)." << std::endl;
						}
						else
						{
							std::cout<<"No creation."<<std::endl;
						}
					}
					else
					{
						if(list_ptrA)
						{
							std::cout << "index?" << std::endl;
							int tmp_index;
							T tmp_value;
							num_input_s(tmp_index);
							std::cout << "value?" << std::endl;
							num_input_s(tmp_value);
							insert_for_index(*list_ptrA,tmp_index,tmp_value);
							std::cout << "Insert." << std::endl;
						}
						else
						{
							std::cout<<"No creation."<<std::endl;
						}
					}
					break;
				case 11:
					if(list_ptrA)
					{
						std::cout << "index?" << std::endl;
						int tmp_index;
						num_input_s(tmp_index);
						delete_for_index(*list_ptrA, tmp_index);
						std::cout << "Delete." << std::endl;
					}
					else
					{
						std::cout<<"No creation."<<std::endl;
					}
					break;
				case 12:
					if(list_ptrA)
					{
						std::cout << "what element?" << std::endl;
						int tmp_value;
						num_input_s(tmp_value);
						delete_for_element(*list_ptrA, tmp_value);
						std::cout << "Delete." << std::endl;
					}
					else
					{
						std::cout<<"No creation."<<std::endl;
					}
					break;
				case 13:
					if(list_ptrA)
					{
						sortList(*list_ptrA);
						std::cout << "Sort." << std::endl;
					}
					else
					{
						std::cout<<"No creation."<<std::endl;
					}
					break;
				case 14:
					print_list(*list_ptrA);
					break;
				case 15:
					list_ptrB = new Sqlist;
					initList(*list_ptrB);
					list_ptrC = new Sqlist;
					initList(*list_ptrC);
					for(int i = 0; i < 13; i++)
					{
						insert_for_index(*list_ptrB, i, demoB[i]);
					}
					list_ptrB->length=13;
					std::cout << "List populated with demoB." << std::endl;

					merge(*list_ptrA,*list_ptrB,*list_ptrC);
					print_list(*list_ptrC);

					if(list_ptrA)
					{
						destroyList(*list_ptrA);
						delete list_ptrA;
						list_ptrA = nullptr;
						std::cout<<"Destruction."<<std::endl;
					}
					if(list_ptrB)
					{
						destroyList(*list_ptrB);
						delete list_ptrB;
						list_ptrB = nullptr;
						std::cout<<"Destruction."<<std::endl;
					}
					if(list_ptrC)
					{
						destroyList(*list_ptrC);
						delete list_ptrC;
						list_ptrC = nullptr;
						std::cout<<"Destruction."<<std::endl;
					}
					break;
				default:
					if(list_ptrA)
					{
						destroyList(*list_ptrA);
						delete list_ptrA;
						list_ptrA = nullptr;
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

	void clearList(Sqlist &sqlist)
	{
		sqlist.length = 0; // 将长度设为0，表示顺序表为空
	}

	int insert_for_index(Sqlist &sqlist, int index, const T value)
	{
		if(sqlist.length>=SQ_SIZE)
		{
			std::cout<<"SIZEERR"<<std::endl;
			return -1;
		}
		if(index>sqlist.length || index<0)
		{
			std::cout<<"INDEXERR"<<std::endl;
			return -1;
		}
		for(int i=sqlist.length;i>index;i--)
		{
			sqlist.data[i]=sqlist.data[i-1];
		}
		sqlist.data[index]=value;
		sqlist.length++;
		return 0;
	}

	void find_index_of_value(const Sqlist &sqlist, const T &value)
	{
		for(int i=0;i<sqlist.length;i++)
		{
			if(sqlist.data[i]==value)
			{
				std::cout<<i<<" "<<std::endl;
			}
		}
	}

	short randRandRand()
	{
		// 1. 创建静态的随机数源和引擎，只初始化一次
		static std::random_device rd;
		static std::mt19937 gen(rd());

		// 2. 创建静态的均匀整数分布器
		static std::uniform_int_distribution<> distrib(-1, 1);

		// 3. 调用分布器生成随机数
		return static_cast<short>(distrib(gen));
	}

	T find_previous(const Sqlist &sqlist, const T &value)
	{
		if(sqlist.length==0)
		{
			std::cout<<"SIZEERR"<<std::endl;
			return -1;
		}
		short randRandRand();
		std::cout<<"default is to make sure it is sorted,"
		<<" so if disorder, back one of it."<<std::endl;
		int where = 0;
		if(randRandRand())
		{
			for(int left=0,right=sqlist.length-1;left<=right;)
			{
				int middle = (left+right)/2;
				if(sqlist.data[middle]==value)
				{
					where=middle;
					if(where == 0)
					{
						std::cout<<"CROSSINGLINEERR"<<std::endl;
						return -1;
					}
					goto find_previous_binary_success;
				}
				else if(sqlist.data[middle]<value)
				{
					left=middle+1;
				}
				else if(sqlist.data[middle]>value)
				{
					right=middle-1;
				}
				else
				{
					std::cout<<"ELEMINVALID"<<std::endl;
					return -1;
				}
			}
			if(false)
			{
				find_previous_binary_success:return sqlist.data[where-1];
			}
		}
		else
		{
			for(int i=0;i<sqlist.length;i++)
			{
				if(sqlist.data[i]==value)
				{
					where=i;
					if(where == 0)
					{
						std::cout<<"CROSSINGLINEERR"<<std::endl;
						return -1;
					}
					goto find_previous_not_binary_success;
				}
			}
			if(false)
			{
				find_previous_not_binary_success:return sqlist.data[where-1];
			}
			return -1;
		}
		std::cout<<"PROCESSERR"<<std::endl;
		return -1;
	}

	T find_next(const Sqlist &sqlist, const T &value)
	{
		if(sqlist.length==0)
		{
			std::cout<<"SIZEERR"<<std::endl;
			return -1;
		}
		short randRandRand();
		std::cout<<"default is to make sure it is sorted,"
		<<" so if disorder, back one of it."<<std::endl;
		int where = 0;
		if(randRandRand())
		{
			for(int left=0,right=sqlist.length-1;left<=right;)
			{
				int middle = (left+right)/2;
				if(sqlist.data[middle]==value)
				{
					where=middle;
					if(where == sqlist.length)
					{
						std::cout<<"CROSSINGLINEERR"<<std::endl;
						return -1;
					}
					goto find_previous_binary_success;
				}
				else if(sqlist.data[middle]<value)
				{
					left=middle+1;
				}
				else if(sqlist.data[middle]>value)
				{
					right=middle-1;
				}
				else
				{
					std::cout<<"ELEMINVALID"<<std::endl;
					return -1;
				}
			}
			if(false)
			{
				find_previous_binary_success:return sqlist.data[where+1];
			}
		}
		else
		{
			for(int i=0;i<sqlist.length;i++)
			{
				if(sqlist.data[i]==value)
				{
					where=i;
					if(where == sqlist.length)
					{
						std::cout<<"CROSSINGLINEERR"<<std::endl;
						return -1;
					}
					goto find_previous_not_binary_success;
				}
			}
			if(false)
			{
				find_previous_not_binary_success:return sqlist.data[where+1];
			}
			return -1;
		}
		std::cout<<"PROCESSERR"<<std::endl;
		return -1;
	}

	int insert_non_decreasing_sort(Sqlist &sqlist, const T value)
	{
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

	void delete_for_index(Sqlist &sqlist, const int index)
	{
		if (index < 0 || index >= sqlist.length)
		{
			std::cout << "CROSSINGLINEERR" << std::endl;
			return;
		}
		for(int i=index;i<sqlist.length-1;i++)
		{
			sqlist.data[i]=sqlist.data[i+1];
		}
		sqlist.length--;
	}

	void delete_for_element(Sqlist &sqlist, const T &value)
	{
		if(sqlist.length==0)
		{
			std::cout<<"SIZEERR"<<std::endl;
			return;
		}
		std::cout<<"default is to make sure it is sorted,"
		<<" so if disorder, delete one of it."<<std::endl;
		for(int i=0;i<sqlist.length;i++)
		{
			if(sqlist.data[i]==value)
			{
				delete_for_index(sqlist,i);
				i--;
			}
		}
	}

	void sortList(Sqlist &sqlist)
	{
		if(sqlist.length > 1)
		{
			// 使用 std::sort 对 data 数组进行排序
			// 起始迭代器是 data，结束迭代器是 data + length
			std::sort(sqlist.data, sqlist.data + sqlist.length);
		}
	}

	void print_list(const Sqlist &sqlist)
	{
		if (!sqlist.length)
		{
			std::cout<<"∅"<<std::endl;
			return;
		}
		std::cout<<"{ ";
		for(int i=0;i<sqlist.length;i++)
		{
			std::cout<<sqlist.data[i]<<" ";
		}
		std::cout<<"}"<<std::endl;
	}
	void merge(const Sqlist &sqlist1, const Sqlist &sqlist2, Sqlist &sqlist3)
	{
		if(sqlist1.length + sqlist2.length > sqlist3.capacity)
		{
			std::cout << "SIZEERR" << std::endl;
			return;
		}
		int i = 0, j = 0, k = 0;
		while(i<sqlist1.length&&j<sqlist2.length)
		{
			if(sqlist1.data[i] < sqlist2.data[j])
			{
				if(k>0 && sqlist3.data[k-1] == sqlist1.data[i]){i++;}
				else{sqlist3.data[k++] = sqlist1.data[i++];}
			}
			else if(sqlist1.data[i] > sqlist2.data[j])
			{
				if(k>0 && sqlist3.data[k-1] == sqlist2.data[j]){j++;}
				else{sqlist3.data[k++] = sqlist2.data[j++];}
			}
			else
			{
				if(k>0 && sqlist3.data[k-1] == sqlist1.data[i])
				{
					i++;
					j++;
				}
				else
				{
					sqlist3.data[k++] = sqlist1.data[i++];
					j++;
				}
			}
		}
		while(i<sqlist1.length)
		{
			if(k>0 && sqlist3.data[k-1] == sqlist1.data[i]){i++;}
			else{sqlist3.data[k++] = sqlist1.data[i++];}
		}
		while(j<sqlist2.length)
		{
			if(k>0 && sqlist3.data[k-1] == sqlist2.data[j]){j++;}
			else{sqlist3.data[k++] = sqlist2.data[j++];}
		}
		sqlist3.length = k;
	}
}
