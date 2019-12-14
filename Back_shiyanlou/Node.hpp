//
//  Node.h
//  QueueSystem
//

#ifndef Node_h
#define Node_h

#include "Random.hpp"

#define RANDOM_PARAMETER 100

struct Node {
    int arrive_time;
    int duration;
    struct Node *next;

    // 默认到达事件为0，需要服务时间是随机的，服从均匀分布->指数分别
//    Node(int arrive_time = 0, int duration = Random::uniform(RANDOM_PARAMETER)):
    Node(int arrive_time = 0, int duration = Random::getRandom(EXPONENTAIL, 0.1)):
        arrive_time(arrive_time),
        duration(duration),
        next(nullptr) {}
};

typedef struct Node Node;
typedef struct Node Customer;

#endif /* Node_h */
