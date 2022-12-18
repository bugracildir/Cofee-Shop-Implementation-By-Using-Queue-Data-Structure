//
// Created by user on 6.12.2022.
//

#include <vector>
#include "Reader.h"
using namespace std;

float Reader::Round(float var) {
    float value = (int)(var*100 + .5);
    return (float)value/100;
}

void Reader::Read(string input, string output){
    Queue *cashierQueue = new Queue();
    Queue *baristaQueue = new Queue();
    Queue *cashierQueue2 = new Queue();

    ofstream writeToFile(output);
    ifstream readFile(input);
    string line;
    getline (readFile, line);
    stringstream sstream;
    sstream << line;
    int numberOfCashiers;
    sstream >> numberOfCashiers;

    Queue *baristaQueueList[numberOfCashiers/3];
    for (int i = 0; i < numberOfCashiers/3; ++i) {
        baristaQueueList[i] = new Queue();
    }

    for (int i = 0; i < numberOfCashiers; ++i) {
        cashierQueue->enque(i+1);
        cashierQueue2->enque(i+1);
    }
    for (int i = 0; i < (numberOfCashiers/3); ++i) {
        baristaQueue->enque(i+1);
        baristaQueueList[i]->enque(1);
    }
    getline (readFile, line);
    int orderNumber;
    stringstream sstream3;
    sstream3 << line;
    sstream3 >> orderNumber;

    theThingWillDo listOfActions[orderNumber];

    string line1;
    int orderId = 1;
    while (getline (readFile, line1)){
        stringstream sstream2;
        sstream2 << line1;
        float arrival, order, brew, price;
        sstream2 >> arrival;
        sstream2 >> order;
        sstream2 >> brew;
        sstream2 >> price;
        int placeInStruct = orderId-1;
        listOfActions[placeInStruct].typeOfTheAction = "takeorder";
        listOfActions[placeInStruct].arrival = arrival;
        listOfActions[placeInStruct].brew = brew;
        listOfActions[placeInStruct].order = order;
        listOfActions[placeInStruct].price = price;
        listOfActions[placeInStruct].orderId = orderId;
        orderId += 1;
    }
    theThingWillDo listOfActions2[orderNumber];
    for (int i = 0; i < orderNumber; ++i) {
        listOfActions2[i] = listOfActions[i];
    }
    int maxBrewQueue = 0;
    int maxCashierQueue = Reader::TakeOrder(listOfActions, orderNumber, numberOfCashiers, cashierQueue);
    maxBrewQueue = Reader::SendOrderToBrew(baristaQueue, orderNumber,listOfActions, maxBrewQueue);


    for (int i = 0; i < orderNumber; ++i) {
        listOfActions[i].theTimeItWillFinishBrew = listOfActions[i].theTimeItWillBeInBrew + listOfActions[i].brew;
    }
    vector < double > maxRunning ;
    vector < double > maxRunningTime ;
    float totalRunningTime = 0.0;
    for (int i = 0; i < orderNumber; ++i) {
        maxRunning.push_back(listOfActions[i].theTimeItWillBeInOrder);
        maxRunningTime.push_back(listOfActions[i].theTimeItWillFinishBrew);
        if (listOfActions[i].theTimeItWillFinishBrew > totalRunningTime){
            totalRunningTime = listOfActions[i].theTimeItWillFinishBrew;
        }
    }
    writeToFile<<totalRunningTime<<endl;
    writeToFile<<maxCashierQueue<<endl;
    writeToFile<<maxBrewQueue<<endl;
    Node * temp = cashierQueue->head();
    for (int i = 0; i < numberOfCashiers; ++i) {
        writeToFile<<Round(temp->workingTime/totalRunningTime)<<endl;
        temp = temp->next;
    }
    temp = baristaQueue->head();
    for (int i = 0; i < numberOfCashiers/3; ++i) {
        writeToFile<<Round(temp->workingTime/totalRunningTime)<<endl;
        temp = temp->next;
    }
    for (int i = 0; i < orderNumber; ++i) {
        writeToFile<<listOfActions[i].theTimeItWillFinishBrew- listOfActions[i].arrival<<endl;
    }
    writeToFile<<endl;
    maxCashierQueue = 0;
    maxCashierQueue = Reader::TakeOrder(listOfActions2, orderNumber, numberOfCashiers, cashierQueue2);
    vector<int> maxBrewQueues;
    int a = 0;
    for (int i = 0; i < numberOfCashiers; i+=3) {
        int maxBrewQueue2 = 0;
        vector<int> smallAction;
        for (int j = 0; j < orderNumber; ++j) {
            if (listOfActions2[j].cashierIdItGoes == i + 1 || listOfActions2[j].cashierIdItGoes == i + 2 ||
                listOfActions2[j].cashierIdItGoes == i + 3) {
                smallAction.push_back(j);
            }
        }
        theThingWillDo smallActionList[smallAction.size()];
        for (int j = 0; j < smallAction.size(); ++j) {
            smallActionList[j] = listOfActions2[smallAction.at(j)];
        }
        maxBrewQueue2 = Reader::SendOrderToBrew(baristaQueueList[a], smallAction.size(), smallActionList, maxBrewQueue2);
        maxBrewQueues.push_back(maxBrewQueue2);
        for (int j = 0; j < smallAction.size(); ++j) {
            for (int k = 0; k < orderNumber; ++k) {
                if (listOfActions2[k].orderId == smallActionList[j].orderId) {
                    listOfActions2[k] = smallActionList[j];
                }
            }
        }
        a += 1;
    }
    for (int i = 0; i < orderNumber; ++i) {
        listOfActions2[i].theTimeItWillFinishBrew = listOfActions2[i].theTimeItWillBeInBrew + listOfActions2[i].brew;
    }
    vector < double > maxRunning2 ;
    vector < double > maxRunningTime2 ;
    totalRunningTime = 0.0;
    for (int i = 0; i < orderNumber; ++i) {
        maxRunning2.push_back(listOfActions2[i].theTimeItWillBeInOrder);
        maxRunningTime2.push_back(listOfActions2[i].theTimeItWillFinishBrew);
        if (listOfActions2[i].theTimeItWillFinishBrew > totalRunningTime){
            totalRunningTime = listOfActions2[i].theTimeItWillFinishBrew;
        }
    }
    writeToFile<<totalRunningTime<<endl;
    writeToFile<<maxCashierQueue<<endl;
    for (int a : maxBrewQueues){
        writeToFile<<a<<endl;
    }
    Node * temp4 = cashierQueue2->head();
    for (int i = 0; i < numberOfCashiers; ++i) {
        writeToFile<<Round(temp4->workingTime/totalRunningTime)<<endl;
        temp4 = temp4->next;
    }
    for (int i = 0; i < numberOfCashiers/3; ++i) {
        Node * temp5 = baristaQueueList[i]->head();
        writeToFile<<Round(temp5->workingTime/totalRunningTime)<<endl;
    }
    for (int i = 0; i < orderNumber; ++i) {
        writeToFile<<listOfActions2[i].theTimeItWillFinishBrew- listOfActions2[i].arrival<<endl;
    }
    readFile.close();
}


