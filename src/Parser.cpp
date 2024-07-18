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

Instruction Parser::parse(const std::string& str) {
    // Define regex patterns for acceptable forms 
    boost::regex regex_instruction_val(R"(^(i32)\.(const) (\d+)$)");
    boost::regex regex_instruction(R"(^(i32)\.(add|sub|mul|div_s|load|store)$)");
    boost::regex regex_memory_size_instruction(R"(^memory\.size$)");
    boost::regex regex_call(R"(^call \$(\w+)$)");

    boost::smatch match; 

    if (boost::regex_match(str, match, regex_instruction_val)) {
        // Match form: i32.const 5 

        DataType dataType; 
        if (match[1] == "i32") {
            dataType = i32; 
        } else if (match[1] == "u32") {
            dataType = u32; 
        } else {
            // throw error: invalid data type 
        }

        Data data(dataType); 
        if (dataType == i32) {
            int32_t val = static_cast<int32_t>(std::stoi(match[3])); 
            data.setDataVal(val); 
        } else if (dataType == u32) {
            uint32_t val = static_cast<uint32_t>(std::stoi(match[3])); 
            data.setDataVal(val); 
        } else {
            // throw error: invalid data type 
        }

        if (match[2] == "const") {
            Instruction instruction = Instruction(ConstInstr(data)); 
            return instruction; 
        } else {
            // throw error: invalid op code 
        }

    } else if (boost::regex_match(str, match, regex_instruction)) {
        // Match form: i32.add, i32.sub, i32.mul, i32.div_s, i32.load, i32.store

        DataType dataType; 
        if (match[1] == "i32") {
            dataType = i32; 
        } else if (match[1] == "u32") {
            dataType = u32; 
        } else {
            // throw error: invalid data type 
        } 

        if (match[2] == "add") {
            Instruction instruction = Instruction(ArithInstr(Add, dataType)); 
            return instruction; 
        } else if (match[2] == "sub") {
            Instruction instruction = Instruction(ArithInstr(Sub, dataType)); 
            return instruction; 
        } else if (match[2] == "mul") {
            Instruction instruction = Instruction(ArithInstr(Mult, dataType)); 
            return instruction; 
        } else if (match[2] == "div_s") {
            Instruction instruction = Instruction(ArithInstr(Div_s, dataType)); 
            return instruction; 
        } else if (match[2] == "load") {
            Instruction instruction = Instruction(LoadInstr(0, dataType)); 
            return instruction; 
        } else if (match[2] == "store") {
            Instruction instruction = Instruction(StoreInstr(0, dataType)); 
            return instruction; 
        } else {
            // throw error: invalid op code 
        }
 
    } else if (boost::regex_match(str, match, regex_memory_size_instruction)) {
        // Match form: memory.size

        Instruction instruction = Instruction(SizeInstr()); 
        return instruction; 

    } else if (boost::regex_match(str, match, regex_call)) {
        // Match form: call $log 

        if (match[1] == "log") {
            Instruction instruction = Instruction(CallInstr("log")); 
            return instruction; 
        } else {
            // throw error: invalid indentifier 
        }
        
    } else {
        // throw error: invalid assembly command 

        throw std::invalid_argument("Invalid assembly command. "); 
    }

    // TODO handle return statement: return invalid instruction type ??? 
}

