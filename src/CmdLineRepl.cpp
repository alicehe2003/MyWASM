#include "CmdLineRepl.hpp"
#include <string>
#include <iostream>
#include "Parser.hpp"
#include "Interpreter.hpp"
#include "State.hpp"

CmdLineRepl::CmdLineRepl() 
    : parser(new Parser()), interpreter(new Interpreter(new State())) {}; 

CmdLineRepl::~CmdLineRepl() {
    delete parser; 
}

void CmdLineRepl::run() {
    while (true) {
        std::string input; 
        std::getline(std::cin, input); 
        if (input == "end") {
            break; 
        }
        Instruction* instruction = parser->parse(input); 
        if (instruction->getActualType() == "ArithInstr") {
            std::cout << "ArithInstr" << std::endl; 
        }
        
    }
}
