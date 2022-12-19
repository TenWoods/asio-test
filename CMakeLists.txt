cmake_minimum_required(VERSION 3.23)
project(asio_test)

set(CMAKE_CXX_STANDARD 17)
set(ASIO_LIB ${CMAKE_CURRENT_SOURCE_DIR}/asio-1.24.0/include)
add_executable(asio_client src/main_client.cpp)
add_executable(asio_server src/main_server.cpp)
target_include_directories(asio_client PUBLIC ${ASIO_LIB})
target_include_directories(asio_server PUBLIC ${ASIO_LIB})
