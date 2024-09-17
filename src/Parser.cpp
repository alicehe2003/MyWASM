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

std::expected<std::variant<instr::Instruction, Function>, std::variant<instr::DataError, instr::CallError, instr::InstructionError, ParserError>> Parser::parse(const std::string& str) {
    using boost::spirit::qi::phrase_parse; 
    using boost::spirit::ascii::space; 
    using Iterator = std::string::const_iterator; 

    InstructionParser<Iterator> grammar; 
    FunctionParser<Iterator> functionGrammar; 

    Iterator iter = str.begin(); 
    Iterator end = str.end(); 

    Iterator iterFunc = str.begin(); 
    Iterator endFunc = str.end(); 

    instr::Instruction instruction; 
    Function function; 

    bool success = phrase_parse(iter, end, grammar, space, instruction); 
    bool funcSuccess = phrase_parse(iterFunc, endFunc, functionGrammar, space, function); 

    if (success && iter == end) {
        return instruction; 
    } else if (funcSuccess && iterFunc == endFunc) {
        return function; 
    } else {
        // parsing error
        std::cout << "PARSING ERROR" << std::endl; 

        return std::unexpected(ParserError::InstructionParseError);
    }
}

ArithOpType_ ArithOpTypeParser;
DataType_ DataTypeParser;

