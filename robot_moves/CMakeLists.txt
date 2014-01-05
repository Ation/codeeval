cmake_minimum_required (VERSION 2.6)

project( robot_moves )

set( SOURCES
  direct_search.cpp
  )

set( TEMPLATE_SOURCES
	template_search.cpp
)

set( RECURSE_SOURCES
	recurse.cpp
)

add_executable( robot_moves ${SOURCES} )
add_executable( template_moves ${TEMPLATE_SOURCES} )
add_executable( recurse ${RECURSE_SOURCES} )
