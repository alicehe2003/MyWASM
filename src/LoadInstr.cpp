#include "LoadInstr.hpp"

LoadInstr::LoadInstr(int index, DataType dataType) {
    this->index = index; 
    this->dataType = dataType; 
}

int LoadInstr::getIndex() {
    return this->index; 
}

DataType LoadInstr::getDataType() {
    return this->dataType; 
}