int Reader::TakeOrder(theThingWillDo listOfActions[], int orderNumber, int numberOfCashiers, Queue *cashierQueue) {
    float currentTime = 0;
    int maxCashierQueue = 0;
    for (int i = 0; i < orderNumber; ++i) {
        float min = 0;
        currentTime = listOfActions[i].arrival;
        if (cashierQueue->queueIsFull()){
            Node* temp = cashierQueue->head();
            min = temp->busyForThisLong;
            temp = temp->next;
            for (int j = 0; j < numberOfCashiers-1; ++j) {
                if (temp->busyForThisLong<min){
                    min = temp->busyForThisLong;
                }
                temp = temp->next;
            }

            vector<int> ordersCouldntTaken;
            float minCashierBusy = cashierQueue->findMinTime();
            for (int k = 0; k < orderNumber; ++k) {
                if (listOfActions[k].orderInCashier == false && listOfActions[k].arrival < minCashierBusy){
                    ordersCouldntTaken.push_back(k);
                }
            }
            if (ordersCouldntTaken.size()>maxCashierQueue){
                maxCashierQueue = ordersCouldntTaken.size();
            }

            temp = cashierQueue->head();
            bool ordertkn = false;

            for (int j = 0; j < numberOfCashiers; ++j) {
                if (temp->busyForThisLong<=currentTime && ordertkn == false){
                    listOfActions[i].theTimeItWillBeInOrder = listOfActions[i].arrival;
                    listOfActions[i].theTimeItWillGoBrew = listOfActions[i].arrival + listOfActions[i].order;
                    temp->busyForThisLong = listOfActions[i].arrival + listOfActions[i].order;
                    temp->workingTime += listOfActions[i].order;
                    ordertkn = true;
                    listOfActions[i].cashierIdItGoes = temp->cashierId;
                    listOfActions[i].orderInCashier = true;
                }
                temp = temp->next;
            }
            temp = cashierQueue->head();
            for (int j = 0; j < numberOfCashiers; ++j) {
                if (temp->busyForThisLong == min && ordertkn == false) {
                    if (temp->busyForThisLong > currentTime) {
                        listOfActions[i].theTimeItWillBeInOrder = temp->busyForThisLong;
                        listOfActions[i].theTimeItWillGoBrew = temp->busyForThisLong + listOfActions[i].order;
                        temp->busyForThisLong += listOfActions[i].order;
                        temp->workingTime += listOfActions[i].order;
                        listOfActions[i].cashierIdItGoes = temp->cashierId;
                        listOfActions[i].orderInCashier = true;
                    }
                }
                temp = temp->next;
            }
        }
        else{
            Node * temp3 = cashierQueue->takeOrder(listOfActions[i].order , listOfActions[i].orderId, currentTime);
            listOfActions[i].cashierIdItGoes = temp3->cashierId;
            listOfActions[i].theTimeItWillBeInOrder = listOfActions[i].arrival;
            listOfActions[i].theTimeItWillGoBrew = listOfActions[i].arrival + listOfActions[i].order;
            listOfActions[i].orderInCashier = true;
        }
    }
    return maxCashierQueue;
}

