//
// Created by user on 6.12.2022.
//

#include "Queue.h"
using namespace std;

void Queue::enque(int id) {
    if (root==nullptr){
        Node *newNode = new Node(id);
        root = newNode;
    }
    else{
        Node *newNode = new Node(id);
        Node* temp = root;
        while (temp->next!=nullptr){
            temp = temp->next;
        }
        temp->next = newNode;
    }
}


Node * Queue::head() {
    return root;
}


Node * Queue::takeOrder(float order, int orderId, float time) {
    Node* temp = root;
    Node * temp3;
    bool orderTaken = false;
    while (temp!=nullptr){
        if (temp->busy == false && orderTaken == false){
            temp->busyForThisLong = order+ time;
            temp->busy = true;
            orderTaken =true;
            temp->takenOrdersId = orderId;
            temp->workingTime += order;
            temp3 = temp;
        }
        temp = temp->next;
    }
    return temp3;
}

bool Queue::sendTakenOrderToBrew(float brew, Node * headOfBarista, int orderId, float time) {
    bool orderTaken = false;
    while (headOfBarista != nullptr && orderTaken == false){
        if (headOfBarista->busy == false){
            headOfBarista->busyForThisLong = time + brew;
            headOfBarista->busy = true;
            headOfBarista->takenOrdersId = orderId;
            orderTaken = true;
            headOfBarista->workingTime += brew;
        }
        headOfBarista = headOfBarista->next;
    }
    return orderTaken;
}


bool Queue::queueIsFull() {
    Node* temp = root;
    bool full = true;
    while (temp!= nullptr){
        if (temp->busy== false){
            full = false;
        }
        temp = temp->next;
    }
    return full;
}

float Queue::findMinTime() {
    Node* temp = root;
    float min = temp->busyForThisLong;
    temp = temp->next;
    while (temp!= nullptr){
        if (temp->busyForThisLong < min ){
            min = temp->busyForThisLong;
        }
        temp = temp->next;
    }
    return min;
}

Node * Queue::findMinBarista() {
    Node* temp = root;
    Node* temp2 = root;
    float min = temp->busyForThisLong;
    temp = temp->next;
    while (temp!= nullptr){
        if (temp->busyForThisLong < min ){
            min = temp->busyForThisLong;
            temp2 = temp;
        }
        temp = temp->next;
    }
    return temp2;
}