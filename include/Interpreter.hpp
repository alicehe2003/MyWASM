#pragma once
#include "State.hpp"
#include "Instruction.hpp"

using namespace instr;

/**
 * @brief Interpreter class used to manipulate state based on given command. 
 */
class Interpreter {
    public: 
        Interpreter(); 

        template <typename T>
        T getValidData(Data& data); 

        /** 
         * Given an instruction, perform the necessary change to state. 
         * 
         * @param instruction is the given instruction. The actual type of instruction
         * must be one of the defined types (Const, Arith, Size, Load, Store). 
         * 
         */
        void interpret(Instruction& instruction); 

        /**
         * Interpret const instruction. 
         */
        void interpret(ConstInstr& instruction, Context& context); 

        /**
         * Interpret arith instruction. 
         */
        void interpret(ArithInstr& instruction, Context& context); 

        /**
         * Interpret size instruction. 
         */
        void interpret(SizeInstr& instruction, Context& context); 

        /**
         * Interpret load instruction. 
         */
        void interpret(LoadInstr& instruction, Context& context); 

        /** 
         * Interpret store instruction. 
         */
        void interpret(StoreInstr& instruction, Context& context); 

        /**
         * Interpret call instruction. 
         * 
         * Print to console the element at the top of the stack without removing. 
         */
        void interpret(CallInstr& instruction, Context& context); 

        /**
         * Interpret local.get instruction. 
         */
        void interpret(LocalInstr& instruction, Context& context); 

        /**
         * Add function definition. 
         */
        void addFunctionDef(Function func) {
            std::string funcName = func.name; 
            functionTable.insert({funcName, func}); 
        }; 

        State state; 
        std::unordered_map<std::string, Function> functionTable; 
}; 
