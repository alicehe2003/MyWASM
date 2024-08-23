#include <iostream>
#include "CmdLineRepl.hpp"
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
    DataType data = u32; 
    std::string str = "i32"; 
    DataType_ dt;
    bool r = parse(str.begin(), str.end(), dt, data); 
    assert(data == i32);

    // testing parse ArithOpType_ 
    ArithOpType opType = Sub; 
    std::string str1 = "add"; 
    ArithOpType_ dt1; 
    bool r1 = parse(str1.begin(), str.end(), dt1, opType); 
    assert(opType == Add); 

    return 0; 
}
