#pragma once 

#include "Data.hpp"

class StoreInstr {
    public: 
        StoreInstr(int index, DataType dataType); 

        int getIndex(); 

        DataType getDataType(); 

    private: 
        int index; 
        DataType dataType; 
}; 
