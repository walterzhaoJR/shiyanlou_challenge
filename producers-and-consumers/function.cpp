#include <iostream>
#include <zconf.h>
#include <unistd.h>
#include <stdlib.h>

#include "CarPack.hpp"
#include "constant.hpp"
#include "function.hpp"

//static void* car_in_handler(void* cp_in)
void* car_in_handler(void* cp_in)
{
    CarPack* temp = NULL;
    unsigned int seed = 0;

    temp = (CarPack*)cp_in;
    //pthread_barrier_wait 表明,线程已经完成工作,等待其他线程赶来
    /*
     * pthread_barrier_*其实只做且只能做一件事，就是充当栏杆（barrier意为栏杆)。
     * 形象的说就是把先后到达的多个线程挡在同一栏杆前，直到所有线程到齐，然后撤下栏杆同时放行。
     * 1）init函数负责指定要等待的线程个数；
     * 2）wait()函数由每个线程主动调用，它告诉栏杆“我到起跑线前了”。
     * wait(）执行末尾栏杆会检查是否所有人都到栏杆前了，如果是，栏杆就消失所有线程继续执行下一句代码；
     * 如果不是，则所有已到wait()的线程停在该函数不动，剩下没执行到wait()的线程继续执行；
     * 3）destroy函数释放init申请的资源。
     * */
    pthread_barrier_wait(&temp->bar);

    while(true)
    {
        //将线程随机挂起一段时间,表示车辆到来的随机性
        usleep(rand_r(&seed)%ONE_SECOND);
        //生产者往停车场停车需要读写 ourpark 数据，由于有2个生产者两个消费者，
        // 所以应该采用互斥的方式读写，所以要首先获取 ourpark 的锁
        pthread_mutex_lock(&temp->lock);

        //循环等待有车位
        while(temp->occupied == temp->capacity)
        {
            //条件变量用来等待一个条件变为真。在生产者这边需要等待停车场有空位,即等待条件 temp->space 为真。
            // 如果暂时条件不为真，则需要释放锁，等待消费者的消费，然后再重新获取锁
            pthread_cond_wait(&temp->space,&temp->lock);//有空的位置才可以停车
        }

        //插入一个车辆
        temp->carpark[temp->nextin] = rand_r(&seed)%RANGE;

        //变量更新
        temp->occupied++;
        temp->nextin++;
        temp->nextin %= temp->capacity;
        temp->cars_in++;

        //可能有人在等可有车可以取 消费,放松信号
        pthread_cond_signal(&temp->car);

        //释放锁
        pthread_mutex_unlock(&temp->lock);
    }

    return (void*) NULL;
}
void* car_out_handler(void* carpack_out)
//static void* car_out_handler(void* carpack_out)
{
    CarPack* temp = NULL;
    unsigned int seed = 0;
    temp = (CarPack*) carpack_out;
    pthread_barrier_wait(&temp->bar);

    for(;;)
    {
        //将线程随机挂起一段时间,模拟车辆到来的随机性
        usleep(rand_r(&seed)%ONE_SECOND);

        pthread_mutex_lock(&temp->lock);

        /*
         * 获取锁之后,temp->occupied 变量,此时如果车辆为0
         * pthread_cond_wait()进行繁忙操作,释放锁,供其他线程使用
         * 知道&temp->car条件变量再次将锁所做
         * */

        while(temp->occupied == 0)
        {
            pthread_cond_wait(&temp->car,&temp->lock);
        }

        //更行变量
        temp->occupied--;
        temp->nextout++;
        temp->nextout %= temp->capacity;
        temp->cars_out++;


        //可能有人在等待空车位,发送temp->space 条件变量
        pthread_cond_signal(&temp->space);

        pthread_mutex_unlock(&temp->lock);
    }

    return (void*)NULL;
}

void* monitor(void* carpark_in)
//static void* monitor(void* carpark_in)
{
    CarPack* temp = NULL;
    temp = (CarPack*)carpark_in;

    for(;;)
    {
        sleep(PERIOD);

        pthread_mutex_lock(&temp->lock);
        /* 证明锁机制保证线程实现的生产者消费者模型正确的方式是：
        temp->cars_in - temp->cars_out - temp->occupied == 0，即总的进来的车 ==
        总的开出去的车 +　停车场现有的车 */

        std::cout<<"----------carpark------data-----------------"<<std::endl;
        std::cout<<"occupied"<<temp->occupied<<std::endl;
        std::cout<<"cars_in"<<temp->cars_in<<std::endl;
        std::cout<<"cars_out"<<temp->cars_out<<std::endl;

        pthread_mutex_unlock(&temp->lock);
    }

    return (void*)NULL ;
}

void initialise(CarPack *cp, int size)
//static void initialise(CarPack *cp, int size)
{

    cp->occupied = cp->nextin = cp->nextout = cp->cars_in = cp->cars_out = 0;
    cp->capacity = size;  //设置停车场的大小

    //cp->carpark = (int *)malloc(cp->capacity * sizeof(*cp->carpark));
    cp->carpark = new int[cp->capacity];

    // 初始化线程屏障，NUM_THREADS 表示等待 NUM_THREADS = 4 个线程同步执行
    pthread_barrier_init(&cp->bar, NULL, NUM_THREADS);


    if (cp->carpark == NULL) {
        std::cout<<"new error"<<std::endl;
        exit(1);
    }

    srand((unsigned int)getpid());

    pthread_mutex_init(&cp->lock, NULL); // 初始化停车场的锁
    pthread_cond_init(&cp->space, NULL); // 初始化描述停车场是否有空位的条件变量
    pthread_cond_init(&cp->car, NULL); // 初始化描述停车场是否有车的条件变量
}
