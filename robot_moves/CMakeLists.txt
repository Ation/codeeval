cmake_minimum_required (VERSION 2.6)

project( robot_moves )

set( SOURCES
  direct_search.cpp
  )

set( HEADERS
  )

add_executable( robot_moves ${SOURCES} ${HEADERS} )
