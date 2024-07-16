#pragma once 

#include <vector>
#include <expected>

#include <iostream> 

/**
 * @brief Instructions allowed by this WASM. 
 * @author Alice He 
 */
class Instruction {
    public: 
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
                    std::cout<< "Data type: i32" << std::endl; 
                    dataVal.resize(4); 
                    break; 
                case u32:
                    std::cout<< "Data type: u32" << std::endl; 
                    dataVal.resize(4); 
                    break; 
            }
        }

        DataType getDataType() {
            std::cout<< "Data type: " << dataType << std::endl; 
            return dataType; 
        }

        template <typename T>
        void setDataVal(T val) {
            dataVal.clear();
            for (size_t i = 0; i < sizeof(T); i++) {
                uint8_t byte = (val >> (i * 8)) & 0xFF; 

                std::cout<< "Bytes of data: " << byte; 

                dataVal.push_back(byte);
            }
        }

        void setDataVal(std::vector<uint8_t> dataVal) {
            
            for (uint8_t d : dataVal) {
                std::cout<< "Bytes of data: " << d; 
            }

            this->dataVal = dataVal; 
        }

        std::vector<uint8_t> getDataVal() {

            for (uint8_t d : dataVal) {
                std::cout<< "Bytes of data: " << d; 
            }

            return dataVal; 
        }

    private: 
        std::vector<uint8_t> dataVal; 
        DataType dataType; 
}; 

enum class DataError {
    InvalidDataError
}; 

