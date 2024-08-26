#pragma once 

#include <iostream>
#include <vector> 
#include <expected>

namespace instr { 
/**
 * @brief Data types allowed by this WASM. 
 */
enum DataType {
    i32, 
    u32 
}; 

/**
 * InvalidDataError: given data is invalid. For example, the instruction 'i32.const a'
 * would cause this error since 'a' is not a valid data. 
 * 
 * DataSizeMismatchError: occurs when two given Data have a size mismatch. 
 * 
 * DataTypeMismatchError: occurs when two given DataTypes do not match. 
 */
enum class DataError {
    InvalidDataError, 
    DataSizeMismatchError, 
    DataTypeMismatchError
}; 

class Data {
    public: 
        Data() = default;
        Data(DataType dataType) {
            this->dataType = dataType; 

            switch(dataType) {
                case i32: 
                    dataVal.resize(4, 0); 
                    setDataVal<int32_t>(0); 
                    break; 
                case u32:
                    dataVal.resize(4, 0); 
                    setDataVal<uint32_t>(0);
                    break; 
            }
        }

        DataType getDataType() const {
            return dataType; 
        }

        template <typename T>
        void setDataVal(T val) {
            dataVal.clear();
            using UnsignedT = typename std::make_unsigned<T>::type; 
            UnsignedT unsignedVal = static_cast<UnsignedT>(val);
            for (size_t i = 0; i < sizeof(T); i++) {
                uint8_t byte = (unsignedVal >> (i * 8)) & 0xFF; 

                dataVal.push_back(byte);
            }
        }

        void setDataVal(std::vector<uint8_t> dataVal) {

            this->dataVal = dataVal; 
        }

        std::vector<uint8_t> getDataVal() {

            return dataVal; 
        }

        template <typename T> 
        std::expected<T, DataError> interpretData() {
            if (dataVal.size() != sizeof(T)) {
                return std::unexpected(DataError::InvalidDataError);
            }

            T value = 0; 
            for (size_t i = 0; i < sizeof(T); i++) {
                value |= (static_cast<T>(dataVal[i]) << (i * 8)); 
            }

            return value; 
        }

        void setByte(int i, uint8_t byte) {
            dataVal[i] = byte; 
        }

        /**
         * @return true if data1 and data2 are the same size, return DataSizeMismatchError 
         * otherwise. 
         * 
         * Note that i32 and u32 are the same size, as they are both 32 bits. Hence expecting true.
         */
        static std::expected<bool, DataError> isSameDataSize(Data data1, Data data2) {
            DataType dataType1 = data1.getDataType(); 
            DataType dataType2 = data2.getDataType(); 

            // add checks for non equal data sizes
            // return std::unexpected(DataError::DataSizeMismatchError); 

            return true; 
        }

        /**
         * @return true if dataType1 and dataType2 are the same type, return DataTypeMismatchError
         * otherwise. 
         * 
         * Note that i32 and u32 are not the same type. Hence expecting DataTypeMismatchError. 
         */
        static std::expected<bool, DataError> isSameDataType(DataType dataType1, DataType dataType2) {
            if (dataType1 == dataType2) {
                return true; 
            }

            return std::unexpected(DataError::DataTypeMismatchError); 
        }



    // private: 
        std::vector<uint8_t> dataVal; 
        DataType dataType; 
}; 


}
