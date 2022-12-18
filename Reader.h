//
// Created by user on 6.12.2022.
//

#ifndef UNTITLED14_READER_H
#define UNTITLED14_READER_H

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Queue.h"
#include "Node.h"
#include "theThingWillDo.h"
using namespace std;
class Reader {
public:
    static void Read(string input, string output);
    static float Round(float var);
    static int TakeOrder(theThingWillDo listOfActions[], int orderNumber, int numberOfCashiers, Queue *cashierQueue);
    static int SendOrderToBrew(Queue * baristaQueue, int orderNumber, theThingWillDo listOfAction[], int maxBrewQueue);
};

#endif //UNTITLED14_READER_H
