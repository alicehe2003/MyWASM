#pragma once

#include "Instruction.hpp"

class ConstInstr : public Instruction {
    public: 
        ConstInstr(Data data); 

        DataType getDataType(); 

        Data getData(); 

    private: 
        Data data; 
}; 
