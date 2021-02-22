cmake_minimum_required(VERSION 3.17)
project(jvmti_agent)

set(CMAKE_CXX_STANDARD 14)

add_library(jvmti_agent SHARED Agent.h Agent.cpp ClassInfo.h ClassInfo.cpp)

include_directories($ENV{JDK_HOME}/include $ENV{JDK_HOME}/include/darwin)
