cmake_minimum_required(VERSION 3.8)

project(qtcoroutine)

# options
option(BUILD_EXAMPLES "build examples" OFF)

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

if(BUILD_EXAMPLES)
    add_subdirectory("examples")
endif()
