#include "StoreInstr.hpp"

StoreInstr::StoreInstr(int index) {
    this->index = index; 
}

int StoreInstr::getIndex() {
    return this->index; 
}
