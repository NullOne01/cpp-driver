#include "MyCPU.h"

int MyCPU::getUnitsNum() const {
    return units_num_;
}

MyCPU::MyCPU(int unitsNum) : units_num_(unitsNum) {
}
