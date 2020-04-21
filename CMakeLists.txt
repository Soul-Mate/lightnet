cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lightnet VERSION 1.0.0 DESCRIPTION "my simple network libaray")

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    add_definitions(-DDEBUG)
endif()


add_library(lightnet SHARED
    lightnet_strarg.cc    
    lightnet_inet_address.cc
    lightnet_socket.cc
    lightnet_listen.cc
    lightnet_tcp_stream.cc
)

set_target_properties(lightnet PROPERTIES VERSION ${PROJECT_VERSION})