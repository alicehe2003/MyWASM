#include "Interpreter.hpp"
#include "State.hpp"
#include "Instruction.hpp"
#include <expected>
#include <iostream>
#include <variant> 
#include <vector> 
#include "Data.hpp"

Interpreter::Interpreter(State state) {
    this->state = state; 
}

template <typename T>
T Interpreter::getValidData(Data& data) {
    auto result = data.interpretData<T>(); 
    T value; 
    if (result.error() == DataError::InvalidDataError) {
        std::cerr << "Invalid data error" << std::endl; 
    }
    if (result.has_value()) {
        value = result.value(); 
    } 
    return value; 
}

void Interpreter::interpret(Instruction& instruction) {
    std::visit([&](auto&& arg){ interpret(arg); }, instruction); 
}

void Interpreter::interpret(ConstInstr& instruction) { 
    state.pushToStack(instruction.getData()); 
}

void Interpreter::interpret(ArithInstr& instruction) {

    ArithOpType opType = instruction.getArithOpType(); 
    DataType dataType = instruction.getDatatType(); 

    // get 2 numbers from top of stack 
    Data data2 = state.getFromStack(); 
    Data data1 = state.getFromStack(); 
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
                    value1 = getValidData<int32_t>(data1); 
                    value2 = getValidData<int32_t>(data2); 
                    result.setDataVal(value1 + value2); 
                    break; 
                }
                case u32: {
                    value1 = getValidData<uint32_t>(data1); 
                    value2 = getValidData<uint32_t>(data2); 
                    result.setDataVal(value1 + value2); 
                    break; 
                }
            }
            break; 
        case Sub: 
            switch(data1.getDataType()) {
                case i32: {
                    value1 = getValidData<int32_t>(data1); 
                    value2 = getValidData<int32_t>(data2); 
                    result.setDataVal(value1 - value2); 
                    break; 
                }
                case u32: {
                    value1 = getValidData<uint32_t>(data1); 
                    value2 = getValidData<uint32_t>(data2); 
                    result.setDataVal(value1 - value2); 
                    break; 
                }
            }
            break; 
        case Mult: 
            switch(data1.getDataType()) {
                case i32: {
                    value1 = getValidData<int32_t>(data1); 
                    value2 = getValidData<int32_t>(data2); 
                    result.setDataVal(value1 * value2); 
                    break; 
                }
                case u32: {
                    value1 = getValidData<uint32_t>(data1); 
                    value2 = getValidData<uint32_t>(data2); 
                    result.setDataVal(value1 * value2); 
                    break; 
                }
            }
            break; 
        case Div_s:
            switch(data1.getDataType()) {
                case i32: {
                    value1 = getValidData<int32_t>(data1); 
                    value2 = getValidData<int32_t>(data2); 
                    result.setDataVal(value1 / value2); 
                    break; 
                }
                case u32: {
                    value1 = getValidData<uint32_t>(data1); 
                    value2 = getValidData<uint32_t>(data2); 
                    result.setDataVal(value1 / value2); 
                    break; 
                }
            }
            break; 
    }

    state.pushToStack(result); 
}

void Interpreter::interpret(SizeInstr& instruction) {
    Data sizeData(u32);
    sizeData.setDataVal(state.size()); 
    state.pushToStack(sizeData);  
}

void Interpreter::interpret(LoadInstr& instruction) {
    Data dataOffset = state.getFromStack(); 
    int offset = getValidData<int>(dataOffset); 
    
    Data valueInMemory = state.loadFromMemory(offset, instruction.getIndex(), instruction.getDataType()); 
    state.pushToStack(valueInMemory); 
}

void Interpreter::interpret(StoreInstr& instruction) {
    Data dataVal = state.getFromStack(); 
    Data dataOffset = state.getFromStack(); 
    int offset = getValidData<int>(dataOffset); 
    
    DataType instructionDataType = instruction.getDataType(); 
    if (instructionDataType != dataVal.getDataType()) {
        // throw error: data type mismatch
    }

    state.storeInMemory(offset, instruction.getIndex(), dataVal); 
}

void Interpreter::interpret(CallInstr& instruction) {
    Data top = state.topOfStack(); 
    int topValue = getValidData<int>(top); 

    std::cout << topValue << std::endl; 
}
