
#include"includes.h"
#include"system_stm32f10x.h"

#define STACK_SIZE 100
#define Q_SIZE 5
OS_EVENT *sem1;
INT8U i, ret, myqueue[Q_SIZE], front = -1, rear = -1;

OS_STK insert_Stk1[STACK_SIZE];
OS_STK insert_Stk2[STACK_SIZE];
OS_STK delete_Stk[STACK_SIZE];

void insert1(void * );
void insert2(void * );
void delete(void* );

int main(void)
{
	OSInit();
	ret = OSTaskCreate(&insert1,(void *)0, &insert_Stk1[STACK_SIZE - 1] , 1);
	if(ret != OS_ERR_NONE)
		printf("Insert1 creation failed\n\r");

	ret = OSTaskCreate(&insert2,(void *)0, &insert_Stk2[STACK_SIZE - 1] , 2);
	if(ret != OS_ERR_NONE)
		printf("Insert2 creation failed\n\r");

	ret = OSTaskCreate(&delete,(void *)0, &delete_Stk[STACK_SIZE - 1] , 3);
		if(ret != OS_ERR_NONE)
			printf("Deletion creation failed\n\r");

	sem1 = OSSemCreate(5);

	OSStart();

    while(1)
    {
    	printf("hello\n\r");
    }
}

void insert1(void* ar)
{
	INT8U j=0, err;

	OS_CPU_SysTickInit(SystemCoreClock/OS_TICKS_PER_SEC);

	for(;;)
	{
			OSSemPend(&sem1, 100 , &err);

			if(((front == 0) && (rear == Q_SIZE-1)) || (front == rear+1))
			{
			  printf("Queue is full\n\r");
			  return;
			}
			else if(rear == -1)
			{
			   front++;
			   rear++;
			}
			else if((front > 0) && (rear == Q_SIZE-1))
			   rear = 0;
			else
			   rear++;

			myqueue[rear] = 'a' + j;
			j++;

		printf("IN Insert1 %s\n\r", myqueue);
		OSTimeDly(0.5*OS_TICKS_PER_SEC);
	}
}

void insert2(void* ar)
{
	INT8U j=0, err;

	for(;;)
	{
		OSSemPend(&sem1, 100 , &err);

		if(((front == 0) && (rear == Q_SIZE-1)) || (front == rear+1))
		{
		  printf("Queue is full\n\r");
		  return;
		}
		else if(rear == -1)
		{
		   front++;
		   rear++;
		}
		else if((front > 0) && (rear == Q_SIZE-1))
		   rear = 0;
		else
		   rear++;

		myqueue[rear] = 'A' + j;
		j++;

		printf("\nIN Insert2 %s\n\r", myqueue);
		OSTimeDly(0.7*OS_TICKS_PER_SEC);

	}
}


void delete(void* ar)
{
	INT8U j=0, res;

	for(;;)
	{
			res = OSSemPost(&sem1);
			if((front == -1) && (rear == -1))
			  printf("Queue is empty\n\r");
			else if(front == rear)
			{
			   printf("\n %c deleted\n\r", myqueue[front]);
			   front = -1;
			   rear = -1;
			}
			/*else if((front == 0) && (rear == Q_SIZE - 1))
			{
				printf("Queue is full\n\r");
			    rear--;
			}*/
			else
			{
			  printf("\n %c deleted..\n\r", myqueue[front]);
			//  myqueue[front] = '\0';
			  front++;
			}
			if(front < rear)
			{
				for(i=front; i<rear;i++)
					printf(" %c", myqueue[i]);
			}
			else if(front == rear)
				printf(" %c", myqueue[rear]);
			else
			{
				i= front;
				while(i != rear)
				{
					if(i == Q_SIZE - 1)
					{
						printf(" %c", myqueue[i]);
						i = -1;
					}
					else
					{
						printf(" %c", myqueue[i]);
					}
					i++;
				}
				printf(" %c", myqueue[i]);

			}
			/*
		for(i= front; i<=rear; i++)
		{

		}*/
		//printf("After Deletion string is %s\n\r", myqueue);
		OSTimeDly(1*OS_TICKS_PER_SEC);

	}
}





