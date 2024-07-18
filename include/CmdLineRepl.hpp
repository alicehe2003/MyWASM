#pragma once

#include "Parser.hpp"
#include "Interpreter.hpp"
#include "State.hpp"

class CmdLineRepl {
    public: 
        CmdLineRepl(); 
        void run(); 

        // TODO delete or refactor these tests 
        void test(); 
    
    private: 
        Parser parser; 
        Interpreter interpreter; 
}; 


