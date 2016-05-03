/**********************************************************
 Author: Chaoyang Liu
 E-mail: chaoyanglius@outlook.com or chaoyanglius@gmail.com
 date:   May 1st, 2016
 **********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <pthread.h>

#define getpch(type) (type*)malloc(sizeof(type))
/*进程状态*/
#define READY 0
#define RUNNING 1
#define BLOCK -1
//时间片大小
#define TIME_SLICE 1
//定义一个pcb结构体
typedef struct pcb
{
    char name[10];
    int state;     //进程状态
    int priority;   //优先级
    int reqtime;
    int runtime;
    struct pcb* link;
} PCB;
char message[] = "This is another thread.";
static PCB *ready, *ptr;

/*****************************************************************************/
//根据优先级对进程进行排序
void sort();
//计算进程队列的长度
int length();
//将进程加入队列，并按照优先级排序
void input();
//获得进程的详细信息
void get_info(PCB *p);
//进行进程调度,采用非抢占的静态优先级调度算法
void execute();
//采用轮转调度算法
void execute2();
//显示进程的详细信息
void *display(void *arg);
//进程执行结束，销毁进程
void destory(PCB *p);
/*****************************************************************************/

int main()
{
    pthread_t disp_thread;
    void *dis_result;
    //输入进程的详细信息
    input();
    //创建另一个进程用于监视进程调度的详细信息
    pthread_create(&disp_thread, NULL, display, (void *)message);
    //execute();
    execute2();
    //确保线程disp_thread在主进程结束前结束
    pthread_join(disp_thread, &dis_result);
    printf("All processes are finished.\n");
    return 0;
}

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

void input()
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

void *display(void *arg)
{
    PCB *p = NULL;
    while (ready != NULL)
    {
        p = ready;
        printf("****************PROCESSES INFO****************\n");
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

void execute()
{
    while (ready != NULL)
    {
        ready->state = 1;
        PCB *p = ready;
        while (1)
        {
            p->runtime += TIME_SLICE;
            Sleep(1000 * TIME_SLICE);
            if (p->runtime == p->reqtime)
            {
                ready = p->link;
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
        ready->state = 1;
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

            Sleep(1000 * TIME_SLICE);
            if (p->runtime == p->reqtime)
            {
                destory(p);
            }
            p = p->link;
        }
    }
}
