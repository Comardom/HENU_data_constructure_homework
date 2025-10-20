//
// Created by comardom on 25-9-24.
//
#include "cppSafeInput.h"
namespace singlyLinkedList
{
	template <typename T>
	struct Node {
		T data;     // 存储数据元素
		Node* next;   // 指向下一个节点的指针
		explicit Node(const T& data) : data(data), next(nullptr) {}
	};
	//链表本身
	template <typename T>
	struct LinkedList {
		Node<T> * head;
		Node<T> * tail;
		int size;
	};


	template <typename T>
	void init_or_remake_list(LinkedList<T> * list);
	template <typename T>
	void print_list(const LinkedList<T> * list);
	template <typename T>
	void delete_list(LinkedList<T> * list);
	template <typename T>
	T get_node_at_index(const LinkedList<T> * list, int index);
	template <typename T>
	int find_index_of_value(const LinkedList<T> *list, T value);
	template <typename T>
	void insert_at_i(LinkedList<T> *list, int index, T value);
	template <typename T>
	void delete_for_index(LinkedList<T> *list, int index);
	template<typename T>
	void insert_head_or_tail(LinkedList<T> *list, T value, bool is_head);

	int main()
	{
		// LinkedList<int> * listA = nullptr;
		auto *listA = new LinkedList<int>();
		goto_re_menu:;
		std::cout << "1.init.\n2.destroy.\n3.clear.\n4.length.\n5.value in index.\n"
		<< "6.index for value.\n7.previous.\n8.next.\n9.insert at i.\n10.delete at i.\n"
		<< "11.print.\n12.insert(head or tail).\n13.reverse.\n14.sort."
		<< std::endl;
		switch(hd_input_s())
		{
			case 1:
				init_or_remake_list(listA);
				std::cout<<"init"<<std::endl;
				break;
			case 2:
			case 3:
				if(listA)
				{
					// ReSharper disable once CppDFAUnreachableCode
					delete_list(listA);
					std::cout<<"destroy or clear"<<std::endl;
				}
				else
				{
					std::cerr<<"list is empty"<<std::endl;
				}
				break;
			case 4:
				// ReSharper disable once CppDFAUnreachableCode
				if(listA)std::cout << listA->size << std::endl;break;
			case 5:
				if(listA)
				{
					// ReSharper disable once CppDFAUnreachableCode
					int index=0;
					num_input_s(index);
					std::cout << get_node_at_index(listA,index) << std::endl;
				}
				else
				{
					std::cerr<<"list is empty"<<std::endl;
				}
				break;
			case 6:
				if(listA)
				{
					// ReSharper disable once CppDFAUnreachableCode
					int value;num_input_s(value);//此处使用int作为示例
					std::cout << find_index_of_value(listA,value) << std::endl;
				}
				else
				{
					std::cerr<<"list is empty"<<std::endl;
				}
				break;
			case 7:
				if(listA)
				{
					// ReSharper disable once CppDFAUnreachableCode
					int value_for_previous;num_input_s(value_for_previous);
					std::cout <<
						get_node_at_index(listA,
							find_index_of_value(listA,value_for_previous-1))
					<< std::endl;
				}
				else
				{
					std::cerr<<"list is empty"<<std::endl;
				}
				break;
			case 8:
				if(listA)
				{
					// ReSharper disable once CppDFAUnreachableCode
					int value_for_next;num_input_s(value_for_next);
					std::cout <<
						get_node_at_index(listA, find_index_of_value(listA,value_for_next+1))
					<< std::endl;
				}
				else
				{
					std::cerr<<"list is empty"<<std::endl;
				}
				break;
			case 9:
				if(listA)
				{
					// ReSharper disable once CppDFAUnreachableCode
					std::cout<<"i"<<std::endl;int i;num_input_s(i);
					if(i<0||i>listA->size){std::cerr<<"SIZEERR"<<std::endl;break;}
					std::cout<<"value"<<std::endl;int value;num_input_s(value);
					insert_at_i(listA,i,value);
					std::cout<<"insert."<<std::endl;
				}
				else
				{
					std::cerr<<"list is empty"<<std::endl;
				}
				break;
			case 10:
				if(listA)
				{
					// ReSharper disable once CppDFAUnreachableCode
					std::cout<<"i"<<std::endl;int i;num_input_s(i);
					if(i<0||i>listA->size){std::cerr<<"SIZEERR"<<std::endl;break;}
					std::cout<<"value"<<std::endl;int value;num_input_s(value);
					delete_for_index(listA,i);
					std::cout<<"delete."<<std::endl;
				}
				else
				{
					std::cerr<<"list is empty"<<std::endl;
				}
				break;
			case 11:
				if(listA)
				{
					// ReSharper disable once CppDFAUnreachableCode
					print_list(listA);
				}
				else
				{
					std::cerr<<"list is empty"<<std::endl;
				}
				break;
			case 12:
				if(listA)
				{
					// ReSharper disable once CppDFAUnreachableCode
					std::cout<<"head for 0, tail for 1."
					<<std::endl;
					if(hd_input_s())
					{
						std::cout<<"value.";int value;num_input_s(value);
						insert_head_or_tail(listA,value,false);
						std::cout<<"insert."<<std::endl;
					}
					else
					{
						std::cout<<"value.";int value;num_input_s(value);
						insert_head_or_tail(listA,value,true);
						std::cout<<"insert."<<std::endl;
					}
				}
				else
				{
					std::cerr<<"list is empty"<<std::endl;
				}
				break;
			case 13:
			case 14:
			default:goto goto_exit_main;
		}
		goto goto_re_menu;
		goto_exit_main:;
		delete listA;
		return 0;
	}


