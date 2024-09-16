#include "Interpreter.hpp"
#include "State.hpp"
#include "Instruction.hpp"
#include <expected>
#include <iostream>
#include <variant> 
#include <vector> 
#include "Data.hpp"
#include <cassert>

Interpreter::Interpreter() {
    Context context; 
    state.contexts.push(context); 

    assert(!state.contexts.empty()); 
}

template <typename T>
T Interpreter::getValidData(Data& data) {
    auto result = data.interpretData<T>(); 
    T value; 
    if (result.error() == DataError::InvalidDataError) {
        std::cerr << "Invalid data error. " << std::endl; 
    } else if (result.has_value()) {
        value = result.value(); 
    } 
    return value; 
}

void Interpreter::interpret(Instruction& instruction) {
    assert(!state.contexts.empty()); 

    Context& curr = state.contexts.top();

    std::visit([&](auto&& arg){ interpret(arg, curr); }, instruction); 
}

void Interpreter::interpret(ConstInstr& instruction, Context& context) { 
    context.stack.push(instruction.getData()); 
}

void Interpreter::interpret(ArithInstr& instruction, Context& context) {

    ArithOpType opType = instruction.getArithOpType(); 
    DataType dataType = instruction.getDatatType(); 

    // get 2 numbers from top of stack 
    Data data2 = context.stack.top(); 
    context.stack.pop(); 
    Data data1 = context.stack.top();
    context.stack.pop(); 
    
    /* CHECK IF CORRECT DATA TYPE AS INSTR 
    auto isSameSize = Data::isSameDataSize(data1, data2); 

    if (!isSameSize.has_value() && isSameSize.error() == DataError::DataSizeMismatchError) {
        std::cerr << "Data size mismatch error. " << std::endl;
    }
    */ 

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

    context.stack.push(result); 
}

void Interpreter::interpret(SizeInstr& instruction, Context& context) {
    Data sizeData(u32);
    sizeData.setDataVal(state.size()); 
    context.stack.push(sizeData); 
}

void Interpreter::interpret(LoadInstr& instruction, Context& context) {
    Data dataOffset = context.stack.top(); 
    context.stack.pop(); 
    int offset = getValidData<int>(dataOffset); 
    
    Data valueInMemory = state.loadFromMemory(offset, instruction.getDataType()); 
    context.stack.push(valueInMemory); 
}

void Interpreter::interpret(StoreInstr& instruction, Context& context) {
    Data dataVal = context.stack.top(); 
    context.stack.pop(); 
    Data dataOffset = context.stack.top(); 
    context.stack.pop(); 
    int offset = getValidData<int>(dataOffset); 

    auto isSameType = Data::isSameDataSize(instruction.getDataType(), dataVal.getDataType()); 

    if (!isSameType.has_value() && isSameType.error() == DataError::DataTypeMismatchError) {
        std::cerr << "Data type mismatch error. " << std::endl;
    }

    state.storeInMemory(offset, dataVal); 
}

void Interpreter::interpret(CallInstr& instruction, Context& context) {

    if (instruction.identifier == "log") {
        Data top = context.stack.top(); 
        int topValue = getValidData<int>(top); 
        std::cout << topValue << std::endl; 
        return; 
    } 

    // create new context 

    Context newContext; 

    // number of params the function takes in 
    Function& newFunc = functionTable.at(instruction.identifier); 
    int numParams = newFunc.params.size(); 
    for (int i = numParams - 1; i >= 0; i--) {
        std::string paramName = newFunc.params[i].ident; 
        instr::DataType paramType = newFunc.params[i].dataType; 

        // type check 
        if (paramType != context.stack.top().dataType) {
            // Type Error 
        }

        newContext.params[paramName] = context.stack.top(); 
        context.stack.pop(); 
    }

    state.contexts.push(newContext); 

    // execute function call 
    Context& currContext = state.contexts.top(); 

    for (Instruction instr : newFunc.instructions) {
        interpret(instr); 
    }

    // handle return 
    bool hasReturnVal = newFunc.returnType.has_value(); 
    int contextStackSize = currContext.stack.size(); 

    if (hasReturnVal) {
        if (contextStackSize != 1) {
            // Error: incorrect stack size 
        }
        // put return val on prev context's stack and remove curr context 
        instr::Data returnVal = currContext.stack.top(); 
        state.contexts.pop(); 
        state.contexts.top().stack.push(returnVal); 
    } else {
        if (contextStackSize != 0) {
            // Error: incorrect stack size 
        }
    }
    
}
