#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include "CarPack.hpp"
#include "function.hpp"

using namespace std;


int main(int argc, char **argv) {

    if (argc != 2) {
        cout<<"argc error"<<endl;
        exit(1);
    }

    CarPack ourpark;

    initialise(&ourpark, atoi(argv[1])); // 初始化停车场数据结构

    pthread_t car_in, car_out, m;  // 定义线程变量
    pthread_t car_in2, car_out2;

    pthread_create(&car_in, NULL, car_in_handler, (void *)&ourpark);  // 创建往停车场停车线程（生产者1）
    pthread_create(&car_out, NULL, car_out_handler, (void *)&ourpark); // 创建从停车场取车线程（消费者1）
    pthread_create(&car_in2, NULL, car_in_handler, (void *)&ourpark); // 创建往停车场停车线程（生产者2）
    pthread_create(&car_out2, NULL, car_out_handler, (void *)&ourpark); // 创建从停车场取车线程（消费者2）
    pthread_create(&m, NULL, monitor, (void *)&ourpark);  // 创建用于监控停车场状况的线程

    // pthread_join 的第二个参数设置为 NULL，表示并不关心线程的返回状态，仅仅等待指定线程（第一个参数）的终止
    pthread_join(car_in, NULL);
    pthread_join(car_out, NULL);
    pthread_join(car_in2, NULL);
    pthread_join(car_out2, NULL);
    pthread_join(m, NULL);

    exit(0);
}