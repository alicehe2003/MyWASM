#include <iostream>
#include "CmdLineRepl.hpp"
#include "Parser.hpp"
#include "Data.hpp"

using namespace std;


#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix/operator.hpp>

#include <boost/fusion/tuple.hpp>

#include <variant>
#include <cassert>

int main () {
    
    cout << "Input WebAssembly command, 'end' to end program. " << endl;
    cout << "Supported data types include i32 and u32. " << endl; 
    cout << "Supported functionalities include arithmetic instructions, memory instructions, and functions. " << endl; 
    cout << "Functions must be expressed in a single line on the command line repl. " << endl; 

    CmdLineRepl repl; 
    repl.run(); 
    /*
    repl.testInstructions(); 
    repl.testParseInstructions(); 
    repl.testFunctions(); 
    repl.testFunctionParser(); 
    repl.testLocalInstr(); 
    repl.testInstructionsMore(); 
    */ 

    return 0; 
}
