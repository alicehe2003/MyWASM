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

    DataType data = u32; 
    std::string str = "i32"; 
    DataType_ dt;

    bool r = parse(str.begin(), str.end(), dt, data); 

    assert(data == i32);

    return 0; 
}
