#include"includes.h"
#include"system_stm32f10x.h"
#include"OS_cpu.h"

void task1(void *arg);
void task2(void *arg);

#define STACK_SIZE 100

OS_STK task_stk1[STACK_SIZE];
OS_STK task_stk2[STACK_SIZE];

OS_EVENT *mybox;
INT8U data[20];

void *msg;

int main(void)
{
	INT8U ret, err;
	OSInit();

	ret=OSTaskCreate(&task1, (void *)0 , &task_stk1[STACK_SIZE-1] , 0);
	if(ret!=OS_ERR_NONE)
		printf("Producer creation failed\n\r");

	ret=OSTaskCreate(&task2, (void *)0 , &task_stk2[STACK_SIZE-1] , 1);
	if(ret!=OS_ERR_NONE)
	{
		printf("Consumer creation failed\n\r");
	}

	mybox = OSMboxCreate((void *)0);
	printf("%d\n\r", mybox);
	OSStart();

    while(1)
    {
    	printf("hello..\n\r");
    }
}


void task1(void *arg)
{
	INT8U err, buff[20];
	void *msg;

	OS_CPU_SysTickInit(SystemCoreClock/OS_TICKS_PER_SEC);

	for( ; ; )
	{
		printf("task 1\n\r");

		strcpy(data,"Hello Sneha");
		OSMboxPost(mybox, (void*)&data);

		/*msg = OSMboxPend(mybox, 100, &err);
		if(msg==0)
		   printf("Error \n\r");
		else
		strcpy(buff,(INT8U*)msg);*/
		printf("Message is: %s\n\r", data);
		OSTimeDly(1*OS_TICKS_PER_SEC);
	}
}
void task2(void *arg)
{
		INT8U err, buff[20];
		void *msg;

		OS_CPU_SysTickInit(SystemCoreClock/OS_TICKS_PER_SEC);

		for( ; ; )
		{
			printf("task 2\n\r");

			msg = OSMboxPend(mybox, 0 , &err);

			if(msg==0)
			   printf("Error \n\r");
			else
			strcpy(buff,(INT8U*)msg);

			printf("Message is: %s\n\r", buff);
			OSTimeDly(1*OS_TICKS_PER_SEC);
		}
}
