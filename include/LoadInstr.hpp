#pragma once 

#include "Instruction.hpp"

class LoadInstr : public Instruction {
    public: 
        LoadInstr(int index); 

        int getIndex(); 

    private: 
        int index; 
}; 
