#pragma once 

#include "Data.hpp"

namespace instr {
/**
 * @brief Store instruction. Used to store value in memory. 
 */
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
