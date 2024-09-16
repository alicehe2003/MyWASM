#pragma once 

#include "Data.hpp"
#include "Instruction.hpp"
#include <optional>

struct Param {
    Param(std::string ident, instr::DataType dataType); 

    std::string ident; 
    instr::DataType dataType; 
}; 

class Function {
    public: 
    /**
     * @param name is name of function 
     * @param returnType is return type of function 
     * @param params is vector of tuples, where each tuple is a (name, type)
     *      name is the name of the parameter 
     *      type is the data type of the parameter 
     * @param instructions is the list of instructions in the function body 
     */
    Function(std::string name, instr::DataType returnType, std::vector<Param> params, std::vector<instr::Instruction> instructions);

    std::string name; 
    std::optional<instr::DataType> returnType; 
    std::vector<Param> params; 
    std::vector<instr::Instruction> instructions; 
}; 
