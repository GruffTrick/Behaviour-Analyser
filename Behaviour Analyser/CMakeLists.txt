cmake_minimum_required(VERSION 3.17)
project(Behaviour_Analyser C)

set(CMAKE_C_STANDARD 11)

set(GCC_ENABLE_WARNINGS "-O1 -Wall -Werror -Wno-unused-result")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_ENABLE_WARNINGS}")

set( project_sources
        main.c
        reader.c
        movements.c
        csv.c
        config.c
        graphs.c
        functions.h )

add_executable(${PROJECT_NAME}
        ${project_sources})
