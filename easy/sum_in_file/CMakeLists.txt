cmake_minimum_required (VERSION 2.6)

project( sum_in_file )

set( SOURCES
  main.c
  )

set( HEADERS
  )

add_executable( sum_in_file ${SOURCES} ${HEADERS} )
