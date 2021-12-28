/*
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2018-2021 Naomasa Matsubayashi
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <cstdint>
#include <vector>
#include <iterator>
#include <iostream>
#include <string>
#include <algorithm>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/phoenix.hpp>

using csv_record_t = std::vector< std::string >;
using csv_t = std::vector< csv_record_t >;
namespace qi {
  template <typename InputIterator>
  class csv :
  public boost::spirit::qi::grammar< InputIterator, csv_t() > {
    public:
      csv() : csv::base_type( file ) {
        namespace qi = boost::spirit::qi;
        namespace phx = boost::phoenix;
        auto q = qi::lit( '"' );
        qq = ( q >> q )[ qi::_val = '"' ];
        file = record % qi::eol >> qi::omit[ -qi::eol ];
        record = field % ',';
        field = escaped | non_escaped;
        non_escaped = *( qi::char_ - qi::eol - ',' );
        escaped_text = *( qi::char_ - q | qq );
        escaped = qi::omit[ *qi::standard::blank >> q ] >> escaped_text >> qi::omit[ q >> *qi::standard::blank ];
      }
    private:
      boost::spirit::qi::rule< InputIterator, char() > qq;
      boost::spirit::qi::rule< InputIterator, csv_t() > file;
      boost::spirit::qi::rule< InputIterator, csv_record_t() > record;
      boost::spirit::qi::rule< InputIterator, std::string() > field;
      boost::spirit::qi::rule< InputIterator, std::string() > non_escaped;
      boost::spirit::qi::rule< InputIterator, std::string() > escaped;
      boost::spirit::qi::rule< InputIterator, std::string() > escaped_text;
  };
}
int main() {
  std::vector< char > data(
    std::istreambuf_iterator< char >{ std::cin },
    std::istreambuf_iterator< char >{}
  );
  csv_t parsed;
  {
    const qi::csv< std::vector< char >::const_iterator > rule;
    auto iter = data.cbegin();
    if( !boost::spirit::qi::parse( iter, data.cend(), rule, parsed ) )
      return 1;
  }
  std::cout << parsed.size() << "lines" << std::endl;
}

