#pragma once 
#include <iostream>

namespace instr {
/**
 * Support instructions of the form local.get $varName. 
 */
class LocalInstr {
    public: 
        LocalInstr() = default; 
        LocalInstr(std::string varName); 

        std::string varName; 
}; 
}
