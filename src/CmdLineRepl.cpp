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
    
    Instruction const10Instruction = parser.parse(const10Command); 
    Instruction const3Instruction = parser.parse(const3Command);
    
    std::string addCommand = "i32.add"; 
    Instruction addInstruction = parser.parse(addCommand); 

    interpreter.interpret(const10Instruction); 
    interpreter.interpret(const3Instruction); 
    interpreter.interpret(addInstruction); 
    
    std::cout << "Testing add, expecting 13 " << std::endl;  
    Data d0 = interpreter.state.stk.top(); 
    std::cout << "Actual value: " << *(d0.interpretData<int>()) << std::endl;
     
    std::string const5Command = "i32.const 5"; 
    Instruction const5Instruction = parser.parse(const5Command); 
    std::string subCommand = "i32.sub"; 
    Instruction subInstruction = parser.parse(subCommand); 
    interpreter.interpret(const5Instruction); 
    interpreter.interpret(subInstruction); 

    std::cout << "Testing sub, expecting 8 " << std::endl; 
    Data d1 = interpreter.state.stk.top(); 
    std::cout << "Actual value: " << *(d1.interpretData<int>()) << std::endl;
     
    std::string mulCommand = "i32.mul";
    Instruction mulInstruction = parser.parse(mulCommand); 
    interpreter.interpret(const3Instruction); 
    interpreter.interpret(mulInstruction); 

    std::cout << "Testing mul, expecting 24 " << std::endl; 
    Data d2 = interpreter.state.stk.top(); 
    std::cout << "Actual value: " << *(d2.interpretData<int>()) << std::endl;
     
    std::string divCommand = "i32.div_s"; 
    Instruction divInstruction = parser.parse(divCommand); 
    interpreter.interpret(const3Instruction); 
    interpreter.interpret(divInstruction);

    std::cout << "Testing div, expecting 8 " << std::endl; 
    Data d3 = interpreter.state.stk.top(); 
    std::cout << "Actual value: " << *(d3.interpretData<int>()) << std::endl;
     
    std::string sizeCommand = "memory.size"; 
    Instruction sizeInstruction = parser.parse(sizeCommand); 
    interpreter.interpret(sizeInstruction); 

    std::cout << "Testing memory.size, expecting 1024x1024 = 1048576 " << std::endl; 
    Data d4 = interpreter.state.stk.top(); 
    std::cout << "Actual value: " << *(d4.interpretData<int>()) << std::endl;
     

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
