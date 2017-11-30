cmake_minimum_required(VERSION 3.8)

project(qtael)

# options
option(BUILD_EXAMPLES "build examples" OFF)

# dependencies
find_package(Qt5Core 5.6 REQUIRED)
set(CMAKE_AUTOMOC ON)
find_package(Boost 1.59 REQUIRED COMPONENTS system context)

# compiler settings
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(EXTRA_CXX_FLAGS "BOOST_ALL_NO_LIB")
endif()

# library source files
set(SOURCES "include/qtael.hpp" "src/qtael.cpp" "src/qtael_p.hpp")

# main build target
add_library(qtael SHARED ${SOURCES})
target_compile_features(qtael PUBLIC cxx_std_14)
target_compile_definitions(qtael PUBLIC ${EXTRA_CXX_FLAGS})
target_compile_definitions(qtael PRIVATE QTAEL_LIBRARY)
target_include_directories(qtael PRIVATE ${Boost_INCLUDE_DIRS} "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(qtael ${Boost_LIBRARIES} Qt5::Core)

install(TARGETS qtael
        RUNTIME DESTINATION "bin"
        LIBRARY DESTINATION "lib"
        ARCHIVE DESTINATION "lib")
install(FILES "include/qtael.hpp" DESTINATION "include")

if(BUILD_EXAMPLES)
    add_subdirectory("examples")
endif()
