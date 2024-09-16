#include "Function.hpp"

Function::Function(std::string name, instr::DataType returnType, std::vector<Param> params, std::vector<instr::Instruction> instructions) :
    name(name), returnType(returnType), params(params), instructions(instructions) {}; 

Param::Param(std::string ident, instr::DataType dataType) : ident(ident), dataType(dataType) {}; 
