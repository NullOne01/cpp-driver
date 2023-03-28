#include "MyCPU.h"

int MyCPU::getUnitsNum() const {
    return units_num_;
}

MyCPU::MyCPU(int unitsNum) : units_num_(unitsNum) {
    for (int i = 0; i < unitsNum; ++i) {
        units.push_back(std::make_unique<Unit>());
    }
}

void MyCPU::makeWork() {
    for(auto unit_index : work_units) {
        if (unit_index >= 0 && unit_index < units_num_) {
            units[unit_index]->makeWork();
        }
    }
}
