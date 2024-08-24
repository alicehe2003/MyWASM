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

std::expected<instr::Instruction, std::variant<instr::DataError, instr::CallError, instr::InstructionError>> Parser::parse(const std::string& str) {

    return std::unexpected(instr::DataError::InvalidDataError);
}


ArithOpType_ ArithOpTypeParser;
DataType_ DataTypeParser;
