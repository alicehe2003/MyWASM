#include "StoreInstr.hpp"

StoreInstr::StoreInstr(int index, DataType dataType) {
    this->index = index; 
    this->dataType = dataType; 
}

int StoreInstr::getIndex() {
    return this->index; 
}

DataType StoreInstr::getDataType() {
    return this->dataType; 
}
