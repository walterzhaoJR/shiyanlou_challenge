#include "Queue.hpp"
// 构造一个带头结点的链式队列，节点位于队列尾部
Queue::Queue() {
    this->front = new T;
    // 如果内存申请失败，则不应该继续运行程序了
    if (!this->front) {
        exit(-1);
    }

    // 初始化节点
    this->front->next = nullptr;
    this->rear = this->front;
}
// 销毁一个队列时候需要释放节点中申请的内存
Queue::~Queue() {
    // 清空当前队列中的元素
    this->clearQueue();

    // 再删除头结点
    delete this->front;

    // 注意在销毁后头结点后，头尾指针应该置空
    this->front = nullptr;
    this->rear  = nullptr;
}

// 入队时，传递节点指针，外部数据不应该由此类进行管理，所以将数据拷贝一份
// 并返回头指针
T* Queue::enqueue(T &node) {
    T *new_node = new T;
    if (!new_node) {
        exit(-1);
    }
    *new_node = node;
    this->rear->next = new_node;
    this->rear = new_node;
    return this->front;
}
// 出队时，从队头元素出队
T* Queue::dequeue() {
    // 如果队列空，则返回空指针
    if (!this->front->next) {
        return nullptr;
    }

    T *temp_node;
    temp_node = this->front->next;
    this->front->next = temp_node->next;

    // 如果队列中只有一个节点，那么记得将队尾节点指针置为头结点
    if (this->rear == temp_node) {
        this->rear = this->front;
    }
    return temp_node;
}

// 事件时的顺序插入，事件有自身的发生事件，应该按事件顺序进行插入
T* Queue::orderEnqueue(Event &event) {
    Event* temp = new Event;
    if (!temp) {
        exit(-1);
    }
    *temp = event;

    // 如果这个列表里没有事件, 则把 temp 事件插入
    if (!this->front->next) {
        this->enqueue(*temp);
        return this->front;
    }

    // 按时间顺序插入
    Event *temp_event_list = this->front;

    // 如果有下一个事件，且下一个事件的发生时间小于要插入的时间的时间，则继续将指针后移
    while (temp_event_list->next && temp_event_list->next->occur_time < event.occur_time) {
        temp_event_list = temp_event_list->next;
    }

    // 将事件插入到队列中
    temp->next = temp_event_list->next;
    temp_event_list->next = temp;

    // 返回队列头指针
    return this->front;
}

//队列的长度计算
int Queue::length() {
    T *temp_node;
    temp_node = this->front->next;
    int length = 0;
    while (temp_node) {
        temp_node = temp_node->next;
        ++length;
    }
    return length;
}

void Queue::clearQueue() {
    T *temp_node;

    while (this->front->next) {
        temp_node = this->front->next;
        this->front->next = temp_node->next;
        delete temp_node;
    }

    this->front->next = nullptr;
    this->rear = this->front;
}
