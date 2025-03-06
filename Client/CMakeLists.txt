cmake_minimum_required(VERSION 3.10)

project(Client)

find_package(Boost REQUIRED COMPONENTS system)

add_executable(client main.cpp client.cpp watcher.cpp)

target_link_libraries(client PRIVATE Boost::system)

target_include_directories(client PRIVATE ${Boost_INCLUDE_DIRS})
