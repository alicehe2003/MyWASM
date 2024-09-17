#pragma once 

#include "Data.hpp"

namespace instr {
/**
 * @brief Load intruction. Loads data to memory. 
 */
class LoadInstr {
    public: 
        LoadInstr(int index, DataType dataType); 

        LoadInstr(DataType dataType) : dataType(dataType) {}; 
        LoadInstr() = default; 

        int getIndex(); 

        DataType getDataType(); 
        
    private: 
        int index; 
        DataType dataType; 
}; 

}
