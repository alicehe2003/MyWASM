#pragma once 

#include "Instruction.hpp"

class LoadInstr : public Instruction {
    public: 
        LoadInstr(int index, DataType dataType); 

        int getIndex(); 

        DataType getDataType(); 
        
    private: 
        int index; 
        DataType dataType; 
}; 
