cmake_minimum_required(VERSION 3.13)
project(mdrun)

set(BUILD_SHARED_LIBS OFF)
if(NOT APPLE)
    set(CMAKE_EXE_LINKER_FLAGS "-static ${CMAKE_EXE_LINKER_FLAGS}")
endif()

set(DIR_INC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(DIR_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(${DIR_INC})

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED true)
set(CMAKE_C_FLAGS "-pedantic -Wall -Werror ${CMAKE_C_FLAGS}")
set(SOURCES ${DIR_SRC}/mdprocess.c ${DIR_SRC}/main.c)

add_executable(${PROJECT_NAME} ${SOURCES})
