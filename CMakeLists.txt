cmake_minimum_required(VERSION 3.10)
project(pocoTcpServer DESCRIPTION "Test app tcp server")
set(CMAKE_CXX_STANDARD 17)
find_package(Poco REQUIRED Net)

if(NOT Poco_FOUND)
    message (FATAL_ERROR "Please make sure you have Poco library installed")
endif()

add_executable(pocoTcpServer main.cpp)
target_link_libraries(pocoTcpServer Poco::Net)
