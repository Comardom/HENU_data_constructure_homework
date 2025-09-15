//
// Created by comardom on 25-9-11.
//
#include "../constData.h"
#include "../cppSafeInput.h"
void init_array(int *arrA,int *arrB,bool if_use_const_data)
{
	if(if_use_const_data)
	{
		for(int i=0;i<ARR_SIZE;i++)
		{
			arrA[i]=TEST_INT_ARR_A[i];
			arrB[i]=TEST_INT_ARR_B[i];
		}
	}
	else
	{
		printf("In %d int for A.\n",ARR_SIZE);
		for(int i=0;i<ARR_SIZE;i++)
		{
			num_input_s(*(arrA+i));
		}
		printf("In %d int for B.\n",ARR_SIZE);
		for(int i=0;i<ARR_SIZE;i++)
		{

			num_input_s(*(arrB+i));
		}
	}
}
void print_array(const int *arr)
{
	for(int i=0;i<ARR_SIZE;i++)
	{
		std::cout<<arr[i]<<" ";
	}
	std::cout<<"\b"<<std::endl;
}
