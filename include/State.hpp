#pragma once 
#include <cstdint>
#include <stack>
#include "Instruction.hpp"

class State {
    public: 
        State();

        /** 
         * @return size of memory in bytes 
         */
        int size(); 

        void storeInMemory(int offset, Data value); 

        Data loadFromMemory(int offset, DataType dataType); 

        void pushToStack(Data value); 

        // get element at top of stack and remove the element 
        Data getFromStack(); 

        // return element at top of stack without removing the element 
        Data topOfStack(); 

    // private: TODO make private 
        // Statically allocated memory with 1MB of available space 
        uint8_t heap[1024 * 1024]; 
        std::stack<Data> stk; 
}; 

enum class StateError {
    MemoryOutOfBoundError
}; 
