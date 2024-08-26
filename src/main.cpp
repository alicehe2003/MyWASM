#include <iostream>
//#include "CmdLineRepl.hpp"
#include "Parser.hpp"
using namespace std;


#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix/operator.hpp>

#include <boost/fusion/tuple.hpp>

int main () {
    /*
    cout << "Input WebAssembly command, 'end' to end program. " << endl;

    CmdLineRepl repl; 
    // repl.run(); 
    repl.test(); 
    */ 

   // testing parse DataType_
    instr::DataType data = instr::DataType::u32; 
    std::string str = "i32"; 
    DataType_ dt;
    bool r = parse(str.begin(), str.end(), dt, data); 
    assert(data == instr::DataType::i32);

    // testing parse ArithOpType_ 
    instr::ArithOpType opType = instr::ArithOpType::Sub; 
    std::string str1 = "add"; 
    ArithOpType_ dt1; 
    bool r1 = parse(str1.begin(), str1.end(), dt1, opType); 
    assert(opType == instr::ArithOpType::Add); 

    using boost::spirit::ascii::space;

    
    // testing parse ArithInstr
    ArithInstrParser<std::string::iterator> p; 
    std::string str2 = "u32.sub"; 
    instr::ArithInstr dt2; 
    bool r2 = phrase_parse(str2.begin(), str2.end(), p, space, dt2);

    assert(dt2.dataType == instr::DataType::u32);
    assert(r2);
    assert(dt2.opType == instr::ArithOpType::Sub);


    // testing parse ConstInstr 
    std::string input = "u32.const 42"; 
    boost::fusion::vector<instr::DataType, boost::variant<int, uint>> constInstr; 
    ConstInstrParser<std::string::iterator> parser; 
    bool result = phrase_parse(input.begin(), input.end(), parser, ascii::space, constInstr); 

    assert(result); 
    std::cout << constInstr << std::endl;
    std::cout << get<0>(constInstr) <<std::endl; 
   
    // testing parse SizeInstr 
    SizeInstrParser<std::string::iterator> p1; 
    std::string str3 = "memory.size"; 
    SizeInstr dt3; 
    bool r3 = phrase_parse(str3.begin(), str3.end(), p1, space, dt3); 

    assert(r3); 

    // testing parser LoadInstr 
    LoadInstrParser<std::string::iterator> p2; 
    std::string str4 = "u32.load"; 
    instr::LoadInstr dt4; 
    bool r4 = phrase_parse(str4.begin(), str4.end(), p2, space, dt4); 

    assert(r4);

    // testing parser StoreInstr 
    StoreInstrParser<std::string::iterator> p3; 
    std::string str5 = "u32.store"; 
    instr::StoreInstr dt5; 
    bool r5 = phrase_parse(str5.begin(), str5.end(), p3, space, dt5); 

    assert(r5);
   



    return 0; 
}
