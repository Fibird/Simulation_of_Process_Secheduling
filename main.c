/**********************************************************
 Author: Chaoyang Liu
 E-mail: chaoyanglius@outlook.com or chaoyanglius@gmail.com
 date:   May 1st, 2016
 **********************************************************/

#include "process_scheduling.h"

int main()
{
    char message[] = "This is another thread.";
    pthread_t disp_thread;
    void *dis_result;
    int a;
    printf("----------------------command---------------------\n");
    printf("1: static priority-driven nonpreemptive scheduling\n");
    printf("2: round robin scheduling\n");
    printf("--------------------------------------------------\n");
    printf("Please enter your commmand: ");
    scanf("%d", &a);
    switch (a)
    {
    case 1:
        //输入进程的详细信息
        input1();
        //清屏操作
        system("CLS");
        //创建另一个进程用于监视进程调度的详细信息
        pthread_create(&disp_thread, NULL, display, (void *)message);
        execute1();
        //确保线程disp_thread在主进程结束前结束
        pthread_join(disp_thread, &dis_result);
        break;
    case 2:
        //输入进程的详细信息
        input2();
        //清屏操作
        system("CLS");
        //创建另一个进程用于监视进程调度的详细信息
        pthread_create(&disp_thread, NULL, display, (void *)message);
        execute2();
        //确保线程disp_thread在主进程结束前结束
        pthread_join(disp_thread, &dis_result);
        break;
    default:
        printf("Error,please check your command!\n");
        break;
    }
    printf("All processes are finished.\n");
    return 0;
}

