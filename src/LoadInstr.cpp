#include "LoadInstr.hpp"

LoadInstr::LoadInstr(int index) {
    this->index = index; 
}

int LoadInstr::getIndex() {
    return this->index; 
}
