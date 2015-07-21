cmake_minimum_required (VERSION 2.6)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
project( cleanup_words )

set( SOURCES
  main.cpp
  )

set( HEADERS
  )

add_executable( cleanup_words ${SOURCES} ${HEADERS} )