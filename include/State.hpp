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

        void storeInMemory(int offset, int index, Data value); 

        Data loadFromMemory(int offset, int index, DataType dataType); 

        void pushToStack(Data value); 

        // get element at top of stack and remove the element 
        Data getFromStack(); 

    private: 
        // Statically allocated memory with 1MB of available space 
        uint8_t heap[1024 * 1024]; 
        std::stack<Data> stk; 
}; 
