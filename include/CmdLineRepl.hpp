#pragma once

#include "Parser.hpp"

class CmdLineRepl {
    public: 
        CmdLineRepl(); 

        void run(); 

    
    private: 
        Parser parser; 

}; 


