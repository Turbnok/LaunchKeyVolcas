cmake_minimum_required (VERSION 2.6)
project(LaunchkeyMiniMK3Midi)

set(EXECUTABLE_NAME main)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/inc /usr/include)

add_executable( ${EXECUTABLE_NAME}
./src/Screen.cpp
./src/ScreenState.cpp
./src/Sequencer.cpp
./src/devices/Device.cpp
./src/devices/VolcaKeys.cpp
./src/devices/VolcaBass.cpp
./src/MenuState.cpp
./src/ConfigInOut.cpp
./src/Config.cpp
./src/application.cpp
./src/midi.cpp
                ./main.cpp)
# add_executable( ${EXECUTABLE_NAME}
# 				./src/test.cpp)

SET(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -std=c++20 -pedantic -lrtmidi -lyaml-cpp")

set(CMAKE_CXX_FLAGS ${GCC_COVERAGE_COMPILE_FLAGS})

target_link_libraries(main rtmidi)
target_link_libraries(main yaml-cpp)
