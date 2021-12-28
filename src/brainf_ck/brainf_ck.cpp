// SPDX-License-Identifier: MIT
// Copyright 2021 Ricerca Security, Inc.

#include <cstdint>
#include <stack>
#include <vector>
#include <iterator>
#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#ifdef FUZZ_TOYS_STRICT_BRAINF_CK
#include <boost/container/flat_set.hpp>
#endif

class brainf_ck {
public:
  brainf_ck() : mem( 30000, 0 ), pointer( mem.data() ) {}
  void operator()( const std::vector< char > &range ) {
    auto pc = range.data();
    auto end = std::next( range.data(), range.size() );
#ifdef FUZZ_TOYS_STRICT_BRAINF_CK
    static const boost::container::flat_set< char > valid( { '>', '<', '+', '-', '.', ',', '[', ']', ' ', '\t', '\x0a', '\x0d' } );
    if( std::find_if( pc, end, [&]( char c ) { return valid.find( c ) == valid.end(); } ) != end )
      throw std::runtime_error( "不正な命令" );
#endif
    while( pc != end )
      pc = exec_instruction( pc, end );
  }
private:
  const char *exec_instruction( const char *at, const char *end ) {
    const char instruction = *at;
    if( instruction == '>' ) {
      if( size_t( std::distance( mem.data(), pointer ) + 1 ) == mem.size() ) {
        mem.resize( mem.size() + 1, 0 );
        pointer = std::next( mem.data(), mem.size() - 1 );
      }
      else pointer = std::next( pointer );
      return std::next( at );
    }
    else if( instruction == '<' ) {
      if( mem.data() == pointer ) throw std::out_of_range( "メモリの先頭を指すポインタがデクリメントされた" );
      pointer = std::prev( pointer );
      return std::next( at );
    }
    else if( instruction == '+' ) {
      ++*pointer;
      return std::next( at );
    }
    else if( instruction == '-' ) {
      --*pointer;
      return std::next( at );
    }
    else if( instruction == '.' ) {
      std::cout << *pointer;
      return std::next( at );
    }
    else if( instruction == ',' ) {
      throw std::out_of_range( "入力ストリームは利用できない" );
    }
    else if( instruction == '[' ) {
      if( *pointer == 0 ) return skip_block( std::next( at ), end );
      loop_head.push( std::next( at ) );
      return std::next( at );
    }
    else if( instruction == ']' ) {
      if( loop_head.empty() ) throw std::runtime_error( "]に対応する[が無い" );
      if( *pointer != 0 ) return loop_head.top();
      loop_head.pop();
      return std::next( at );
    }
    else if( instruction == ' ' ) return std::next( at );
    else if( instruction == '\t' ) return std::next( at );
    else if( instruction == '\x0a' ) return std::next( at );
    else if( instruction == '\x0d' ) return std::next( at );
    else throw std::runtime_error( "不正な命令" );
  }
  const char *skip_block( const char *at, const char *end ) {
    auto token = std::find_if( at, end, []( char c ) { return c == '[' || c == ']'; } );
    if( token == end ) {
#ifdef FUZZ_TOYS_STRICT_BRAINF_CK
      throw std::runtime_error( "[に対応する]が無い" );
#else
      return token;
#endif
    }
    if( *token == '[' ) return skip_block( skip_block( std::next( token ), end ), end );
    return std::next( token );
  }
  std::vector< std::uint8_t > mem;
  std::uint8_t *pointer;
  std::stack< const char* > loop_head;
};

int main() {
  std::vector< char > data(
    std::istreambuf_iterator< char >{ std::cin },
    std::istreambuf_iterator< char >{}
  );
  brainf_ck interpretor;
  interpretor( data );
}


