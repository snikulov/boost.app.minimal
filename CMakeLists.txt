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
project(the-messanjah)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED yes)

# set where to find additional cmake modules if any
# comment it out if not required
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

option(WITH_UT  "Build Unit Test" OFF)
option(WITH_STD "Build with std:: namespace" ON)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

find_package(Threads)
#find_package(ZMQ REQUIRED)

# we will use static libs
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.58.0 REQUIRED
    COMPONENTS
        thread system chrono regex
        filesystem atomic program_options)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

#include_directories(${ZMQ_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)
#include_directories(${PROJECT_SOURCE_DIR}/include/cppzmq)
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

if(WITH_STD)
    set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY COMPILE_DEFINITIONS "BOOST_APPLICATION_FEATURE_NS_SELECT_STD")
else()
    set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY COMPILE_DEFINITIONS "BOOST_APPLICATION_FEATURE_NS_SELECT_BOOST;BOOST_THREAD_PROVIDES_THREAD_DESTRUCTOR_CALLS_TERMINATE_IF_JOINABLE")
endif()

if( WIN32 )
    set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY COMPILE_DEFINITIONS "_WIN32_WINNT=_WIN32_WINNT_VISTA")
    set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY COMPILE_DEFINITIONS "BOOST_ALL_NO_LIB")
endif()

# linker command - add additional libraries for build target
target_link_libraries( ${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} )
target_link_libraries( ${PROJECT_NAME} ${Boost_LIBRARIES} )
target_link_libraries( ${PROJECT_NAME} ${ZMQ_LIBRARY} )

set_property( TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11 )

if(WITH_UT)
    include(CTest)
    enable_testing()
    add_subdirectory(test)
endif()
