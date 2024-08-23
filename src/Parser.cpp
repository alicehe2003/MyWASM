#include "Parser.hpp"
#include <boost/regex.hpp>
#include <iostream>
#include "Instruction.hpp"
#include "ConstInstr.hpp"
#include "ArithInstr.hpp"
#include "LoadInstr.hpp"
#include "SizeInstr.hpp"
#include "StoreInstr.hpp"

Parser::Parser() {

}

std::expected<Instruction, std::variant<DataError, CallError, InstructionError>> Parser::parse(const std::string& str) {
    
    return std::unexpected(DataError::InvalidDataError);
}
