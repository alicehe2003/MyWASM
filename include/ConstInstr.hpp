#pragma once

#include "Data.hpp"

class ConstInstr {
    public: 
        ConstInstr(Data data); 

        DataType getDataType(); 

        Data getData(); 

    private: 
        Data data; 
}; 
