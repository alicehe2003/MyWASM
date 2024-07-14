#include "ConstInstr.hpp"

ConstInstr::ConstInstr(Data data): Instruction("ConstInstr"), data(data) {};

Data ConstInstr::getData() {
    return this->data; 
}

DataType ConstInstr::getDataType() {
    return this->data.getDataType(); 
} 

