#pragma once 

#include <vector>

/**
 * @brief Instructions allowed by this WASM. 
 * @author Alice He 
 */
class Instruction {
    
}; 

/**
 * @brief Data types allowed by this WASM. 
 */
enum DataType {
    i32, 
    u32 
}; 

class Data {
    public: 
        Data(DataType dataType) {
            this->dataType = dataType; 

            switch(dataType) {
                case i32:
                    data.resize(4); 
                    break; 
                case u32:
                    data.resize(4); 
                    break; 
            }
        }

        DataType getDataType() {
            return dataType; 
        }

    private: 
        std::vector<u_int8_t> data; 
        DataType dataType; 
}; 
