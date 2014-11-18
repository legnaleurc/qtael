cmake_minimum_required(VERSION 2.8.12)

if(APPLE)
    set(CMAKE_MACOSX_RPATH ON)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "^Clang|GNU$")
    set(EXTRA_CXX_FLAGS "-std=c++11")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(EXTRA_CXX_FLAGS "-DBOOST_ALL_NO_LIB")
endif()

find_package(Qt5Core REQUIRED)
set(CMAKE_AUTOMOC ON)
find_package(Boost REQUIRED COMPONENTS coroutine system context)

include_directories(${Boost_INCLUDE_DIRS} "${CMAKE_SOURCE_DIR}/include")

set(SOURCES "include/qtcoroutine.hpp" "src/qtcoroutine.cpp" "src/qtcoroutine_p.hpp")

add_library(qtcoroutine SHARED ${SOURCES})
set_target_properties(qtcoroutine PROPERTIES COMPILE_DEFINITIONS QTCOROUTINE_LIBRARY)
qt5_use_modules(qtcoroutine Core)
set_target_properties(qtcoroutine PROPERTIES COMPILE_FLAGS ${EXTRA_CXX_FLAGS})
target_link_libraries(qtcoroutine ${Boost_LIBRARIES})

install(TARGETS qtcoroutine
        RUNTIME DESTINATION "bin"
        LIBRARY DESTINATION "lib"
        ARCHIVE DESTINATION "lib")
install(FILES "include/qtcoroutine.hpp" DESTINATION "include")

find_package(Qt5Network REQUIRED)
add_executable(example_01 WIN32 "examples/01_httpclient/main.cpp")
qt5_use_modules(example_01 Core Network)
set_target_properties(example_01 PROPERTIES COMPILE_FLAGS ${EXTRA_CXX_FLAGS})
target_link_libraries(example_01 qtcoroutine)
if(MSVC)
    target_link_libraries(example_01 Qt5::WinMain)
endif()

add_executable(example_02 WIN32 "examples/02_jobqueue/main.cpp" "examples/02_jobqueue/jobqueue.hpp" "examples/02_jobqueue/jobqueue.cpp")
qt5_use_modules(example_02 Core)
set_target_properties(example_02 PROPERTIES COMPILE_FLAGS ${EXTRA_CXX_FLAGS})
target_link_libraries(example_02 qtcoroutine)
if(MSVC)
    target_link_libraries(example_02 Qt5::WinMain)
endif()

find_package(Qt5Network REQUIRED)
add_executable(example_03 WIN32 "examples/03_httpserver/main.cpp" "examples/03_httpserver/httpserver.hpp" "examples/03_httpserver/httpserver.cpp")
qt5_use_modules(example_03 Core Network)
set_target_properties(example_03 PROPERTIES COMPILE_FLAGS ${EXTRA_CXX_FLAGS})
target_link_libraries(example_03 qtcoroutine)
if(MSVC)
    target_link_libraries(example_03 Qt5::WinMain)
endif()

add_executable(example_04 WIN32 "examples/04_jobqueue2/main.cpp" "examples/04_jobqueue2/jobqueue.hpp" "examples/04_jobqueue2/jobqueue.cpp")
qt5_use_modules(example_04 Core)
set_target_properties(example_04 PROPERTIES COMPILE_FLAGS ${EXTRA_CXX_FLAGS})
target_link_libraries(example_04 qtcoroutine)
if(MSVC)
    target_link_libraries(example_04 Qt5::WinMain)
endif()
