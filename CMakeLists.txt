cmake_minimum_required(VERSION 3.8)

project(qtcoroutine)

# dependencies
find_package(Qt5Core REQUIRED)
set(CMAKE_AUTOMOC ON)
find_package(Boost 1.59 REQUIRED COMPONENTS system context)

# compiler settings
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(EXTRA_CXX_FLAGS "BOOST_ALL_NO_LIB")
endif()

# library source files
set(SOURCES "include/qtcoroutine.hpp" "src/qtcoroutine.cpp" "src/qtcoroutine_p.hpp")

# main build target
add_library(qtcoroutine SHARED ${SOURCES})
target_compile_features(qtcoroutine PUBLIC cxx_std_11)
target_compile_definitions(qtcoroutine PUBLIC ${EXTRA_CXX_FLAGS})
target_compile_definitions(qtcoroutine PRIVATE QTCOROUTINE_LIBRARY)
target_include_directories(qtcoroutine PRIVATE ${Boost_INCLUDE_DIRS} "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(qtcoroutine ${Boost_LIBRARIES} Qt5::Core)

install(TARGETS qtcoroutine
        RUNTIME DESTINATION "bin"
        LIBRARY DESTINATION "lib"
        ARCHIVE DESTINATION "lib")
install(FILES "include/qtcoroutine.hpp" DESTINATION "include")

# example 1
find_package(Qt5Network REQUIRED)
add_executable(example_01 WIN32 "examples/01_httpclient/main.cpp")
target_include_directories(example_01 PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(example_01 Qt5::Core Qt5::Network qtcoroutine)

# example 2
add_executable(example_02 WIN32 "examples/02_jobqueue/main.cpp" "examples/02_jobqueue/jobqueue.hpp" "examples/02_jobqueue/jobqueue.cpp")
target_include_directories(example_02 PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(example_02 Qt5::Core qtcoroutine)

# examples 3
find_package(Qt5Network REQUIRED)
add_executable(example_03 WIN32 "examples/03_httpserver/main.cpp" "examples/03_httpserver/httpserver.hpp" "examples/03_httpserver/httpserver.cpp")
target_include_directories(example_03 PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(example_03 Qt5::Core Qt5::Network qtcoroutine)

# examples 4
add_executable(example_04 WIN32 "examples/04_jobqueue2/main.cpp" "examples/04_jobqueue2/jobqueue.hpp" "examples/04_jobqueue2/jobqueue.cpp")
target_include_directories(example_04 PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(example_04 Qt5::Core qtcoroutine)

# examples 5
add_executable(example_05 WIN32 "examples/05_future/main.cpp")
target_include_directories(example_05 PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(example_05 Qt5::Core qtcoroutine)
