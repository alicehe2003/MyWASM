#pragma once 

#include "Data.hpp"

class LoadInstr {
    public: 
        LoadInstr(int index, DataType dataType); 

        int getIndex(); 

        DataType getDataType(); 
        
    private: 
        int index; 
        DataType dataType; 
}; 
