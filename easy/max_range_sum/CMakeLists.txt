cmake_minimum_required (VERSION 2.6)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
project( max_sum )

set( SOURCES
  main.cpp
  )

set( HEADERS
  )

add_executable( max_sum ${SOURCES} ${HEADERS} )