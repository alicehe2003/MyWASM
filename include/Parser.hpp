#pragma once

#include "Instruction.hpp"
#include <expected>
#include <variant> 

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
       std::expected<Instruction, std::variant<DataError, CallError>> parse(const std::string& str); 
}; 

