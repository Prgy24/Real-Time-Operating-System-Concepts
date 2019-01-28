
#include"includes.h"
#include"system_stm32f10x.h"

OS_STK task_master[100];
OS_STK task_slave1[100];
OS_STK task_slave2[100];



void master(void *arg);
void slave1(void *arg);
void slave2(void *arg);


INT8U ret;

int main(void)
{
	OSInit();

	ret = OSTaskCreate(&slave1,(void *)0,&task_slave1[100-1], 0);
	if(ret != OS_ERR_NONE)
		printf("slave1 creation failed\n\r");

	ret = OSTaskCreate(&slave2,(void *)0,&task_slave2[100-1], 1);
	if(ret != OS_ERR_NONE)
		printf("slave2 creation failed\n\r");

	ret = OSTaskCreate(&master,(void *)0,&task_master[100-1], 2);
		if(ret != OS_ERR_NONE)
			printf("master creation failed\n\r");

	OSStart();

    while(1)
    {
    	printf("Hi...\n\r");
    }
}


void slave1(void* ar)
{
	//OS_CPU_SysTickInit(SystemCoreClock/OS_TICKS_PER_SEC);

	for(;;)
	{
		printf("IN slave1\n\r");
		//OSTimeDly(1*OS_TICKS_PER_SEC);
		OSTaskSuspend(0);
	}
}


void slave2(void* ar)
{
	//OS_CPU_SysTickInit(SystemCoreClock/OS_TICKS_PER_SEC);

	for(;;)
	{
		printf("IN slave2\n\r");
		//OSTimeDly(1*OS_TICKS_PER_SEC);
		OSTaskSuspend(1);
	}
}


void master(void* ar)
{

	OS_CPU_SysTickInit(SystemCoreClock/OS_TICKS_PER_SEC);

	for(;;)
	{
		printf("IN master\n\r");

		 OSTimeDly(0.5*OS_TICKS_PER_SEC);
		 OSTaskResume(0);
		 OSTimeDly(0.7*OS_TICKS_PER_SEC);
		 OSTaskResume(1);
	}
}



