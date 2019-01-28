#include"includes.h"
#include"system_stm32f10x.h"
#include"OS_cpu.h"

void pro1(void *arg);
void pro2(void *arg);
void con(void *arg);

#define STACK_SIZE 100
OS_STK task_stk1[100];
OS_STK task_stk2[100];
OS_STK task_stk3[100];

INT8U a=0, i;

int main(void)
{
	INT8U ret;
	OSInit();
	ret=OSTaskCreate(&pro1,(void *)0,&task_stk1[100-1],1);
	if(ret!=OS_ERR_NONE)
	{
		printf("task(producer 1) creation failed\n\r");
	}
	ret=OSTaskCreate(&pro2,(void *)0,&task_stk2[100-1],2);
	if(ret!=OS_ERR_NONE)
	{
		printf("task(producer 2) creation failed\n\r");
	}
	ret=OSTaskCreate(&con,(void *)0,&task_stk3[100-1],0);
	if(ret!=OS_ERR_NONE)
	{
		printf("task(consumer) creation failed\n\r");
	}

	OSStart();
    while(1)
    {
    	printf("hello..\n\r");
    }
}


void pro1(void *arg)
{
	OS_CPU_SR cpu_sr;
	for( ; ; )
	{
		printf("producer 1\n\r");
		OS_ENTER_CRITICAL();
		a = a+10;
		OS_EXIT_CRITICAL();
		OSTimeDly(5*OS_TICKS_PER_SEC);
	}

}

void pro2(void *arg)
{
	OS_CPU_SR cpu_sr;
	for( ; ; )
	{
		printf("producer 2\n\r");
		OS_ENTER_CRITICAL();
		a = a+5;
		OS_EXIT_CRITICAL();
		OSTimeDly(0.7*OS_TICKS_PER_SEC);
	}

}

void con(void *arg)
{
	OS_CPU_SysTickInit(SystemCoreClock/OS_TICKS_PER_SEC);
	for( ; ; )
	{
		printf("consumer\n\r");
		printf("%d\n\r",a);
		OSTimeDly(2*OS_TICKS_PER_SEC);
	}

}
