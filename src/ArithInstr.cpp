#include "ArithInstr.hpp" 
#include "Instruction.hpp"

ArithInstr::ArithInstr(ArithOpType opType, DataType dataType) 
    : Instruction("ArithInstr"), opType(opType), dataType(dataType) {}; 

ArithOpType ArithInstr::getArithOpType() {
    return this->opType; 
}

DataType ArithInstr::getDatatType() {
    return this->dataType; 
} 
