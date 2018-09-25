cmake_minimum_required(VERSION 2.6)

project(ASIOTest)
find_package(Boost REQUIRED COMPONENTS system thread)

add_executable("server" "src/server.cpp")
target_link_libraries("server" ${Boost_LIBRARIES})
add_executable("client" "src/client.cpp")
target_link_libraries("client" ${Boost_LIBRARIES})
