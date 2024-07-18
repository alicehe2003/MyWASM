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
    std::string callCommand = "call $log"; 
    Instruction callInstruction = parser.parse(callCommand); 
    
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
    interpreter.interpret(callInstruction);
    
    std::string const5Command = "i32.const 5"; 
    Instruction const5Instruction = parser.parse(const5Command); 
    std::string subCommand = "i32.sub"; 
    Instruction subInstruction = parser.parse(subCommand); 
    interpreter.interpret(const5Instruction); 
    interpreter.interpret(subInstruction); 

    std::cout << "Testing sub, expecting 8 " << std::endl; 
    interpreter.interpret(callInstruction);

    std::string mulCommand = "i32.mul";
    Instruction mulInstruction = parser.parse(mulCommand); 
    interpreter.interpret(const3Instruction); 
    interpreter.interpret(mulInstruction); 

    std::cout << "Testing mul, expecting 24 " << std::endl; 
    interpreter.interpret(callInstruction);
    
    std::string divCommand = "i32.div_s"; 
    Instruction divInstruction = parser.parse(divCommand); 
    interpreter.interpret(const3Instruction); 
    interpreter.interpret(divInstruction);

    std::cout << "Testing div, expecting 8 " << std::endl; 
    interpreter.interpret(callInstruction);
     
    std::string sizeCommand = "memory.size"; 
    Instruction sizeInstruction = parser.parse(sizeCommand); 
    interpreter.interpret(sizeInstruction); 

    std::cout << "Testing memory.size, expecting 1024x1024 = 1048576 " << std::endl; 
    interpreter.interpret(callInstruction);
     
    std::cout << "Testing call $log, expecting 1048576 " << std::endl; 
    interpreter.interpret(callInstruction); 

    // testing load and store 
    std::string const1Command = "i32.const 1"; 
    std::string storeCommand = "i32.store"; 
    std::string loadCommand = "i32.load"; 
    Instruction const1Instruction = parser.parse(const1Command); 
    Instruction storeInstruction = parser.parse(storeCommand); 
    Instruction loadInstruction = parser.parse(loadCommand); 
    // store value at offset 1 
    interpreter.interpret(const1Instruction); 
    // number to store 
    interpreter.interpret(const10Instruction); 
    // store in memory with offset 1
    interpreter.interpret(storeInstruction); 
    // offset in memory to load from 
    interpreter.interpret(const1Instruction); 
    // load from memory with offset 1
    interpreter.interpret(loadInstruction); 
    std::cout << "Testing load and store, expecting 10 " << std::endl; 
    interpreter.interpret(callInstruction); 

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
