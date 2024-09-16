#include "CmdLineRepl.hpp"
#include <string>
#include <iostream>
#include "Parser.hpp"
#include "Interpreter.hpp"
#include "State.hpp"

#include <variant>
#include <cassert>
#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix/operator.hpp>
#include <boost/fusion/tuple.hpp>

#include <tuple>

CmdLineRepl::CmdLineRepl() 
    : parser(Parser()) {
        assert(!interpreter.state.contexts.empty()); 
    }; 

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

/**
 * TESTING 
 */

void CmdLineRepl::testInstructions() {
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

    // testing arithmetic instructions 
    processCommand(const10Command); 
    processCommand(const3Command); 
    processCommand(addCommand); 
    std::cout << "Testing add, expecting 13." << std::endl;  
    processCommand(callCommand); 
    
    processCommand(const5Command); 
    processCommand(subCommand); 
    std::cout << "Testing sub, expecting 8." << std::endl; 
    processCommand(callCommand); 

    processCommand(const3Command); 
    processCommand(mulCommand); 
    std::cout << "Testing mul, expecting 24." << std::endl; 
    processCommand(callCommand); 
    
    
    processCommand(const3Command); 
    processCommand(divCommand); 
    std::cout << "Testing div, expecting 8." << std::endl; 
    processCommand(callCommand); 
     
    // testing memory size 
    processCommand(sizeCommand); 
    std::cout << "Testing memory.size, expecting 1024x1024 = 1048576." << std::endl; 
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
    std::cout << "Testing load and store, expecting 10." << std::endl; 
    processCommand(callCommand); 

    // testing negative numbers 
    std::string constNeg1Command = "i32.const -1"; 

    processCommand(constNeg1Command); 
    processCommand(addCommand);  
    std::cout << "Testing add on negative number, expecting 9." << std::endl; 
    processCommand(callCommand); 
}

void CmdLineRepl::testParseInstructions() {
    // testing parse DataType_
    instr::DataType data = instr::DataType::u32; 
    std::string str = "i32"; 
    DataType_ dt;
    bool r = parse(str.begin(), str.end(), dt, data); 
    assert(data == instr::DataType::i32);
    std::cout << "DataType_ parsing successful." << std::endl; 

    // testing parse ArithOpType_ 
    instr::ArithOpType opType = instr::ArithOpType::Sub; 
    std::string str1 = "add"; 
    ArithOpType_ dt1; 
    bool r1 = parse(str1.begin(), str1.end(), dt1, opType); 
    assert(opType == instr::ArithOpType::Add); 
    std::cout << "ArithOpType_ parsing successful." << std::endl; 

    using boost::spirit::ascii::space;
    
    // testing parse ArithInstr
    ArithInstrParser<std::string::iterator> p; 
    std::string str2 = "u32.sub"; 
    instr::ArithInstr dt2; 
    bool r2 = phrase_parse(str2.begin(), str2.end(), p, space, dt2);

    assert(dt2.dataType == instr::DataType::u32);
    assert(r2);
    assert(dt2.opType == instr::ArithOpType::Sub); 
    std::cout << "ArithInstr parsing successful." << std::endl; 

    // testing parse ConstInstr 
    std::string input = "u32.const 42"; 
    ConstInstrParser<std::string::iterator> parser; 
    instr::ConstInstr dt8; 
    bool result = phrase_parse(input.begin(), input.end(), parser, ascii::space, dt8); 

    assert(result); 
    std::cout << "ConstInstr parsing successful." << std::endl; 
   
    // testing parse SizeInstr 
    SizeInstrParser<std::string::iterator> p1; 
    std::string str3 = "memory.size"; 
    SizeInstr dt3; 
    bool r3 = phrase_parse(str3.begin(), str3.end(), p1, space, dt3); 

    assert(r3); 
    std::cout << "SizeInstr parsing successful." << std::endl; 

    // testing parser LoadInstr 
    LoadInstrParser<std::string::iterator> p2; 
    std::string str4 = "u32.load"; 
    instr::LoadInstr dt4; 
    bool r4 = phrase_parse(str4.begin(), str4.end(), p2, space, dt4); 

    assert(r4);
    std::cout << "LoadInstr parsing successful." << std::endl; 

    // testing parser StoreInstr 
    StoreInstrParser<std::string::iterator> p3; 
    std::string str5 = "u32.store"; 
    instr::StoreInstr dt5; 
    bool r5 = phrase_parse(str5.begin(), str5.end(), p3, space, dt5); 

    assert(r5);
    std::cout << "StoreInstr parsing successful." << std::endl; 

    // testing parser Instruction 
    instr::Data data2(instr::DataType::i32, 5);
    InstructionParser<std::string::iterator> p4; 
    std::string str6 = "i32.const 43"; 
    instr::Instruction dt6; 
    bool r6 = phrase_parse(str6.begin(), str6.end(), p4, space, dt6); 

    assert(r6); 
    std::cout << "Instruction parsing successful." << std::endl; 

    // testing parser CallInstr 
    CallInstrParser<std::string::iterator> p5; 
    std::string str7 = "call $log"; 
    instr::CallInstr dt7; 
    bool r7 = phrase_parse(str7.begin(), str7.end(), p5, space, dt7); 

    assert(r7);
    assert(dt7.identifier == "log"); 
    std::cout << "CallInstr parsing successful." << std::endl; 
}

void CmdLineRepl::testFunctions() {
    instr::DataType type = i32; 
    std::vector<Param> params; 
    params.push_back({.ident = "x", .dataType = type}); 
    params.push_back({.ident = "y", .dataType = type}); 
    std::vector<instr::Instruction> instructions; 
    ArithInstr addInstr(ArithOpType::Add, type); 

    instr::Data data1(type, 1); 
    instr::Data data2(type, 2); 
    instr::ConstInstr const1(data1); 
    instr::ConstInstr const2(data2); 

    instructions.push_back(const1); 
    instructions.push_back(const2); 

    instructions.push_back(addInstr); 
    Function function("adding", params, type, instructions); 

    std::string adding = "adding"; 
    interpreter.functionTable.insert(std::pair(adding, function)); 

    instr::CallInstr call("adding"); 

    Instruction instruction(call); 

    interpreter.interpret(instruction); 

    assert(interpreter.state.contexts.top().stack.top().getDataVal()[0] == 3); 
    std::cout << "Simple function call successful." << std::endl; 
}

void CmdLineRepl::testFunctionParser() {
    // testing function parser 
    using boost::spirit::ascii::space;
    FunctionParser<std::string::iterator> parser; 
    std::string str = "(func $hello (param $x i32) (param $y i32) (result i32) i32.const 3 i32.const 4 i32.add)"; 
    bool result = phrase_parse(str.begin(), str.end(), parser, space); 

    assert(result); 
    std::cout << "Simple function parser successful." << std::endl; 
}
