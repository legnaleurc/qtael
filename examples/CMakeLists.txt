# example 1
find_package(Qt5Network REQUIRED)
add_executable(example_01 WIN32 "01_httpclient/main.cpp")
target_include_directories(example_01 PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(example_01 Qt5::Core Qt5::Network qtael)

# example 2
add_executable(example_02 WIN32 "02_jobqueue/main.cpp" "02_jobqueue/jobqueue.hpp" "02_jobqueue/jobqueue.cpp")
target_include_directories(example_02 PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(example_02 Qt5::Core qtael)

# examples 3
find_package(Qt5Network REQUIRED)
add_executable(example_03 WIN32 "03_httpserver/main.cpp" "03_httpserver/httpserver.hpp" "03_httpserver/httpserver.cpp")
target_include_directories(example_03 PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(example_03 Qt5::Core Qt5::Network qtael)

# examples 4
add_executable(example_04 WIN32 "04_jobqueue2/main.cpp" "04_jobqueue2/jobqueue.hpp" "04_jobqueue2/jobqueue.cpp")
target_include_directories(example_04 PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(example_04 Qt5::Core qtael)

# examples 5
add_executable(example_05 WIN32 "05_future/main.cpp")
target_include_directories(example_05 PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(example_05 Qt5::Core qtael)

# example 6
find_package(Qt5Network REQUIRED)
add_executable(example_06 WIN32 "06_httpclient2/main.cpp")
target_include_directories(example_06 PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(example_06 Qt5::Core Qt5::Network qtael)
