#ifndef PARSER_HPP_
#define PARSER_HPP_

#include "Instruction.hpp"
#include "Function.hpp"
#include <expected>
#include <variant> 
#include <tuple>

#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator.hpp>
#include <boost/phoenix/object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/phoenix/fusion.hpp>
#include <boost/spirit/include/support_istream_iterator.hpp>

/**
 * Parser errors
 */
enum class ParserError {
    InstructionParseError
}; 

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
      std::expected<instr::Instruction, std::variant<instr::DataError, instr::CallError, instr::InstructionError, ParserError>> parse(const std::string& str); 
      
}; 

namespace qi = boost::spirit::qi;

/** 
 * DataType parser 
 */

struct DataType_ : qi::symbols<char, instr::DataType> {
  DataType_() {
    add
        ("i32", instr::DataType::i32) 
        ("u32", instr::DataType::u32); 
  }
}; 
extern DataType_ DataTypeParser;

/**
 * ArithOpType parser 
 */

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

/**
 * AirthInstr parser 
 */

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

    start %= lexeme[
              DataTypeParser
              >> '.'
              >> ArithOpTypeParser
    ];
  }

  qi::rule<Iterator, instr::ArithInstr(), ascii::space_type> start;
}; 

/**
 * ConstInstr parser 
 */

BOOST_FUSION_ADAPT_STRUCT(
  instr::ConstInstr, 
  (instr::Data, data)
)

template <typename Iterator> 
struct ConstInstrParser : qi::grammar<Iterator, instr::ConstInstr(), ascii::space_type, qi::locals<instr::DataType>> {
  ConstInstrParser() : ConstInstrParser::base_type(start) {
    using qi::lexeme; 
    using qi::int_; 
    using qi::uint_; 
    using qi::_1; 
    using qi::_val; 
    using qi::lit; 
    using qi::_a; 
    using namespace qi::labels; 
    using boost::phoenix::at_c;
    
    start %= lexeme[
      DataTypeParser[_a = _1] >> ".const "  >> 
      ( (qi::eps(_a == instr::DataType::i32) >> int_[at_c<0>(_val) = boost::phoenix::construct<instr::Data>(_a, _1)])
      | (qi::eps(_a == instr::DataType::u32) >> uint_[at_c<0>(_val) = boost::phoenix::construct<instr::Data>(_a, _1)])
      )
    ]; 
  }

  qi::rule<Iterator, instr::ConstInstr(), ascii::space_type, qi::locals<instr::DataType>> start;
}; 

/**
 * SizeInstr parser 
 */

template <typename Iterator>
struct SizeInstrParser : qi::grammar<Iterator, SizeInstr(), ascii::space_type> {
    SizeInstrParser() : SizeInstrParser::base_type(start) {
        using qi::lit;
        using qi::_val; 

        start %= lit("memory.size")[_val = _val];
    }

    qi::rule<Iterator, SizeInstr(), ascii::space_type> start;
};

/**
 * LoadInstr parser 
 */

BOOST_FUSION_ADAPT_STRUCT(
  instr::LoadInstr, 
  (int, index),
  (instr::DataType, dataType)
)

template <typename Iterator>
struct LoadInstrParser : qi::grammar<Iterator, instr::LoadInstr(), ascii::space_type> {
  LoadInstrParser() : LoadInstrParser::base_type(start) {
    using qi::lexeme;

    start %= lexeme[
              DataTypeParser
              >> ".load"
    ];
  }

  qi::rule<Iterator, instr::LoadInstr(), ascii::space_type> start;
}; 

/**
 * StoreInstr parser 
 */

BOOST_FUSION_ADAPT_STRUCT(
  instr::StoreInstr, 
  (int, index),
  (instr::DataType, dataType)
)

template <typename Iterator>
struct StoreInstrParser : qi::grammar<Iterator, instr::StoreInstr(), ascii::space_type> {
  StoreInstrParser() : StoreInstrParser::base_type(start) {
    using qi::lexeme;

    start %= lexeme[
              DataTypeParser
              >> ".store"
    ];
  }

  qi::rule<Iterator, instr::StoreInstr(), ascii::space_type> start;
}; 


/**
 * Call instruction parser
 * call $log 
 */
BOOST_FUSION_ADAPT_STRUCT(
  instr::CallInstr, 
  (instr::ident, identifier)
)

template <typename Iterator>
struct CallInstrParser : qi::grammar<Iterator, instr::CallInstr(), ascii::space_type> {
  CallInstrParser() : CallInstrParser::base_type(start) {
        using qi::lit;
        using qi::_val; 
        using qi::lexeme; 
        using qi::char_; 
        using boost::phoenix::construct; 
        using qi::_1; 

        ident = lexeme["$" >> +(char_("a-zA-Z_")) [_val += _1]]; 

        start %= lit("call")
                  >> ident 
                  [_val = boost::phoenix::construct<instr::CallInstr>(_1)];
    }

    qi::rule<Iterator, instr::CallInstr(), ascii::space_type> start;
    qi::rule<Iterator, std::string(), ascii::space_type> ident; 
}; 

/**
 * Function parser 
 * 
 * Parses given string into function object and places into function table. 
 */

BOOST_FUSION_ADAPT_STRUCT(
  Function, 
  (std::string, name), 
  (std::optional<instr::DataType>, returnType), 
  (std::vector<Param>, params),
  (std::vector<instr::Instruction>, instructions)
)

template <typename Iterator>
struct FunctionParser : qi::grammar<Iterator, void(), ascii::space_type> {
  FunctionParser() : FunctionParser::base_type(start) {
    using qi::lit;
    using qi::_val; 
    using qi::lexeme; 
    using qi::char_; 
    using boost::phoenix::construct; 
    using qi::_1; 
    using qi::_a; 

    ident = lexeme["$" >> +(char_("a-zA-Z_")) [_val += _1]]; 

    /*
    param = "("
      >> lit("param")
      >> ident[_a = _1]
      >> DataTypeParser[_val = std::make_tuple(_a, _1)]
      >> ")"; 
    */ 

    start %= "(" 
      >> lit("func")
      >> ident 
      >> ")"; 

  }

  qi::rule<Iterator, void(), ascii::space_type> start;
  qi::rule<Iterator, std::string(), ascii::space_type> ident; 
  // qi::rule<Iterator, Function::Param(), ascii::space_type> param;
}; 





/**
 * Instruction parser 
 */

template <typename Iterator>
struct InstructionParser : qi::grammar<Iterator, instr::Instruction(), ascii::space_type> {
  InstructionParser() : InstructionParser::base_type(start) {
    start = arithInstrParser 
          | constInstrParser
          | sizeInstrParser 
          | loadInstrParser 
          | storeInstrParser
          | callInstrParser; 
  }

  // instruction parsers 
  ArithInstrParser<Iterator> arithInstrParser; 
  ConstInstrParser<Iterator> constInstrParser; 
  SizeInstrParser<Iterator> sizeInstrParser; 
  LoadInstrParser<Iterator> loadInstrParser; 
  StoreInstrParser<Iterator> storeInstrParser; 
  CallInstrParser<Iterator> callInstrParser; 

  qi::rule<Iterator, instr::Instruction(), ascii::space_type> start; 
}; 

#endif // PARSER_HPP_
