# Copyright 2011,2012,2016 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

list(APPEND src_sources
    signal_src_impl.cc
)

set(src_sources "${src_sources}" PARENT_SCOPE)
if(NOT src_sources)
	MESSAGE(STATUS "No C++ sources... skipping lib/")
	return()
endif(NOT src_sources)

add_library(gnuradio-src SHARED ${src_sources})
target_link_libraries(gnuradio-src ${Boost_LIBRARIES} ${GNURADIO_ALL_LIBRARIES})
set_target_properties(gnuradio-src PROPERTIES DEFINE_SYMBOL "gnuradio_src_EXPORTS")

if(APPLE)
    set_target_properties(gnuradio-src PROPERTIES
        INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    )
endif(APPLE)

########################################################################
# Install built library files
########################################################################
include(GrMiscUtils)
GR_LIBRARY_FOO(gnuradio-src RUNTIME_COMPONENT "src_runtime" DEVEL_COMPONENT "src_devel")

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

include_directories(${CPPUNIT_INCLUDE_DIRS})

list(APPEND test_src_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test_src.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_src.cc
)

add_executable(test-src ${test_src_sources})

target_link_libraries(
  test-src
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CPPUNIT_LIBRARIES}
  gnuradio-src
)

GR_ADD_TEST(test_src test-src)

########################################################################
# Print summary
########################################################################
message(STATUS "Using install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Building for version: ${VERSION} / ${LIBVER}")

