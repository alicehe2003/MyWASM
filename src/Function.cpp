#include "Function.hpp"

Function::Function(std::string name, instr::DataType returnType, std::vector<std::tuple<std::string, instr::DataType>> params, std::vector<instr::Instruction> instructions) :
    name(name), returnType(returnType), params(params), instructions(instructions) {}; 
