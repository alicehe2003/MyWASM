#include <iostream>
#include "CmdLineRepl.hpp"
using namespace std;

int main () {
    cout << "HelloWorld!" << endl;

    CmdLineRepl repl; 
    repl.run(); 

    return 0; 
}
