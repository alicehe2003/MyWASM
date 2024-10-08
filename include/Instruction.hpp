#pragma once 

#include <vector>
#include <expected>
#include <iostream> 
#include <variant>
#include "ArithInstr.hpp"
#include "ConstInstr.hpp"
#include "LoadInstr.hpp"
#include "SizeInstr.hpp"
#include "StoreInstr.hpp"
#include "CallInstr.hpp"
#include "LocalInstr.hpp"

namespace instr {
/**
 * @brief Instructions allowed by this WASM. 
 * @author Alice He 
 */
enum class InstructionError {
    InvalidOpCodeError 
}; 

using Instruction = std::variant<ArithInstr, ConstInstr, LoadInstr, SizeInstr, StoreInstr, CallInstr, LocalInstr>; 
}
