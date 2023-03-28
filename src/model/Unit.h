#ifndef CPP_DRIVER_UNIT_H
#define CPP_DRIVER_UNIT_H


#include <memory>
#include "ram/LRam.h"
#include "ram/PRam.h"

class Unit {
public:
    Unit();

    std::unique_ptr<LRam> lram;
    std::unique_ptr<PRam> pram;

    void makeWork();
};


#endif //CPP_DRIVER_UNIT_H
