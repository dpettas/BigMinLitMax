cmake_minimum_required(VERSION 3.0.0)
project(bigminlitmax VERSION 0.1.0)

set( SOURCES
    ./src/Zkey.cpp
    ./src/BigMinLitMax.cpp
    ./src/bitset_manip.cpp
)

add_executable(bigminlitmax ./src/main.cpp ${SOURCES} )
target_include_directories( bigminlitmax PUBLIC "./include")

