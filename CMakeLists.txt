cmake_minimum_required(VERSION 3.28)
project(asmt-5-game-engine-olesia-mykhailyshyn)

set(CMAKE_CXX_STANDARD 17)
include_directories("C:/SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.1/include")
link_directories("C:/SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.1/lib")

add_executable(asmt-5-game-engine-olesia-mykhailyshyn
        main.cpp
        Input.h
)

target_link_libraries(asmt-5-game-engine-olesia-mykhailyshyn sfml-graphics sfml-window sfml-system opengl32 freetype winmm gdi32 user32 ws2_32)