#pragma once

#include "Parser.hpp"
#include "Interpreter.hpp"
#include "State.hpp"

/**
 * @brief Command line repl for processing each command. 
 * Contains functions for testing purposes. 
 */
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

        /**
         * Testing functions. 
         */
        void testInstructions(); 
        void testParseInstructions(); 
        void testFunctions(); 
        void testFunctionParser(); 
        void testLocalInstr(); 
        void testInstructionsMore(); 
    
        Parser parser; 
        Interpreter interpreter; 
}; 


