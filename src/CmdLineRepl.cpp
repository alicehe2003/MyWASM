#include "CmdLineRepl.hpp"
#include <string>
#include <iostream>
#include "Parser.hpp"
#include "Interpreter.hpp"
#include "State.hpp"

CmdLineRepl::CmdLineRepl() 
    : parser(Parser()), interpreter(Interpreter(State())) {}; 


void CmdLineRepl::processCommand(std::string command) {
    auto commandResult = parser.parse(command);

    if (commandResult.has_value()) {
        Instruction validCommand = commandResult.value();
        interpreter.interpret(validCommand);
    } else {
        std::visit([](const auto& error) {
            if constexpr (std::is_same_v<decltype(error), DataError>) {
                switch (error) {
                    case DataError::InvalidDataError:
                        std::cerr << "Invalid data error." << std::endl;
                        break;
                    case DataError::DataSizeMismatchError:
                        std::cerr << "Data size mismatch error." << std::endl;
                        break;
                    case DataError::DataTypeMismatchError:
                        std::cerr << "Data type mismatch error." << std::endl;
                        break;
                    default:
                        std::cerr << "Unknown data error." << std::endl;
                        break;
                }
            }
            else if constexpr (std::is_same_v<decltype(error), CallError>) {
                switch (error) {
                    case CallError::InvalidIdentifierError:
                        std::cerr << "Invalid identifier error." << std::endl; 
                        break; 
                    default: 
                        std::cerr << "Unknown call error." << std::endl; 
                }
            } else if constexpr (std::is_same_v<decltype(error), InstructionError>) {
                switch (error) {
                    case InstructionError::InvalidOpCodeError:
                        std::cerr << "Invalid op code error." << std::endl; 
                        break; 
                    default: 
                        std::cerr << "Unknown Instruction error." << std::endl; 
                }
            } else if constexpr (std::is_same_v<decltype(error), ParserError>) {
                switch (error) {
                    case ParserError::InstructionParseError: 
                        std::cerr << "Boost spirit parsing error." << std::endl; 
                        break; 
                    default: 
                        std::cerr << "Unknown parsing error." << std::endl; 
                }
            } else {
                std::cerr << "Unknown error." << std::endl; 
            }
        }, commandResult.error());
    }
}

void CmdLineRepl::run() {

    while (true) {

        std::string input; 
        std::getline(std::cin, input); 
        if (input == "end") {
            break; 
        }

        processCommand(input); 
    }

    std::cout << "Ending program. " << std::endl; 
}

void CmdLineRepl::test() {
    // TESTING: create commands and parse 
    std::string callCommand = "call $log"; 
    std::string const10Command = "i32.const 10"; 
    std::string const3Command = "i32.const 3"; 
    std::string addCommand = "i32.add"; 
    std::string const5Command = "i32.const 5"; 
    std::string subCommand = "i32.sub"; 
    std::string mulCommand = "i32.mul";
    std::string divCommand = "i32.div_s"; 
    std::string sizeCommand = "memory.size"; 

    processCommand(const10Command); 
    processCommand(const3Command); 
    processCommand(addCommand); 
    std::cout << "Testing add, expecting 13 " << std::endl;  
    processCommand(callCommand); 
    
    processCommand(const5Command); 
    processCommand(subCommand); 
    std::cout << "Testing sub, expecting 8 " << std::endl; 
    processCommand(callCommand); 

    processCommand(const3Command); 
    processCommand(mulCommand); 
    std::cout << "Testing mul, expecting 24 " << std::endl; 
    processCommand(callCommand); 
    
    
    processCommand(const3Command); 
    processCommand(divCommand); 
    std::cout << "Testing div, expecting 8 " << std::endl; 
    processCommand(callCommand); 
     
    
    processCommand(sizeCommand); 
    std::cout << "Testing memory.size, expecting 1024x1024 = 1048576 " << std::endl; 
    processCommand(callCommand); 

    // testing load and store 
    std::string const1Command = "i32.const 1"; 
    std::string storeCommand = "i32.store"; 
    std::string loadCommand = "i32.load"; 

    processCommand(const1Command); 
    processCommand(const10Command); 
    processCommand(storeCommand); 
    processCommand(const1Command); 
    processCommand(loadCommand); 
    std::cout << "Testing load and store, expecting 10 " << std::endl; 
    processCommand(callCommand); 

    // testing negative numbers 
    std::string constNeg1Command = "i32.const -1"; 

    processCommand(constNeg1Command); 
    processCommand(addCommand);  
    std::cout << "Testing add on negative number, expecting 9 " << std::endl; 
    processCommand(callCommand); 
}
