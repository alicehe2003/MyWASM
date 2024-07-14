#pragma once

#include "Parser.hpp"
#include "Interpreter.hpp"
#include "State.hpp"

class CmdLineRepl {
    public: 
        CmdLineRepl(); 
        ~CmdLineRepl(); 
        void run(); 

    
    private: 
        Parser* parser; 
        Interpreter* interpreter; 
}; 


