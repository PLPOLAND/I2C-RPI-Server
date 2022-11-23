cmake_minimum_required(VERSION 3.2)

project(I2C-RPI-SERVER VERSION 1.0)
set(CMAKE_C_STANDARD 17)


add_subdirectory(src/TwoWire)
add_executable(I2C-RPI-SERVER src/main.cpp
                src/NetServer.cpp)

add_link_options(-lwiringPi)
add_library(NetServer src/NetServer.cpp)

# target_link_libraries(I2C-RPI-SERVER PUBLIC twowire)
target_link_libraries(I2C-RPI-SERVER PUBLIC wiringPi)

target_include_directories(I2C-RPI-SERVER PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/TwoWire"
    "${PROJECT_SOURCE_DIR}/../include"
)

