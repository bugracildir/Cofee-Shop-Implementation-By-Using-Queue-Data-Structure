//
// Created by user on 6.12.2022.
//

#ifndef UNTITLED14_NODE_H
#define UNTITLED14_NODE_H


#include <string>


using namespace std;
class Node {
public:

    Node* next = NULL;
    int cashierId;
    int takenOrdersId;
    float busyForThisLong;
    bool busy = false;
    float workingTime;


    Node(int id){
        this->cashierId = id;
    }

};


#endif //UNTITLED14_NODE_H
