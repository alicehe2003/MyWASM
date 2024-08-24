#pragma once

#include "Data.hpp"

namespace instr {
class ConstInstr {
    public: 
        ConstInstr(Data data); 

        DataType getDataType(); 

        Data getData(); 

    private: 
        Data data; 
}; 
}