	template <typename T>
	void init_or_remake_list(LinkedList<T> * list)
	{
		list->head = new Node<T>(T{});
		list->head->next = nullptr;
		list->tail = list->head;
		list->size = 0;
	}

	template <typename T>
	void print_list(const LinkedList<T> * list)
	{
		//如果不存在
		if (!list->size)
		{
			std::cout << "∅" << std::endl;
			return;
		}
		std::cout << "{ " << std::endl;
		//创建一个临时指针用于读取数据
		const Node<T> * current = list->head->next;
		//只要存在就执行
		while(current)
		{
			//读取数据
			std::cout << current->data << " ";
			//往后挪
			current = current->next;
		}
		std::cout << "}" << std::endl;
	}

	template <typename T>
	void delete_list(LinkedList<T> * list)
	{
		//临时目击者
		const Node<T> * current = list->head->next;
		//大记忆恢复术！打不死就接着打
		while(current)
		{
			//先把头指针杀了就读不到后面的东西了，
			//所以给留一个后继
			const Node<T> * next_node = current->next;
			//弄死
			delete current;
			//攻守之势异也
			current = next_node;
		}
		//Reversio in nihilum
		list->head->next = nullptr;
		list->tail = list->head;
		list->size = 0;
	}

	template <typename T>
	T get_node_at_index(const LinkedList<T> * list, const int index)
	{
		if(index < 0 || index >= list->size)
		{
			std::cerr << "INDEXERR" << std::endl;
			return -1;
		}
		//临时指针
		Node<T> * current = list->head->next;
		int count = 0;

		while(current)
		{
			//找到第i个节点，返回其指针
			if (count == index){return current->data;}
			// 移动到下一个节点
			current = current->next;
			count++;
		}
		return -1; // 理论上不会执行到这里，除非链表大小错误
	}

	template <typename T>
	int find_index_of_value(const LinkedList<T> *list, const T value)
	{
		//临时指针
		const Node<T> * current = list->head->next;
		int count = 0;
		while(current)
		{
			if (current->data == value){return count;}
			// 移动到下一个节点
			current = current->next;
			count++;
		}
		return -1; //元素不存在
	}

	template <typename T>
	void delete_for_index(LinkedList<T> *list, const int index)
	{
		//临时指针
		Node<T> * pathfinder = nullptr;
		Node<T> * assistant = nullptr;

		if(index==0)
		{
			list->head->next = list->head->next->next;
			if(list->head->next==nullptr)
			{
				list->tail = list->head;
			}
			--list->size;
		}
		else
		{
			pathfinder = list->head;
			for(int count_for_pioneer = 0;
				pathfinder && count_for_pioneer < index;
				pathfinder = pathfinder->next, count_for_pioneer++){}
			assistant = pathfinder->next;
			if(assistant)
			{
				pathfinder->next = assistant->next;
				if(assistant==list->tail)
				{
					list->tail = pathfinder;
				}
				assistant->next=nullptr;
				delete assistant;
				--list->size;
			}
		}
	}

	template <typename T>
	void insert_at_i(LinkedList<T> *list, const int index, const T value)
	{
		Node<T> * current = nullptr;
		if(index==0)
		{
			auto *tmp = new Node<T>(value);
			tmp->next = list->head->next;
			list->head->next = tmp;
			if(list->tail==list->head)
			{
				list->tail = tmp;
			}
		}
		else
		{
			current = list->head;
			for(int count=0;
			current && count<index;
			count++,current=current->next){}
			auto *tmp = new Node<T>(value);
			tmp->next = current->next;
			current->next = tmp;
			if(tmp->next==nullptr)
			{
				list->tail = tmp;
			}
		}
		++list->size;
	}

	template<typename T>
	void insert_head_or_tail(LinkedList<T> *list,
		const T value, const bool is_head)
	{
		if(is_head)
		{
			insert_at_i(list, 0, value);
		}
		else
		{
			insert_at_i(list, list->size, value);
		}
	}

	//从这里开始
}