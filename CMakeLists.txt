cmake_minimum_required(VERSION 2.8.12)

project(qtcoroutine)

# OS settings
if(APPLE)
    set(CMAKE_MACOSX_RPATH ON)
endif()

# compiler settings
# if("${CMAKE_CXX_COMPILER_ID}" MATCHES "^Clang|GNU$")
#     set(EXTRA_CXX_FLAGS "-std=c++11")
# elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
#     set(EXTRA_CXX_FLAGS "-DBOOST_ALL_NO_LIB")
# endif()

# dependencies
find_package(Qt5Core REQUIRED)
set(CMAKE_AUTOMOC ON)
find_package(Boost 1.56 REQUIRED COMPONENTS system context)

# global -I
include_directories(${Boost_INCLUDE_DIRS} "${CMAKE_SOURCE_DIR}/include")

# library source files
set(SOURCES "include/qtcoroutine.hpp" "src/qtcoroutine.cpp" "src/qtcoroutine_p.hpp")

# main build target
add_library(qtcoroutine SHARED ${SOURCES})
target_link_libraries(qtcoroutine ${Boost_LIBRARIES} Qt5::Core)
set_property(TARGET qtcoroutine APPEND PROPERTY
    COMPILE_FLAGS ${EXTRA_CXX_FLAGS})
set_property(TARGET qtcoroutine APPEND PROPERTY
    COMPILE_DEFINITIONS QTCOROUTINE_LIBRARY)

install(TARGETS qtcoroutine
        RUNTIME DESTINATION "bin"
        LIBRARY DESTINATION "lib"
        ARCHIVE DESTINATION "lib")
install(FILES "include/qtcoroutine.hpp" DESTINATION "include")

# example 1
find_package(Qt5Network REQUIRED)
add_executable(example_01 WIN32 "examples/01_httpclient/main.cpp")
target_link_libraries(example_01 Qt5::Core Qt5::Network qtcoroutine)
set_property(TARGET example_01 APPEND PROPERTY
    COMPILE_FLAGS ${EXTRA_CXX_FLAGS})

# example 2
add_executable(example_02 WIN32 "examples/02_jobqueue/main.cpp" "examples/02_jobqueue/jobqueue.hpp" "examples/02_jobqueue/jobqueue.cpp")
target_link_libraries(example_02 Qt5::Core qtcoroutine)
set_property(TARGET example_02 APPEND PROPERTY
    COMPILE_FLAGS ${EXTRA_CXX_FLAGS})

# examples 3
find_package(Qt5Network REQUIRED)
add_executable(example_03 WIN32 "examples/03_httpserver/main.cpp" "examples/03_httpserver/httpserver.hpp" "examples/03_httpserver/httpserver.cpp")
target_link_libraries(example_03 Qt5::Core Qt5::Network qtcoroutine)
set_property(TARGET example_03 APPEND PROPERTY
    COMPILE_FLAGS ${EXTRA_CXX_FLAGS})

# examples 4
add_executable(example_04 WIN32 "examples/04_jobqueue2/main.cpp" "examples/04_jobqueue2/jobqueue.hpp" "examples/04_jobqueue2/jobqueue.cpp")
target_link_libraries(example_04 Qt5::Core qtcoroutine)
set_property(TARGET example_04 APPEND PROPERTY
    COMPILE_FLAGS ${EXTRA_CXX_FLAGS})

# examples 5
add_executable(example_05 WIN32 "examples/05_future/main.cpp")
target_link_libraries(example_05 Qt5::Core qtcoroutine)
set_property(TARGET example_05 APPEND PROPERTY
    COMPILE_FLAGS ${EXTRA_CXX_FLAGS})
