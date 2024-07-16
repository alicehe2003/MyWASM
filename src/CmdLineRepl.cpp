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
    delete interpreter;
}

void CmdLineRepl::run() {
    // TESTING: create commands and parse 
    std::string const10Command = "i32.const 10"; 
    std::string const3Command = "i32.const 3"; 
    Instruction* const10Instruction = parser->parse(const10Command); 
    Instruction* const3Instruction = parser->parse(const3Command);
    


    /*
    while (true) {

        std::string input; 
        std::getline(std::cin, input); 
        if (input == "end") {
            break; 
        }
        Instruction* instruction = parser->parse(input); 
        
    }
    */ 
}
