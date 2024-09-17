#pragma once

#include "Data.hpp"

namespace instr {
/**
 * @brief Const instruction. 
 * @author Alice He 
 */
class ConstInstr {
    public: 
        ConstInstr(Data data); 

        ConstInstr() : data(Data(instr::DataType::i32)) {}; 

        DataType getDataType(); 

        Data getData(); 

        Data data; 
}; 
}
