#include"includes.h"
#include"stm32f10x.h"

#define STACK_SIZE 100

OS_STK task_stk1[STACK_SIZE];
OS_STK task_stk2[STACK_SIZE];

void task1(void *arg);
void task2(void *arg);
int main(void)
{
	INT8U ret;
	OSInit();
	ret = OSTaskCreate(&task1, (void*)0, &task_stk1[STACK_SIZE - 1], 0);
	if(ret != OS_ERR_NONE)
		printf("Task1 creation failed..\n\r");
	//OSStart();
	ret = OSTaskCreate(&task2, (void*)0, &task_stk2[STACK_SIZE - 1], 1);
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
		OSTimeDly(1*OS_TICKS_PER_SEC);
	}
}
void task2(void *arg)
{
	OS_CPU_SysTickInit(SystemCoreClock/OS_TICKS_PER_SEC);
	for( ; ; )
	{
		printf("In Task2..\n\r");
		OSTimeDly(1*OS_TICKS_PER_SEC);
	}
}
