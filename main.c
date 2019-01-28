#include"includes.h"
#include"stm32f10x.h"

#define STACK_SIZE 100

OS_STK task_stk1[STACK_SIZE];
OS_STK task_stk2[STACK_SIZE];
OS_STK task_stk3[STACK_SIZE];
OS_STK task_stk4[STACK_SIZE];
OS_STK task_stk5[STACK_SIZE];

void task1(void *arg);
void task2(void *arg);
void task3(void *arg);
void task4(void *arg);
void task5(void *arg);


int main(void)
{
	INT8U ret;
	OSInit();

	ret = OSTaskCreate(&task1, (void*)0, &task_stk1[STACK_SIZE - 1], 1);
	if(ret != OS_ERR_NONE)
		printf("Task1 creation failed..\n\r");

	ret = OSTaskCreate(&task2, (void*)0, &task_stk2[STACK_SIZE - 1], 2);
	if(ret != OS_ERR_NONE)
		printf("Task2 creation failed..\n\r");

	ret = OSTaskCreate(&task3, (void*)0, &task_stk3[STACK_SIZE - 1], 3);
	if(ret != OS_ERR_NONE)
		printf("Task1 creation failed..\n\r");

	ret = OSTaskCreate(&task4, (void*)0, &task_stk4[STACK_SIZE - 1], 4);
	if(ret != OS_ERR_NONE)
		printf("Task2 creation failed..\n\r");

	ret = OSTaskCreate(&task5, (void*)0, &task_stk5[STACK_SIZE - 1], 5);
	if(ret != OS_ERR_NONE)
		printf("Task2 creation failed..\n\r");

	OSStart();

    while(1)
    {
    	printf("Hello..\n\r");
    }
}

void task1(void *arg)
{
	OS_CPU_SysTickInit(SystemCoreClock/OS_TICKS_PER_SEC);
	for( ; ; )
	{
		printf("In Task1..\n\r");
		OSTimeDly(0.2*OS_TICKS_PER_SEC);
	}
}
void task2(void *arg)
{
	OS_CPU_SysTickInit(SystemCoreClock/OS_TICKS_PER_SEC);
	for( ; ; )
	{
		printf("In Task2..\n\r");
		OSTimeDly(0.4*OS_TICKS_PER_SEC);
	}
}

void task3(void *arg)
{
	OS_CPU_SysTickInit(SystemCoreClock/OS_TICKS_PER_SEC);
	for( ; ; )
	{
		printf("In Task3..\n\r");
		OSTimeDly(0.6*OS_TICKS_PER_SEC);
	}
}
void task4(void *arg)
{
	OS_CPU_SysTickInit(SystemCoreClock/OS_TICKS_PER_SEC);
	for( ; ; )
	{
		printf("In Task4..\n\r");
		OSTimeDly(0.8*OS_TICKS_PER_SEC);
	}
}

void task5(void *arg)
{
	OS_CPU_SysTickInit(SystemCoreClock/OS_TICKS_PER_SEC);
	for( ; ; )
	{
		printf("In Task5..\n\r");
		OSTimeDly(1*OS_TICKS_PER_SEC);
	}
}
