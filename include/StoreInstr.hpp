#pragma once 

#include "Instruction.hpp"

class StoreInstr : public Instruction {
    public: 
        StoreInstr(int index, DataType dataType); 

        int getIndex(); 

        DataType getDataType(); 

    private: 
        int index; 
        DataType dataType; 
}; 
