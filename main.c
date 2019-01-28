#include"includes.h"
#include"system_stm32f10x.h"

OS_STK task_Stk1[100];
OS_STK task_Stk2[100];
OS_STK task_Stk3[100];
OS_STK task_Stk4[100];


void task1(void *arg);
void task2(void *arg);
void task3(void *arg);
void task4(void *arg);

INT8U ret;

int main(void)
{
	OSInit();
	ret = OSTaskCreate(&task1,(void *)0,&task_Stk1[100-1],1);
	if(ret != OS_ERR_NONE)
		printf("task1 creation failed\n\r");

	OSStart();

    while(1)
    {
    }
}

void task1(void* ar)
{
	OS_CPU_SysTickInit(SystemCoreClock/OS_TICKS_PER_SEC);
	ret = OSTaskCreate(&task2,(void *)0,&task_Stk2[100-1],2);
	if(ret != OS_ERR_NONE)
		printf("task2 creation failed\n\r");

	ret = OSTaskCreate(&task3,(void *)0,&task_Stk3[100-1],3);
	if(ret != OS_ERR_NONE)
		printf("task3 creation failed\n\r");

	ret = OSTaskCreate(&task4,(void *)0,&task_Stk4[100-1],4);
	if(ret != OS_ERR_NONE)
		printf("task4 creation failed\n\r");

	for(;;)
	{
		printf("IN TASK1\n\r");
		OSTimeDly(1*OS_TICKS_PER_SEC);
	}
}

void task2(void* ar)
{
	INT8U cond=0;

	OS_CPU_SysTickInit(SystemCoreClock/OS_TICKS_PER_SEC);
	for(;;)
	{
		printf("IN TASK2\n\r");
		OSTaskDel(OS_PRIO_SELF);
	}
}

void task3(void* ar)
{
	OS_CPU_SysTickInit(SystemCoreClock/OS_TICKS_PER_SEC);
	for(;;)
	{
		printf("IN TASK3\n\r");
		OSTaskDel(OS_PRIO_SELF);
	}
}

void task4(void* ar)
{
	OS_CPU_SysTickInit(SystemCoreClock/OS_TICKS_PER_SEC);
	for(;;)
	{
		printf("IN TASK4\n\r");
		OSTaskDel(OS_PRIO_SELF);
	}
}




