cmake_minimum_required(VERSION 2.6)

project(ASIOTest)

set(CMAKE_MODULE_PATH
	${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(Boost REQUIRED COMPONENTS system thread)
find_package(GMP REQUIRED)

add_executable("server" "src/server.cpp")
target_link_libraries("server" ${Boost_LIBRARIES})
add_executable("client" "src/client.cpp")
target_link_libraries("client" ${Boost_LIBRARIES})
add_executable("gmp_server" "src/gmp_server.cpp")
target_link_libraries("gmp_server" ${Boost_LIBRARIES})
target_link_libraries("gmp_server" gmp)
add_executable("gmp_client" "src/gmp_client.cpp")
target_link_libraries("gmp_client" ${Boost_LIBRARIES})
target_link_libraries("gmp_client" gmp)
