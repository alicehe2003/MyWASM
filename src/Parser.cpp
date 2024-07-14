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

Instruction* Parser::parse(const std::string& str) {
    // Define regex patterns for acceptable forms 
    boost::regex regex_instruction_val(R"(^(i32)\.(const) (\d+)$)");
    boost::regex regex_instruction(R"(^(i32)\.(add|sub|mul|div_s|load|store)$)");
    boost::regex regex_memory_size_instruction(R"(^memory\.size$)");
    boost::regex regex_memory_instruction(R"(^(i32)\.(load|store) \(memory (\d+)\)$)");

    boost::smatch match; 
    Instruction* instruction; 

    if (boost::regex_match(str, match, regex_instruction_val)) {
        // Match form: i32.const 5 

        DataType dataType; 
        if (match[1] == "i32") {
            dataType = i32; 
        } else if (match[1] == "u32") {
            dataType = u32; 
        } else {
            // throw error 
        }

        Data data(dataType); 
        if (dataType == i32) {
            int32_t val = static_cast<int32_t>(std::stoi(match[3])); 
            data.setDataVal(val); 
        } else if (dataType == u32) {
            uint32_t val = static_cast<uint32_t>(std::stoi(match[3])); 
            data.setDataVal(val); 
        } else {
            // throw error 
        }

        if (match[2] == "const") {
            instruction = new ConstInstr(data); 
        } else {
            // throw error 
        }

    } else if (boost::regex_match(str, match, regex_instruction)) {
        // Match form: i32.add, i32.sub, i32.mul, i32.div_s, i32.load, i32.store

        DataType dataType; 
        if (match[1] == "i32") {
            dataType = i32; 
        } else if (match[1] == "u32") {
            dataType = u32; 
        } else {
            // throw error 
        } 

        if (match[2] == "add") {
            instruction = new ArithInstr(Add, dataType); 
        } else if (match[2] == "sub") {
            instruction = new ArithInstr(Sub, dataType); 
        } else if (match[2] == "mul") {
            instruction = new ArithInstr(Mult, dataType); 
        } else if (match[2] == "div_s") {
            instruction = new ArithInstr(Div_s, dataType); 
        } else if (match[2] == "load") {
            instruction = new LoadInstr(0, dataType); 
        } else if (match[2] == "store") {
            instruction = new StoreInstr(0, dataType); 
        } else {
            // throw error 
        }
 
    } else if (boost::regex_match(str, match, regex_memory_size_instruction)) {
        // Match form: memory.size

        instruction = new SizeInstr(); 

    } else if (boost::regex_match(str, match, regex_memory_instruction)) {
        // Match form: i32.load (memory 5), i32.store (memory 5)

        // match[1] is data type string 
        // match[2] is instruction string 
        // match[3] is data value string

        DataType dataType; 
        if (match[1] == "i32") {
            dataType = i32; 
        } else if (match[1] == "u32") {
            dataType = u32; 
        } else {
            // throw error 
        } 

        int index = std::stoi(match[3]); 

        if (match[2] == "load") {
            instruction = new LoadInstr(index, dataType); 
        } else if (match[2] == "store") {
            instruction = new StoreInstr(index, dataType); 
        } else {
            // throw error 
        }

    } else {
        // throw error 
    }

    return instruction; 
}

