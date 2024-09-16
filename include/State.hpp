#pragma once 
#include <cstdint>
#include <stack>
#include "Instruction.hpp"
#include <expected>

#include "Function.hpp"
#include <unordered_map>

enum class StateError {
    MemoryOutOfBoundError
}; 

class Context {
    public: 

        std::stack<instr::Data> stack; 
        Function* func; 
        int instrIndex; 
        std::unordered_map<std::string, instr::Data> params; 
}; 

class State {
    public: 
        State();

        /** 
         * @return size of memory in bytes 
         */
        int size(); 

        void storeInMemory(int offset, instr::Data value); 

        instr::Data loadFromMemory(int offset, instr::DataType dataType); 

    // private: TODO make private 
        // Statically allocated memory with 1MB of available space 
        uint8_t heap[1024 * 1024]; 
        std::stack<Context> contexts; 
}; 

