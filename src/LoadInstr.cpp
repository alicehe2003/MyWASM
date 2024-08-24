#include "LoadInstr.hpp"

using namespace instr;

LoadInstr::LoadInstr(int index, DataType dataType) 
    : index(index), dataType(dataType) {}; 

int LoadInstr::getIndex() {
    return this->index; 
}

DataType LoadInstr::getDataType() {
    return this->dataType; 
}
