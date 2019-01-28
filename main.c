
#include"includes.h"
#include"system_stm32f10x.h"

OS_STK task_Stk1[100];
OS_STK task_Stk2[100];


void task1(void *arg);
void task2(void *arg);

INT8U ret;

int main(void)
{
	OSInit();
	ret = OSTaskCreate(&task1,(void *)0,&task_Stk1[100-1],1);
	if(ret != OS_ERR_NONE)
		printf("task1 creation failed\n\r");

	ret = OSTaskCreate(&task2,(void *)0,&task_Stk2[100-1],2);
	if(ret != OS_ERR_NONE)
		printf("task2 creation failed\n\r");

	OSStart();

    while(1)
    {
    	printf("hello\n\r");
    }
}

void task1(void* ar)
{
	INT8U count=0;

	OS_CPU_SysTickInit(SystemCoreClock/OS_TICKS_PER_SEC);

	for(;;)
	{
		count++;
		if(count > 3)
		   OSTaskDel(OS_PRIO_SELF);
		printf("IN TASK1\n\r");
		OSTimeDly(1*OS_TICKS_PER_SEC);
	}
}

void task2(void* ar)
{
	INT8U count=0;

	OS_CPU_SysTickInit(SystemCoreClock/OS_TICKS_PER_SEC);
	for(;;)
	{
		count++;
		if(count > 3)
		    OSTaskDel(OS_PRIO_SELF);
		 printf("IN TASK2\n\r");
		 OSTimeDly(1*OS_TICKS_PER_SEC);

	}
}






