#--------------------------------------------
# C++ language project template
#
# default folder structure as follows
# <project root folder>
#      cmake/   <- here the additional modules with handy macro and finders
#      include/
#      src/
#      test/
#--------------------------------------------
cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

set(PROJECT_NAME the-messanjah)

# define project for C++ language
project(${PROJECT_NAME})


# set where to find additional cmake modules if any
# comment it out if not required
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

option(WITH_UT "Build Unit Test" OFF)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

find_package(Threads)

find_package(Boost 1.58.0 REQUIRED
    COMPONENTS
        thread system chrono regex
        filesystem atomic program_options)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/cppzmq)
include_directories(${PROJECT_SOURCE_DIR}/include/boost.application/include)


set(HDR_FILES
    include/service.hpp
)
set(SRC_FILES
    src/main.cpp
)

source_group( "Header Files" FILES ${HDR_FILES} )
source_group( "Source Files" FILES ${SRC_FILES} )

# build target
add_executable( ${PROJECT_NAME}
   ${SRC_FILES} ${HDR_FILES} )

set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY COMPILE_DEFINITIONS "BOOST_APPLICATION_FEATURE_NS_SELECT_BOOST")
if( WIN32 )
    set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY COMPILE_DEFINITIONS "_WIN32_WINNT=_WIN32_WINNT_VISTA")
    set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY COMPILE_DEFINITIONS "BOOST_ALL_NO_LIB")
endif()

# linker command - add additional libraries for build target
target_link_libraries( ${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} )
target_link_libraries( ${PROJECT_NAME} ${Boost_LIBRARIES} )

set_property( TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11 )

if(WITH_UT)
    include(CTest)
    enable_testing()
    add_subdirectory(test)
endif()
