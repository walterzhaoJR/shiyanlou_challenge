//
// Created by walter on 2017/2/12.
//

#ifndef CARPACK_H
#define CARPACK_H

#include <pthread.h>

class CarPack
{
public:
    int* carpark;//用一个数组模拟停车场位置
    int capacity;//停车场容量
    int occupied;//停车场现有车辆数目
    int nextin;//下一个进来车的位置,用carpack下标来表示
    int nextout;//下一个取走车位置,同上
    int cars_in;//记录进入车的总数
    int cars_out;//记录离开车的总数
    pthread_mutex_t lock;//互斥量,保护该结构中的数据被线程互斥的地方使用
    pthread_cond_t space;//条件变量,描述是否还有空位
    pthread_cond_t car;//条件变量,描述停车场是否有车
    pthread_barrier_t bar;//线程屏障
};


#endif //CARPACK_H
