#include "State.hpp"
#include "Instruction.hpp"
#include <iostream>


using namespace instr;
State::State() {

}

int State::size() {
    return sizeof(heap); 
}

void State::storeInMemory(int offset, Data value) {
    DataType dataType = value.getDataType(); 
    int size = 0; 

    switch (dataType) {
        case i32: 
        case u32: 
            size = 4; 
        break; 
    }

    if (offset + size > sizeof(heap)) {
        // throw error: memory out of bounds 
    }

    for (int i = 0; i < size; i++) {
        uint8_t bt = value.getDataVal()[i]; 
        int position = offset + i; 

        heap[position] = bt; 
    }
}

Data State::loadFromMemory(int offset, DataType dataType) {
    Data data(dataType); 
    int size = 0; 

    switch (dataType) {
        case i32:
        case u32:
            size = 4; 
            break; 
    }

    if (offset + size > sizeof(heap)) {
        // throw error: memory out of bounds 
    }

    for (int i = 0; i < size; i++) {
        int position = offset + i; 

        uint8_t bt = heap[position]; 
        data.setByte(i, bt);  
    }

    return data; 
}


