#ifndef PROCESS_SCHEDULING_H_INCLUDED
#define PROCESS_SCHEDULING_H_INCLUDED

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
#define TIME_SLICE 2
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

//根据优先级对进程进行排序
void sort();
//将进程加入就绪队列
void join();
//计算进程队列的长度
int length();
//将进程加入队列，并按照优先级排序
void input1();
void input2();
//获得进程的详细信息
void get_info(PCB *p);
//进行进程调度,采用非抢占的静态优先级调度算法
void execute1();
//采用轮转调度算法
void execute2();
//显示进程的详细信息
void *display(void *arg);
//进程执行结束，销毁进程
void destory(PCB *p);


#endif // PROCESS_SCHEDULING_H_INCLUDED
