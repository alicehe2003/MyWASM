#pragma once
#include "State.hpp"
#include "ArithInstr.hpp"
#include "ConstInstr.hpp"
#include "LoadInstr.hpp"
#include "SizeInstr.hpp"
#include "StoreInstr.hpp"

class Interpreter {
    public: 
        Interpreter(State* state); 

        void interpretConst(ConstInstr instruction); 

        void interpretArith(ArithInstr instruction); 

        void interpretSize(SizeInstr instruction); 

        void interpretLoad(LoadInstr instruction); 

        void interpretStore(StoreInstr instruction); 

    private: 
        State* state; 
}; 
