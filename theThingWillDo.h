//
// Created by user on 6.12.2022.
//

#ifndef UNTITLED14_THETHINGWILLDO_H
#define UNTITLED14_THETHINGWILLDO_H
#include <string>

class theThingWillDo {
public:
    std::string typeOfTheAction = " ";
    float theTimeItWillGoBrew = 0, theTimeItWillBeInOrder= 0, theTimeItWillBeInBrew = 0, theTimeItWillFinishBrew = 0;
    float arrival = 0, order = 0, brew = 0, price = 0;
    bool orderTaken = false;
    bool orderInCashier = false;
    int orderId = -1;
    int cashierIdItGoes;
};


#endif //UNTITLED14_THETHINGWILLDO_H