int Reader::SendOrderToBrew(Queue * baristaQueue, int orderNumber, theThingWillDo listOfAction[], int maxBrewQueue) {
    double time = 0.0;
    for (int i = 0; i < orderNumber; ++i) {
        double min = 999999.0;
        for (int k = 0; k < orderNumber; ++k) {
            if (listOfAction[k].theTimeItWillGoBrew<min && listOfAction[k].orderTaken == false){
                min = listOfAction[k].theTimeItWillGoBrew;
            }
        }
        Node* temp = baristaQueue->head();
        for (int j = 0; j < orderNumber; ++j) {
            if (listOfAction[j].theTimeItWillGoBrew == min){
                if (!baristaQueue->queueIsFull()){
                    time = listOfAction[j].theTimeItWillGoBrew;
                    baristaQueue->sendTakenOrderToBrew(listOfAction[j].brew, temp, listOfAction[j].orderId,time);
                    listOfAction[j].theTimeItWillBeInBrew = listOfAction[j].theTimeItWillGoBrew;
                    listOfAction[j].orderTaken = true;
                }

                else{
                    vector<int> ordersCouldntTaken;
                    float minBaristaBusy = baristaQueue->findMinTime();
                    for (int k = 0; k < orderNumber; ++k) {
                        if (listOfAction[k].orderTaken == false && listOfAction[k].theTimeItWillGoBrew < minBaristaBusy){
                            ordersCouldntTaken.push_back(k);
                        }
                    }
                    int cheapestOrderId = 0;
                    float maxPrice = 0.0;
                    for (int k = 0; k < ordersCouldntTaken.size(); ++k) {
                        if (listOfAction[ordersCouldntTaken.at(k)].price > maxPrice){
                            maxPrice = listOfAction[ordersCouldntTaken.at(k)].price;
                            cheapestOrderId = ordersCouldntTaken.at(k) + 1;
                        }
                    }
                    listOfAction[cheapestOrderId-1].theTimeItWillBeInBrew = minBaristaBusy;
                    Node * temp = baristaQueue->findMinBarista();
                    temp->busyForThisLong += listOfAction[cheapestOrderId-1].brew;
                    temp->workingTime+=listOfAction[cheapestOrderId-1].brew;
                    listOfAction[cheapestOrderId-1].orderTaken = true;
                    if (ordersCouldntTaken.size()>maxBrewQueue){
                        maxBrewQueue = ordersCouldntTaken.size();
                    }
                }
            }
        }
    }
    return maxBrewQueue;
}