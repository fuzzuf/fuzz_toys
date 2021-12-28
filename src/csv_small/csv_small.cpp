// SPDX-License-Identifier: MIT
// Copyright 2021 Ricerca Security, Inc.

#include <cstdint>
#include <vector>
#include <iterator>
#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <tuple>

using csv_record_t = std::vector< std::string >;
using csv_t = std::vector< csv_record_t >;
struct invalid_csv : public std::runtime_error {
  using std::runtime_error::runtime_error;
};
const char *parse_blank(
  const char *begin, const char *end
) {
  return std::find_if( begin, end, []( const auto &c ) {
    return c != ' ' && c != '\t';
  } );
}
const char *parse_eol(
  const char *begin, const char *end
) {
  return std::find_if( begin, end, []( const auto &c ) {
    return c != '\x0d' && c != '\x0a';
  } );
}
std::tuple< const char *, std::string > parse_quoted_token( const char *begin, const char *end ) {
  auto meta = std::find_if( begin, end, []( const auto &c ) {
    return c == '"';
  } );
  if( meta == end ) throw invalid_csv( "\"が閉じられていない" );
  auto next = std::next( meta );
  if( next != end && *next == '"' ) {
    auto [last_quote,tail] = parse_quoted_token( std::next( next ), end );
    return std::make_tuple( last_quote, std::string( begin, meta ) + '"' + tail );
  }
  auto end_of_token = parse_blank( next, end );
  return std::make_tuple( end_of_token, std::string( begin, meta ) );
}
std::tuple< const char *, std::string > parse_token(
  const char *begin, const char *end
) {
  auto meta = std::find_if( begin, end, []( const auto &c ) {
    return c == ',' || c == '\x0d' || c == '\x0a' || c == '"';
  } );
  if( meta == end ) return std::make_tuple( meta, std::string( begin, meta ) );
  else if( *meta == '"' ) {
    auto non_blank = parse_blank( begin, meta );
    if( non_blank != meta ) throw invalid_csv( "\"の前に値がある" );
    return parse_quoted_token( std::next( meta ), end );
  }
  return std::make_tuple( meta, std::string( begin, meta ) );
}
std::tuple< const char *, csv_record_t > parse_record(
  const char *begin, const char *end
) {
  csv_record_t record;
  auto [head_end,head] = parse_token( begin, end );
  record.push_back( std::move( head ) );
  if( head_end == end ) return std::make_tuple( head_end, record );
  else if( *head_end == ',' ) {
    auto [tail_end,tail] = parse_record( std::next( head_end ), end );
    record.insert( record.end(), tail.begin(), tail.end() );
    return std::make_tuple( tail_end, record );
  }
  auto new_line = parse_eol( head_end, end );
  return std::make_tuple( new_line, record );
}
std::tuple< const char *, csv_t > parse_csv(
  const char *begin, const char *end
) {
  csv_t csv;
  auto [head_end,head] = parse_record( begin, end );
  csv.push_back( std::move( head ) );
  if( head_end == end ) return std::make_tuple( head_end, csv );
  auto [tail_end,tail] = parse_csv( head_end, end );
  csv.insert( csv.end(), tail.begin(), tail.end() );
  return std::make_tuple( tail_end, csv );
}
int main() {
  std::vector< char > data(
    std::istreambuf_iterator< char >{ std::cin },
    std::istreambuf_iterator< char >{}
  );
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
  auto [end,parsed] = parse_csv( data.data(), std::next( data.data(), data.size() ) );
#pragma GCC diagnostic pop
  std::cout << parsed.size() << "lines" << std::endl;
}

