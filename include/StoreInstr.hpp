#pragma once 

#include "Instruction.hpp"

class StoreInstr : public Instruction {
    public: 
        StoreInstr(int index); 

        int getIndex(); 

    private: 
        int index; 
}; 
