#pragma once 

#include "Data.hpp"

namespace instr {
class StoreInstr {
    public: 
        StoreInstr(int index, DataType dataType); 

        StoreInstr(DataType dataType) : dataType(dataType) {}; 
        StoreInstr() = default; 

        int getIndex(); 

        DataType getDataType(); 

    private: 
        int index; 
        DataType dataType; 
}; 

}
