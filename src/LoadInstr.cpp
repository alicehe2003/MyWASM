#include "LoadInstr.hpp"

LoadInstr::LoadInstr(int index, DataType dataType) 
    : Instruction("LoadInstr"), index(index), dataType(dataType) {}; 

int LoadInstr::getIndex() {
    return this->index; 
}

DataType LoadInstr::getDataType() {
    return this->dataType; 
}
