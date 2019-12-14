#include "Queue.hpp"
// ����һ����ͷ������ʽ���У��ڵ�λ�ڶ���β��
Queue::Queue() {
    this->front = new T;
    // ����ڴ�����ʧ�ܣ���Ӧ�ü������г�����
    if (!this->front) {
        exit(-1);
    }

    // ��ʼ���ڵ�
    this->front->next = nullptr;
    this->rear = this->front;
}
// ����һ������ʱ����Ҫ�ͷŽڵ���������ڴ�
Queue::~Queue() {
    // ��յ�ǰ�����е�Ԫ��
    this->clearQueue();

    // ��ɾ��ͷ���
    delete this->front;

    // ע�������ٺ�ͷ����ͷβָ��Ӧ���ÿ�
    this->front = nullptr;
    this->rear  = nullptr;
}

// ���ʱ�����ݽڵ�ָ�룬�ⲿ���ݲ�Ӧ���ɴ�����й������Խ����ݿ���һ��
// ������ͷָ��
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
// ����ʱ���Ӷ�ͷԪ�س���
T* Queue::dequeue() {
    // ������пգ��򷵻ؿ�ָ��
    if (!this->front->next) {
        return nullptr;
    }

    T *temp_node;
    temp_node = this->front->next;
    this->front->next = temp_node->next;

    // ���������ֻ��һ���ڵ㣬��ô�ǵý���β�ڵ�ָ����Ϊͷ���
    if (this->rear == temp_node) {
        this->rear = this->front;
    }
    return temp_node;
}

// �¼�ʱ��˳����룬�¼�������ķ����¼���Ӧ�ð��¼�˳����в���
T* Queue::orderEnqueue(Event &event) {
    Event* temp = new Event;
    if (!temp) {
        exit(-1);
    }
    *temp = event;

    // �������б���û���¼�, ��� temp �¼�����
    if (!this->front->next) {
        this->enqueue(*temp);
        return this->front;
    }

    // ��ʱ��˳�����
    Event *temp_event_list = this->front;

    // �������һ���¼�������һ���¼��ķ���ʱ��С��Ҫ�����ʱ���ʱ�䣬�������ָ�����
    while (temp_event_list->next && temp_event_list->next->occur_time < event.occur_time) {
        temp_event_list = temp_event_list->next;
    }

    // ���¼����뵽������
    temp->next = temp_event_list->next;
    temp_event_list->next = temp;

    // ���ض���ͷָ��
    return this->front;
}

//���еĳ��ȼ���
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
