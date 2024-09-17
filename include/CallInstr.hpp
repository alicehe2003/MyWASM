#pragma once 

#include "Data.hpp" 

namespace instr {
using ident = std::string; 

/**
 * @brief Error type(s) for CallInstr 
 */
enum class CallError {
    InvalidIdentifierError
}; 

/**
 * @brief Call instruction 
 * @author Alice He 
 */
class CallInstr {
    public: 
        /**
         * @param identifier is a string representation of an identifier. 
         * 
         * Note: Current identifiers supported include only log. 
         */
        CallInstr(ident identifier); 

        CallInstr() = default; 

        ident identifier; 
}; 

}
