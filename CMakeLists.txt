cmake_minimum_required(VERSION 3.20)

file(GLOB src "src/*.cpp")

project(group_gen)

add_executable(${PROJECT_NAME} ${src})

