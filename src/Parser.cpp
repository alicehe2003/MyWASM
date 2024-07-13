#include "Parser.hpp"
#include <boost/regex.hpp>
#include "Instruction.hpp"
#include "ConstInstr.hpp"
#include <iostream>

Parser::Parser() {

}

Instruction* Parser::parse(const std::string& str) {
    // Define regex patterns for acceptable forms 
    boost::regex regex_instruction_val(R"(^(i32)\.(const) (\d+)$)");
    boost::regex regex_instruction(R"(^(i32)\.(add|sub|mul|div_u|load|store)$)");
    boost::regex regex_memory_size_instruction(R"(^memory\.size$)");
    boost::regex regex_memory_instruction(R"(^(i32)\.(load|store) \(memory (\d+)\)$)");

    boost::smatch match; 

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

        Instruction* instruction; 
        if (match[2] == "const") {
            instruction = new ConstInstr(data); 
        } else {
            // throw error 
        }

        return instruction; 
    } else if (boost::regex_match(str, match, regex_instruction)) {
        // Match form: i32.add, i32.sub, i32.mul, i32.div_u, i32.load, i32.store

        // match[1] is data type string 
        // match[2] is instruction string 
    } else if (boost::regex_match(str, match, regex_memory_size_instruction)) {
        // Match form: memory.size
    } else if (boost::regex_match(str, match, regex_memory_instruction)) {
        // Match form: i32.load (memory 5), i32.store (memory 5)

        // match[1] is data type string 
        // match[2] is instruction string 
        // match[3] is data value string
    } else {
        // throw error 
    }


}

