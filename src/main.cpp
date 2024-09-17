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

    CmdLineRepl repl; 
    // repl.run(); 
    repl.testInstructions(); 
    repl.testParseInstructions(); 
    // repl.testFunctions(); 
    repl.testFunctionParser(); 
    repl.testLocalInstr(); 

    return 0; 
}
