#pragma once
#include "State.hpp"
#include "Instruction.hpp"

using namespace instr;

class Interpreter {
    public: 
        Interpreter(State state); 

        template <typename T>
        T getValidData(Data& data); 

        /** 
         * Given an instruction, perform the necassary change to state. 
         * 
         * @param instruction is the given instruction. The actual type of instruction
         * must be one of the defined types (Const, Arith, Size, Load, Store). 
         * 
         */
        void interpret(Instruction& instruction); 

        /**
         * Interpret const instruction. 
         */
        void interpret(ConstInstr& instruction); 

        /**
         * Interpret arith instruction. 
         */
        void interpret(ArithInstr& instruction); 

        /**
         * Interpret size instruction. 
         */
        void interpret(SizeInstr& instruction); 

        /**
         * Interpret load instruction. 
         */
        void interpret(LoadInstr& instruction); 

        /** 
         * Interpret store instruction. 
         */
        void interpret(StoreInstr& instruction); 

        /**
         * Interpret call instruction. 
         * 
         * Print to console the element at the top of the stack without removing. 
         */
        void interpret(CallInstr& instruction); 

    // private: TODO make private 
        State state; 
}; 
