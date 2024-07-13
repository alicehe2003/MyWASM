#include "CmdLineRepl.hpp"
#include <string>
#include <iostream>
#include "Parser.hpp"

CmdLineRepl::CmdLineRepl() : parser(new Parser()) {}; 

CmdLineRepl::~CmdLineRepl() {
    delete parser; 
}

void CmdLineRepl::run() {
    while (true) {
        std::string input; 
        std::getline(std::cin, input); 
        Instruction* instruction = parser->parse(input); 
        if (instruction != nullptr) {
            std::cout << "instruction address: " << instruction << std::endl; 
            std::cout << input << std::endl; 
        }
    }
}
