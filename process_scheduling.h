#ifndef PROCESS_SCHEDULING_H_INCLUDED
#define PROCESS_SCHEDULING_H_INCLUDED

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
#define TIME_SLICE 2
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

//�������ȼ��Խ��̽�������
void sort();
//�����̼����������
void join();
//������̶��еĳ���
int length();
//�����̼�����У����������ȼ�����
void input1();
void input2();
//��ý��̵���ϸ��Ϣ
void get_info(PCB *p);
//���н��̵���,���÷���ռ�ľ�̬���ȼ������㷨
void execute1();
//������ת�����㷨
void execute2();
//��ʾ���̵���ϸ��Ϣ
void *display(void *arg);
//����ִ�н��������ٽ���
void destory(PCB *p);


#endif // PROCESS_SCHEDULING_H_INCLUDED
