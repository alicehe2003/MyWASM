#include <iostream>
//#include "CmdLineRepl.hpp"
#include "Parser.hpp"
using namespace std;


#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix/operator.hpp>

int main () {
    /*
    cout << "Input WebAssembly command, 'end' to end program. " << endl;

    CmdLineRepl repl; 
    // repl.run(); 
    repl.test(); 
    */ 

   // testing parse DataType_
    // DataType data = u32; 
    // std::string str = "i32"; 
    // DataType_ dt;
    // bool r = parse(str.begin(), str.end(), dt, data); 
    // assert(data == i32);

    // // testing parse ArithOpType_ 
    // ArithOpType opType = Sub; 
    // std::string str1 = "add"; 
    // ArithOpType_ dt1; 
    // bool r1 = parse(str1.begin(), str1.end(), dt1, opType); 
    // assert(opType == Add); 

    using boost::spirit::ascii::space;

    // testing parse ArithInstr
    ArithInstrParser<std::string::iterator> p; 
    std::string str2 = "u32.sub"; 
    instr::ArithInstr dt2; 
    bool r2 = phrase_parse(str2.begin(), str2.end(), p, space, dt2);

    assert(dt2.dataType == instr::DataType::u32);
    assert(r2);
    assert(dt2.opType == instr::ArithOpType::Sub);

    return 0; 
}
