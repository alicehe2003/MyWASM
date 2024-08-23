#pragma once

#include "Instruction.hpp"
#include <expected>
#include <variant> 

#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix/operator.hpp>

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
      std::expected<Instruction, std::variant<DataError, CallError, InstructionError>> parse(const std::string& str); 
}; 

namespace qi = boost::spirit::qi;

struct DataType_ : qi::symbols<char, DataType> {
  DataType_() {
    add
        ("i32", DataType::i32) 
        ("u32", DataType::u32); 
  }
}; 

struct ArithOpType_ : qi::symbols<char, ArithOpType> {
  ArithOpType_() {
    add 
        ("add", ArithOpType::Add)
        ("sub", ArithOpType::Sub)
        ("mul", ArithOpType::Mult)
        ("div_s", ArithOpType::Div_s); 
  }
}; 


