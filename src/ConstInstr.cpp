#include "ConstInstr.hpp"
using namespace instr;

ConstInstr::ConstInstr(Data data): data(data) {};

Data ConstInstr::getData() {
    return this->data; 
}

DataType ConstInstr::getDataType() {
    return this->data.getDataType(); 
} 

