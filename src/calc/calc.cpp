// SPDX-License-Identifier: MIT
// Copyright 2021 Ricerca Security, Inc.

#include <cstdint>
#include <vector>
#include <iterator>
#include <iostream>
#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix.hpp>

namespace qi {
  template <typename InputIterator>
  class calc : public boost::spirit::qi::grammar< InputIterator, int() > {
    enum class op_t {
      add,
      sub,
      mul,
      div,
      mod
    };
    public:
      calc() : calc::base_type( l2 ) {
        namespace qi = boost::spirit::qi;
        namespace phx = boost::phoenix;
        l0 = qi::skip( qi::standard::space )[
          ( '(' >> l2 >> ')' ) | qi::int_
        ];
        l1oper.add
          ( "*", op_t::mul )
          ( "/", op_t::div )
          ( "%", op_t::mod );
        l2oper.add
          ( "+", op_t::add )
          ( "-", op_t::sub );
        l1 = qi::skip( qi::standard::space )[
          ( l0 >> *( l1oper >> l0 ) )[ qi::_pass = phx::bind( &calc::calculate, qi::_val, qi::_1, qi::_2 ) ]
        ];
        l2 = qi::skip( qi::standard::space )[
          ( l1 >> *( l2oper >> l1 ) )[ qi::_pass = phx::bind( &calc::calculate, qi::_val, qi::_1, qi::_2 ) ]
        ];
      }
    private:
      static bool calculate( int &dest, int head, const std::vector< boost::fusion::vector< op_t, int > > &tail ) {
        dest = head;
        for( const auto &v: tail ) {
          const auto op = boost::fusion::at_c< 0 >( v );
          const auto right = boost::fusion::at_c< 1 >( v );
          if( op == op_t::add ) dest += right;
          else if( op == op_t::sub ) dest -= right;
          else if( op == op_t::mul ) dest *= right;
          else if( op == op_t::div ) dest /= right;
          else if( op == op_t::mod ) dest %= right;
        }
        return true;
      }
      boost::spirit::qi::symbols< char, op_t > l1oper;
      boost::spirit::qi::symbols< char, op_t > l2oper;
      boost::spirit::qi::rule< InputIterator, int() > l0;
      boost::spirit::qi::rule< InputIterator, int() > l1;
      boost::spirit::qi::rule< InputIterator, int() > l2;
  };
}
int main() {
  std::vector< char > data(
    std::istreambuf_iterator< char >{ std::cin },
    std::istreambuf_iterator< char >{}
  );
  int parsed;
  {
    const qi::calc< std::vector< char >::const_iterator > rule;
    auto iter = data.cbegin();
    if( !boost::spirit::qi::parse( iter, data.cend(), rule, parsed ) )
      return 1;
  }
  std::cout << parsed << std::flush;
}

