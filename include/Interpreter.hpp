#pragma once
#include "State.hpp"
#include "ArithInstr.hpp"
#include "ConstInstr.hpp"
#include "LoadInstr.hpp"
#include "SizeInstr.hpp"
#include "StoreInstr.hpp"
#include "Instruction.hpp"

class Interpreter {
    public: 
        Interpreter(State* state); 

        template <typename T>
        std::expected<T, DataError> interpretData(Data& data);

        template <typename T>
        T getValidData(Data& data); 

        void interpretConst(ConstInstr instruction); 

        void interpretArith(ArithInstr instruction); 

        void interpretSize(SizeInstr instruction); 

        void interpretLoad(LoadInstr instruction); 

        void interpretStore(StoreInstr instruction); 

    private: 
        State* state; 
}; 
