#include "State.hpp"
#include "Instruction.hpp"

State::State() {

}

int State::size() {
    return sizeof(heap); 
}

void State::storeInMemory(int offset, int index, Data value) {
    DataType dataType = value.getDataType(); 

    switch (dataType) {
        case i32: 
        case u32: 
            for (int i = 0; i < 4; i++) {
                uint8_t bt = value.getDataVal()[i]; 
                int position = offset + index * 4 + i; 

                if (position < sizeof(heap)) {
                    heap[position] = bt; 
                } else {
                    // throw error: memory out of bound 
                }
            }
        break; 
    }
}

Data State::loadFromMemory(int offset, int index, DataType dataType) {
    Data data(dataType); 

    switch (dataType) {
        case i32:
        case u32:
            std::vector<uint8_t> dataVal; 
            for (int i = 0; i < 4; i++) {
                int position = offset + index * 4 + i; 

                if (position < sizeof(heap)) {
                    uint8_t bt = heap[position]; 
                    dataVal.push_back(bt);  
                } else {
                    // throw error: memory out of bound 
                } 
            }
            data.setDataVal(dataVal);
            break; 
    }

    return data; 
}

void State::pushToStack(Data value) {
    DataType dataType = value.getDataType(); 

    switch (dataType) {
        case i32: 
        case u32: 
            for (int i = 0; i < 4; i++) {
                uint8_t bt = value.getDataVal()[i]; 
                stk.push(bt); 
            }
        break; 
    }
}

Data State::getFromStack(DataType dataType) {
    Data data(dataType); 

    switch (dataType) {
        case i32:
        case u32:
            std::vector<uint8_t> dataVal; 
            for (int i = 0; i < 4; i++) {
                uint8_t bt = stk.top();
                stk.pop(); 
                dataVal.push_back(bt); 
            }
            data.setDataVal(dataVal);
            break; 
    }

    return data; 
}
