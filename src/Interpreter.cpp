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

template <typename T> 
T Interpreter::interpretData(Data& data) {
    if (data.getDataVal().size() != sizeof(T)) {
        // throw error: data type mismatch 
    }

    T value = 0; 
    for (size_t i = 0; i < sizeof(T); i++) {
        value |= (static_cast<T>(data.getDataVal()[i]) << (i * 8)); 
    }

    return value; 
}

void Interpreter::interpretConst(ConstInstr instruction) {
    state->pushToStack(instruction.getData()); 
}

void Interpreter::interpretArith(ArithInstr instruction) {
    ArithOpType opType = instruction.getArithOpType(); 
    DataType dataType = instruction.getDatatType(); 

    // get 2 numbers from top of stack 
    Data data2 = state->getFromStack(); 
    Data data1 = state->getFromStack(); 
    if (data1.getDataType() != data2.getDataType()) {
        // throw error: data type mismatch 
    }

    Data result(dataType); 

    int32_t value1; 
    int32_t value2; 

    switch (opType) {
        case Add:
            switch(data1.getDataType()) {
                case i32: {
                    value1 = interpretData<int32_t>(data1); 
                    value2 = interpretData<int32_t>(data2); 
                    result.setDataVal(value1 + value2); 
                    break; 
                }
                case u32: {
                    value1 = interpretData<uint32_t>(data1); 
                    value2 = interpretData<uint32_t>(data2); 
                    result.setDataVal(value1 + value2); 
                    break; 
                }
            }
            break; 
        case Sub: 
            switch(data1.getDataType()) {
                case i32: {
                    value1 = interpretData<int32_t>(data1); 
                    value2 = interpretData<int32_t>(data2); 
                    result.setDataVal(value1 - value2); 
                    break; 
                }
                case u32: {
                    value1 = interpretData<uint32_t>(data1); 
                    value2 = interpretData<uint32_t>(data2); 
                    result.setDataVal(value1 - value2); 
                    break; 
                }
            }
            break; 
        case Mult: 
            switch(data1.getDataType()) {
                case i32: {
                    value1 = interpretData<int32_t>(data1); 
                    value2 = interpretData<int32_t>(data2); 
                    result.setDataVal(value1 * value2); 
                    break; 
                }
                case u32: {
                    value1 = interpretData<uint32_t>(data1); 
                    value2 = interpretData<uint32_t>(data2); 
                    result.setDataVal(value1 * value2); 
                    break; 
                }
            }
            break; 
        case Div_s:
            switch(data1.getDataType()) {
                case i32: {
                    value1 = interpretData<int32_t>(data1); 
                    value2 = interpretData<int32_t>(data2); 
                    result.setDataVal(value1 / value2); 
                    break; 
                }
                case u32: {
                    value1 = interpretData<uint32_t>(data1); 
                    value2 = interpretData<uint32_t>(data2); 
                    result.setDataVal(value1 / value2); 
                    break; 
                }
            }
            break; 
    }

    state->pushToStack(result); 
}

void Interpreter::interpretSize(SizeInstr instruction) {

}

void Interpreter::interpretLoad(LoadInstr instruction) {

}

void Interpreter::interpretStore(StoreInstr instruction) {

}
