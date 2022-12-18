//
// Created by user on 6.12.2022.
//

#ifndef UNTITLED14_QUEUE_H
#define UNTITLED14_QUEUE_H


#include "Node.h"

class Queue {
public:
    Node* root = NULL;
    void enque(int id);
    Node * head();
    Node * takeOrder(float order, int orderId, float time);
    bool sendTakenOrderToBrew(float brew, Node * headOfBarista, int orderId, float time);
    bool queueIsFull();
    float findMinTime();
    Node * findMinBarista();

};


#endif //UNTITLED14_QUEUE_H
