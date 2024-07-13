#pragma once 

#include "Instruction.hpp"

/**
 * @brief Types of arithmetic operations allowed. 
 * 
 * Note: Div_s stands for signed division (as opposed to unsigned). 
 */
enum ArithOpType {
    Add, 
    Sub, 
    Mult, 
    Div_s 
}; 

/**
 * @brief Arithmetic instructions 
 * @author Alice He 
 * 
 * Arithmetic operation instructions allowable on my WASM simulation. 
 */
class ArithInstr : public Instruction {
    public: 
        /**
         * Constructor sets opType and dataType to given. 
         * @param opType is the type of ArithOpType defined below. 
         * @param dataType is the type of DataType defined in Instruction 
         * (parent) class. 
         */
        ArithInstr(ArithOpType opType, DataType dataType); 

        /** 
         * @return The opType of this object. 
         */
        ArithOpType getArithOpType(); 

        /**
         * @return The dataType of this object. 
         */
        DataType getDatatType(); 

    private: 
        ArithOpType opType; 
        DataType dataType; 
}; 

