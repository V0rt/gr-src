INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_SRC src)

FIND_PATH(
    SRC_INCLUDE_DIRS
    NAMES src/api.h
    HINTS $ENV{SRC_DIR}/include
        ${PC_SRC_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    SRC_LIBRARIES
    NAMES gnuradio-src
    HINTS $ENV{SRC_DIR}/lib
        ${PC_SRC_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SRC DEFAULT_MSG SRC_LIBRARIES SRC_INCLUDE_DIRS)
MARK_AS_ADVANCED(SRC_LIBRARIES SRC_INCLUDE_DIRS)

