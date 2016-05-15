#include <stdio.h>
#include "process_scheduling.h"
static PCB *ready, *ptr;
//根据优先级对进程进行排序
void sort()
{
    PCB *cur, *pre;
    int ins_flag = 0;

    if ((ready == NULL) || (ptr->priority > ready->priority))
    {
        ptr->link = ready;
        ready = ptr;
    }
    else
    {
        cur = ready;
        pre = cur->link;
        while (pre != NULL)
        {
            if (ptr->priority > pre->priority)
            {
                ptr->link = pre;
                cur->link = ptr;
                pre = NULL;
                ins_flag = 1;
            }
            else
            {
                //若优先级最低，则插入到队尾
                //查找队尾
                cur = cur->link;
                pre = pre->link;
            }
        }
        if (ins_flag == 0)
        {
            cur->link = ptr;
        }
    }
}

void join()
{
    PCB *p = NULL;

    if (ready == NULL)
    {
        ready = ptr;
    }
    else
    {
        p = ready;
        while (p->link != NULL)
        {
            p = p->link;
        }
        p->link = ptr;
    }

}

int length()
{
    int length = 0;
    PCB *p = ready;
    while(p!=NULL)
    {
        length++;
        p =p->link;
    }

    return length;
}

void input1()
{
    int i, num;
    printf("Please enter the number of the process: ");
    scanf("%d", &num);

    for (i = 0; i < num; i++)
    {
        printf("the ID of process:No.%d\n", i);
        ptr = getpch(PCB);
        printf("Please enter the name of the process: ");
        scanf("%s", ptr->name);
        printf("Please enter the priority of the process: ");
        scanf("%d", &ptr->priority);
        printf("Please enter the time of the process need: ");
        scanf("%d", &ptr->reqtime);
        printf("\n");
        ptr->runtime = 0;
        ptr->state = READY;
        ptr->link = NULL;
        sort();
    }
}

void input2()
{
    int i, num;
    printf("Please enter the number of the process: ");
    scanf("%d", &num);

    for (i = 0; i < num; i++)
    {
        printf("the ID of process:No.%d\n", i);
        ptr = getpch(PCB);
        printf("Please enter the name of the process: ");
        scanf("%s", ptr->name);
        printf("Please enter the priority of the process: ");
        scanf("%d", &ptr->priority);
        printf("Please enter the time of the process need: ");
        scanf("%d", &ptr->reqtime);
        printf("\n");
        ptr->runtime = 0;
        ptr->state = READY;
        ptr->link = NULL;
        join();
    }
}

void *display(void *arg)
{
    PCB *p = NULL;
    while (ready != NULL)
    {
        p = ready;
        printf("**********************PROCESSES INFO***********************\n");
        while (p != NULL)
        {
            get_info(p);
            p = p->link;
        }
        Sleep(1000);
        //清屏操作
        system("CLS");
    }
    pthread_exit(0);
    return NULL;
}

void get_info(PCB *p)
{
    printf("name\tstate\tpriority\trequire time\trunning time\n");
    printf("%s\t", p->name);
    switch (p->state)
    {
    case 0:
        printf("Ready\t");
        break;
    case 1:
        printf("Running\t");
        break;
    case -1:
        printf("Block\t");
        break;
    default:
        printf("UNknow\t");
        break;
    }
    printf("%d\t\t", p->priority);
    printf("%d\t\t", p->reqtime);
    printf("%d\t", p->runtime);
    printf("\n");
}

void destory(PCB *p)
{
    PCB *pre, *cur;
    pre = cur = ready;
    if (p == ready)
    {
        ready = p->link;
    }
    while (!(cur->name == p->name || cur == NULL))
    {
        pre = cur;
        cur = cur->link;
    }
    if (cur != NULL)
    {
        pre->link = cur->link;
    }
    else
    {
        pre->link = NULL;
    }
    p = NULL;
    free(p);
}

void execute1()
{
    int remainder = 0;
    while (ready != NULL)
    {
        ready->state = 1;
        PCB *p = ready;
        while (1)
        {
            //进程所需时间对时间片取余
            remainder = p->reqtime % TIME_SLICE;
            if ((p->reqtime - p->runtime) == remainder)
            {
                p->runtime += remainder;
            }
            else
            {
                p->runtime += TIME_SLICE;
            }
            Sleep(1000 * TIME_SLICE);
            if (p->runtime == p->reqtime)
            {
                destory(p);
                break;
            }
        }
    }
}

void execute2()
{
    PCB *p = NULL;
    int remainder = 0;
    while (ready != NULL)
    {
        p = ready;
        while (p != NULL)
        {
            //进程所需时间对时间片取余
            remainder = p->reqtime % TIME_SLICE;
            if ((p->reqtime - p->runtime) == remainder)
            {
                p->runtime += remainder;
            }
            else
            {
                p->runtime += TIME_SLICE;
            }
            p->state = 1;
            Sleep(1000 * TIME_SLICE);
            p->state = 0;
            if (p->runtime == p->reqtime)
            {
                destory(p);
            }
            p = p->link;
        }
    }
}
