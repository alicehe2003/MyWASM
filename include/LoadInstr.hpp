#pragma once 

#include "Data.hpp"

namespace instr {
class LoadInstr {
    public: 
        LoadInstr(int index, DataType dataType); 

        int getIndex(); 

        DataType getDataType(); 
        
    private: 
        int index; 
        DataType dataType; 
}; 

}
