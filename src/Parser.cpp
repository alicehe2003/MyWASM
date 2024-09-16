#include "Parser.hpp"
#include <iostream>
#include "Instruction.hpp"
#include "ConstInstr.hpp"
#include "ArithInstr.hpp"
#include "LoadInstr.hpp"
#include "SizeInstr.hpp"
#include "StoreInstr.hpp"

#include <expected>
#include <variant> 

Parser::Parser() {

}

std::expected<instr::Instruction, std::variant<instr::DataError, instr::CallError, instr::InstructionError, ParserError>> Parser::parse(const std::string& str) {
    using boost::spirit::qi::phrase_parse; 
    using boost::spirit::ascii::space; 
    using Iterator = std::string::const_iterator; 

    InstructionParser<Iterator> grammar; 
    Iterator iter = str.begin(); 
    Iterator end = str.end(); 

    instr::Instruction instruction; 
    bool success = phrase_parse(iter, end, grammar, space, instruction); 

    if (success && iter == end) {
        return instruction; 
    } else {
        // parsing error
        return std::unexpected(ParserError::InstructionParseError);
    }
}

ArithOpType_ ArithOpTypeParser;
DataType_ DataTypeParser;

