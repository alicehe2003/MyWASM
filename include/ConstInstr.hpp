#pragma once

#include "Data.hpp"

namespace instr {
class ConstInstr {
    public: 
        ConstInstr(Data data); 

        ConstInstr() : data(Data(instr::DataType::i32)) {}; 

        DataType getDataType(); 

        Data getData(); 

    // private: 
        Data data; 
}; 
}
