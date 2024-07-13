#pragma once

#include "Parser.hpp"

class CmdLineRepl {
    public: 
        CmdLineRepl(); 
        ~CmdLineRepl(); 
        void run(); 

    
    private: 
        Parser* parser; 
        
}; 


