#pragma once 
#include <cstdint>
#include <stack>
#include "Instruction.hpp"
#include <expected>

#include "Function.hpp"
#include <unordered_map>

/**
 * @brief Represents the error(s) that can be thrown by state. 
 */
enum class StateError {
    MemoryOutOfBoundError
}; 

/**
 * @brief A context tracks the current stack and parameters passed. 
 * Used by functions to track what is in scope, and which parameters have been passed to it (accessibile). 
 */
class Context {
    public: 

        std::stack<instr::Data> stack; 
        std::unordered_map<std::string, instr::Data> params; 
}; 

/**
 * @brief Represents the current state of the program. Contains the heap (memory space allocated) and a stack of
 * contexts to track variables in scope. 
 */
class State {
    public: 
        State();

        /** 
         * @return size of memory in bytes 
         */
        int size(); 

        void storeInMemory(int offset, instr::Data value); 

        instr::Data loadFromMemory(int offset, instr::DataType dataType); 

        // Statically allocated memory with 1MB of available space 
        uint8_t heap[1024 * 1024]; 
        std::stack<Context> contexts; 
}; 

