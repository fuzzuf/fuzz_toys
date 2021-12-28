// SPDX-License-Identifier: MIT
// Copyright 2021 Ricerca Security, Inc.

#include <vector>
#include <iterator>
#include <iostream>
#include <string>

void encode_char( std::string &dest, char c ) {
  if( c == ':' ) dest += "%3A";
  else if( c == '/' ) dest += "%2F";
  else if( c == '?' ) dest += "%3F";
  else if( c == '#' ) dest += "%23";
  else if( c == '[' ) dest += "%5B";
  else if( c == ']' ) dest += "%5D";
  else if( c == '@' ) dest += "%40";
  else if( c == '!' ) dest += "%21";
  else if( c == '$' ) dest += "%24";
  else if( c == '&' ) dest += "%26";
  else if( c == '\'' ) dest += "%27";
  else if( c == '(' ) dest += "%28";
  else if( c == ')' ) dest += "%29";
  else if( c == '*' ) dest += "%2A";
  else if( c == '+' ) dest += "%2B";
  else if( c == ',' ) dest += "%2C";
  else if( c == ';' ) dest += "%3B";
  else if( c == '=' ) dest += "%3D";
  else if( c == '%' ) dest += "%25";
  else if( c == ' ' ) dest += "%20";
  else dest += c;
}
template< typename Range >
std::string encode_percent_encoding( const Range &range ) {
  std::string encoded;
  for( auto c: range )
    encode_char( encoded, c );
  return encoded;
}

int main() {
  std::vector< char > data(
    std::istreambuf_iterator< char >{ std::cin },
    std::istreambuf_iterator< char >{}
  );
  std::cout << encode_percent_encoding( data );
}


