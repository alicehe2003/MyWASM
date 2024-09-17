#pragma once

#include "Parser.hpp"
#include "Interpreter.hpp"
#include "State.hpp"

class CmdLineRepl {
    public: 
        CmdLineRepl(); 
        void run(); 
        /**
         * @param command is the given string command 
         * 
         * Given a command, parse and interpret the command. 
         */
        void processCommand(std::string command); 

        // TODO delete or refactor these tests 
        void testInstructions(); 
        void testParseInstructions(); 
        void testFunctions(); 
        void testFunctionParser(); 
        void testLocalInstr(); 
        void testInstructionsMore(); 
    
    // private: 
        Parser parser; 
        Interpreter interpreter; 
}; 


