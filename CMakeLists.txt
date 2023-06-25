cmake_minimum_required(VERSION 3.16)
project(ray_tracer)

set(CMAKE_CXX_STANDARD 17)
include(FetchContent)

FetchContent_Declare(tinyxml2
    GIT_REPOSITORY https://github.com/leethomason/tinyxml2
    GIT_TAG 9.0.0
)

FetchContent_MakeAvailable(tinyxml2)

file(GLOB_RECURSE SRCS 
        src/*.cpp
        include/*.h
)


# include_directories()
include_directories(include)  # Include the 'include' directory

add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME} tinyxml2::tinyxml2)