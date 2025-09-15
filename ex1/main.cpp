#include "cSafeInput.h"
#include "prototypes.h"


int main(int argc, char *argv[])
{
	re_full_menu:;
	printf("1.C fixed array.\n2.C dynamic array.\n"
		"3.C dynamic linked list.\n4.C++.\n");
	switch(hd_input())
	{
		case 1: cFixedArray::main_CFA();break;
		case 2: cDynamicArray::main_CDA();break;
		case 3: cDyLinkedList::main_CDLL();break;
		case 4: cppSet::main_CppS();break;
		default: goto full_exit;
	}
	goto re_full_menu;
	full_exit:;
	return 0;
}