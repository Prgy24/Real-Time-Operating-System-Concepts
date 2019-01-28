
#include"includes.h"
#include"system_stm32f10x.h"

OS_STK task_Stk_low[100];
OS_STK task_Stk_medium[100];
OS_STK task_Stk_high[100];


void task_low(void *arg);
void task_medium(void *arg);
void task_high(void *arg);

OS_EVENT *Mutex;

INT8U ret,err;
int main(void)
{
	OSInit();

	ret = OSTaskCreate(&task_low,(void *)0,&task_Stk_low[100-1],2);
	if(ret != OS_ERR_NONE)
		printf("task_low creation failed\n\r");
	ret = OSTaskCreate(&task_medium,(void *)0,&task_Stk_medium[100-1],1);
	if(ret != OS_ERR_NONE)
		printf("task_medium creation failed\n\r");
	ret = OSTaskCreate(&task_high,(void *)0,&task_Stk_high[100-1],0);
	if(ret != OS_ERR_NONE)
		printf("task_high creation failed\n\r");

	Mutex = OSMutexCreate(0, &err);
	OSStart();

    while(1)
    {
    }
}

void task_high(void* ar)
{
	INT8U err, res;
	OS_CPU_SysTickInit(SystemCoreClock/OS_TICKS_PER_SEC);

	for(;;)
	{
		OSTimeDly(1*OS_TICKS_PER_SEC);
		OSMutexPend(Mutex, 0, &err);

		printf("IN TASK_high\n\r");

		OSMutexPost(Mutex);
		OSTimeDly(1*OS_TICKS_PER_SEC);

	}
}

void task_medium(void* ar)
{
	for(;;)
	{
		OSTimeDly(1*OS_TICKS_PER_SEC);
		INT8U count, i;

		printf("IN TASK_medium\n\r");
		for(i=0; i<5; i++)
		{
		}

		OSTimeDly(1*OS_TICKS_PER_SEC);
	}
}

void task_low(void* ar)
{
	INT8U i, count=0, err, res;
	for(;;)
	{
		 OSMutexPend(Mutex, 0, &err);

		/*if(err != OS_ERR_NONE)
		{
			printf("error\n\r");
		}*/
		printf("IN TASK_low\n\r");
		for(i=0; i<100; i++)
		{
			//OSTimeDly(0.1*OS_TICKS_PER_SEC);
			printf(" %d",i);

		}
		printf("sema relesed in low\n\r");
		OSMutexPost(Mutex);
		OSTimeDly(1*OS_TICKS_PER_SEC);

	}
}



