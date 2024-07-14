#include "StoreInstr.hpp"

StoreInstr::StoreInstr(int index, DataType dataType) 
    : Instruction("StoreInstr"), index(index), dataType(dataType) {}; 

int StoreInstr::getIndex() {
    return this->index; 
}

DataType StoreInstr::getDataType() {
    return this->dataType; 
}
