#include "Interpreter.hpp"
#include "State.hpp"
#include "ArithInstr.hpp"
#include "ConstInstr.hpp"
#include "LoadInstr.hpp"
#include "SizeInstr.hpp"
#include "StoreInstr.hpp"

Interpreter::Interpreter(State* state) {
    this->state = state; 
}

void Interpreter::interpretConst(ConstInstr instruction) {
    
}

void Interpreter::interpretArith(ArithInstr instruction) {

}

void Interpreter::interpretSize(SizeInstr instruction) {

}

void Interpreter::interpretLoad(LoadInstr instruction) {

}

void Interpreter::interpretStore(StoreInstr instruction) {

}
