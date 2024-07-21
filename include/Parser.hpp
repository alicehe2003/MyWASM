#pragma once

#include "Instruction.hpp"
#include <expected>

class Parser {
    public: 
        Parser(); 
        
        /**
         * Parses instruction input and returns Instruction object.
         * 
         * @param str is the given instruction in string format. 
         * 
         * @return The correct Instruction object representation of str. 
         */
       std::expected<Instruction, DataError> parse(const std::string& str); 
}; 

