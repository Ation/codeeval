cmake_minimum_required (VERSION 2.6)

project( lowercase )

set( SOURCES
  main.c
  )

set( HEADERS
  )

add_executable( lowercase ${SOURCES} ${HEADERS} )
