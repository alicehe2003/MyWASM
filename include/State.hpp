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

        void store(int offset, int index, Data value); 

        Data load(int offset, int index, DataType dataType); 

    private: 
        // Statically allocated memory with 1MB of available space 
        uint8_t heap[1024 * 1024]; 
        std::stack<uint8_t> stk; 
}; 
