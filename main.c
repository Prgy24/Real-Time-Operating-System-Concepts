
#include"includes.h"
#include"system_stm32f10x.h"


#define STACK_SIZE 100
OS_EVENT *sem1;
INT8U i, ret, count=0, mystring[20];

OS_STK write_Stk1[STACK_SIZE];
OS_STK write_Stk2[STACK_SIZE];

void write1(void *arg);
void write2(void *arg);


int main(void)
{
	OSInit();
	ret = OSTaskCreate(&write1,(void *)0,&write_Stk1[STACK_SIZE - 1], 1);
	if(ret != OS_ERR_NONE)
		printf("task1 creation failed\n\r");

	ret = OSTaskCreate(&write2,(void *)0,&write_Stk2[STACK_SIZE - 1], 2);
	if(ret != OS_ERR_NONE)
		printf("task2 creation failed\n\r");

	sem1 = OSSemCreate(1);

	OSStart();

    while(1)
    {
    	printf("hello\n\r");
    }
}

void write1(void* ar)
{
	INT8U j=0, err;

	OS_CPU_SysTickInit(SystemCoreClock/OS_TICKS_PER_SEC);

	for(;;)
	{
		OSSemPend(&sem1, 100 , &err);
		mystring[i] = 'a' + j;
		i++;
		j++;
		count++;
		if(count > 20)
			OSTaskDel(OS_PRIO_SELF);
		printf("IN write1 %s\n\r", mystring);
		OSTimeDly(1*OS_TICKS_PER_SEC);
	}
}

void write2(void* ar)
{
	INT8U j=0, res;

	for(;;)
	{
		res = OSSemPost(&sem1);
		mystring[i] = '1' + j;
		i++;
		j++;
		count++;
		if(count > 19)
			OSTaskDel(OS_PRIO_SELF);

		printf("IN write2 %s\n\r", mystring);

		 OSTimeDly(1*OS_TICKS_PER_SEC);

	}
}






