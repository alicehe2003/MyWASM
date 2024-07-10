#ifndef CMDLINEREPL_H
#define CMDLINEREPL_H

#include "Parser.hpp"

class CmdLineRepl {
    public: 
        CmdLineRepl(); 

        void run(); 

    
    private: 
        Parser parser; 

}; 

#endif
