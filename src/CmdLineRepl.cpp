#include "CmdLineRepl.hpp"
#include <string>
#include <iostream>
#include "Parser.hpp"
#include "Interpreter.hpp"
#include "State.hpp"

CmdLineRepl::CmdLineRepl() 
    : parser(Parser()), interpreter(Interpreter(State())) {}; 

void CmdLineRepl::run() {
    // TESTING: create commands and parse 
    
    std::string const10Command = "i32.const 10"; 
    std::string const3Command = "i32.const 3"; 
    Instruction* const10Instruction = parser.parse(const10Command); 
    Instruction* const3Instruction = parser.parse(const3Command);
    
    std::string addCommand = "i32.add"; 
    Instruction* addInstruction = parser.parse(addCommand); 

    interpreter.interpret(*const10Instruction); 
    interpreter.interpret(*const3Instruction); 
    interpreter.interpret(*addInstruction); 
    
    std::cout<< interpreter.state.heap << std::endl; 
    Data d = interpreter.state.stk.top(); 
    std::cout << *(interpreter.interpretData<int>(d)) << std::endl;
     


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
