#ifndef PARSER_HPP_
#define PARSER_HPP_

#include "Instruction.hpp"
#include <expected>
#include <variant> 

#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator.hpp>
#include <boost/phoenix/object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

class Parser {
    public: 
        Parser(); 
        
        /**
         * Parses instruction input and returns Instruction object.
         * 
         * @param str is the given instruction in string format. 
         * 
         * @return The correct Instruction object representation of str. 
         */
      std::expected<instr::Instruction, std::variant<instr::DataError, instr::CallError, instr::InstructionError>> parse(const std::string& str); 
}; 

namespace qi = boost::spirit::qi;

struct DataType_ : qi::symbols<char, instr::DataType> {
  DataType_() {
    add
        ("i32", instr::DataType::i32) 
        ("u32", instr::DataType::u32); 
  }
}; 
extern DataType_ DataTypeParser;

struct ArithOpType_ : qi::symbols<char, instr::ArithOpType> {
  ArithOpType_() {
    add 
        ("add", instr::ArithOpType::Add)
        ("sub", instr::ArithOpType::Sub)
        ("mul", instr::ArithOpType::Mult)
        ("div_s", instr::ArithOpType::Div_s); 
  }
}; 
extern ArithOpType_ ArithOpTypeParser;

BOOST_FUSION_ADAPT_STRUCT(
  instr::ArithInstr, 
  (instr::DataType, dataType)
  (instr::ArithOpType, opType)
)

namespace ascii = boost::spirit::ascii;
template <typename Iterator>
struct ArithInstrParser : qi::grammar<Iterator, instr::ArithInstr(), ascii::space_type> {
  ArithInstrParser() : ArithInstrParser::base_type(start) {
    using qi::lexeme;
    using boost::spirit::eps;

    start %= 
            lexeme[
              DataTypeParser
              >> '.'
              >> ArithOpTypeParser
            ]
          ;
  }

  qi::rule<Iterator, instr::DataType(), ascii::space_type> data_type;
  qi::rule<Iterator, instr::ArithOpType(), ascii::space_type> arith_op_type;
  qi::rule<Iterator, instr::ArithInstr(), ascii::space_type> start;
}; 


#endif // PARSER_HPP_
