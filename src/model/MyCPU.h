#ifndef CPP_DRIVER_MYCPU_H
#define CPP_DRIVER_MYCPU_H


#include <memory>
#include <vector>
#include <set>
#include "Unit.h"

class MyCPU {
public:
    MyCPU(int unitsNum);

    int getUnitsNum() const;

    std::vector<std::unique_ptr<Unit>> units;

    std::set<int> work_units;

    void makeWork();
private:
    int units_num_;
};


#endif //CPP_DRIVER_MYCPU_H
