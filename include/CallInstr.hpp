#pragma once 

#include "Data.hpp" 

using ident = std::string; 

class CallInstr {
    public: 
        /**
         * @param identifier is a string representation of an identifier. 
         * 
         * Note: Current identifiers supported include only log. 
         */
        CallInstr(ident identifier); 

    private: 
        ident identifier; 
}; 
