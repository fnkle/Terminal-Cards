cmake_minimum_required(VERSION 3.10)
project(Cards)
include_directories("include/")
file(GLOB_RECURSE ${PROJECT_NAME}_SRC "src/*.cpp")


add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SRC})
