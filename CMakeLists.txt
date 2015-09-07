#--------------------------------------------
# C++ language project template
#
# default folder structure as follows
# <project root folder>
#      cmake/   <- here the additional modules with handy macro and finders
#      include/
#      src/
#      test/
#
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

find_package(Boost 1.58.0 EXACT REQUIRED
    COMPONENTS
        thread system date_time chrono regex
        filesystem atomic program_options unit_test_framework)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

include_directories(${PROJECT_SOURCE_DIR}/include)

set(HDR_FILES
)
set(SRC_FILES
    src/main.cpp
)

source_group("Source Files" FILES ${SRC_FILES})

# build target
add_executable(${PROJECT_NAME}
   ${SRC_FILES} ${HDR_FILES}
   )

# linker command - add additional libraries for build target
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

if(WITH_UT)
    include(CTest)
    enable_testing()
    add_subdirectory(test)
endif()
