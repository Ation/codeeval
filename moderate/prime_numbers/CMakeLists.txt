cmake_minimum_required (VERSION 2.6)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
project( p_n )

set( SOURCES
  main.cpp
  )

set( HEADERS
  )

add_executable( p_n ${SOURCES} ${HEADERS} )