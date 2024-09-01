#pragma once 

#include "Data.hpp" 

namespace instr {
using ident = std::string; 

enum class CallError {
    InvalidIdentifierError
}; 

class CallInstr {
    public: 
        /**
         * @param identifier is a string representation of an identifier. 
         * 
         * Note: Current identifiers supported include only log. 
         */
        CallInstr(ident identifier); 

        CallInstr() = default; 

    // private: 
        ident identifier; 
}; 

}
