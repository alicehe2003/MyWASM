#include "Function.hpp"

Function::Function(std::string name, std::vector<Param> params, instr::DataType returnType, std::vector<instr::Instruction> instructions) :
    name(name), returnType(returnType), params(params), instructions(instructions) {}; 

// Param::Param(std::string ident, instr::DataType dataType) : ident(ident), dataType(dataType) {}; 
