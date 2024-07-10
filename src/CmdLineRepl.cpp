#include "CmdLineRepl.hpp"
#include <string>
#include <iostream>

CmdLineRepl::CmdLineRepl() {
    
}

void CmdLineRepl::run() {
    while (true) {
        std::string input; 
        std::cin>>input; 
        std::cout<<input; 
    }
}
