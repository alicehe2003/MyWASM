#pragma once 
#include <cstdint>
#include <stack>
#include "Instruction.hpp"
#include <expected>

enum class StateError {
    MemoryOutOfBoundError
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

        void pushToStack(instr::Data value); 

        // get element at top of stack and remove the element 
        instr::Data getFromStack(); 

        // return element at top of stack without removing the element 
        instr::Data topOfStack(); 

    // private: TODO make private 
        // Statically allocated memory with 1MB of available space 
        uint8_t heap[1024 * 1024]; 
        std::stack<instr::Data> stk; 
}; 
