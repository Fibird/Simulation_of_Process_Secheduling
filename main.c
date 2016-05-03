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
/*����״̬*/
#define READY 0
#define RUNNING 1
#define BLOCK -1
//ʱ��Ƭ��С
#define TIME_SLICE 1
//����һ��pcb�ṹ��
typedef struct pcb
{
    char name[10];
    int state;     //����״̬
    int priority;   //���ȼ�
    int reqtime;
    int runtime;
    struct pcb* link;
} PCB;
char message[] = "This is another thread.";
static PCB *ready, *ptr;

/*****************************************************************************/
//�������ȼ��Խ��̽�������
void sort();
//������̶��еĳ���
int length();
//�����̼�����У����������ȼ�����
void input();
//��ý��̵���ϸ��Ϣ
void get_info(PCB *p);
//���н��̵���,���÷���ռ�ľ�̬���ȼ������㷨
void execute();
//������ת�����㷨
void execute2();
//��ʾ���̵���ϸ��Ϣ
void *display(void *arg);
//����ִ�н��������ٽ���
void destory(PCB *p);
/*****************************************************************************/

int main()
{
    pthread_t disp_thread;
    void *dis_result;
    //������̵���ϸ��Ϣ
    input();
    //������һ���������ڼ��ӽ��̵��ȵ���ϸ��Ϣ
    pthread_create(&disp_thread, NULL, display, (void *)message);
    //execute();
    execute2();
    //ȷ���߳�disp_thread�������̽���ǰ����
    pthread_join(disp_thread, &dis_result);
    printf("All processes are finished.\n");
    return 0;
}

//�������ȼ��Խ��̽�������
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
                //�����ȼ���ͣ�����뵽��β
                //���Ҷ�β
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
        //��������
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
            //��������ʱ���ʱ��Ƭȡ��
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
