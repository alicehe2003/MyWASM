#include <iostream>
#include "CmdLineRepl.hpp"
using namespace std;

int main () {
    cout << "Input WebAssembly command, 'end' to end program. " << endl;

    CmdLineRepl repl; 
    repl.run(); 
    // repl.test(); 

    return 0; 
}
