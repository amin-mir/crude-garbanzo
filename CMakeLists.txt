cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main
    src/main.cpp
    src/input_receiver.cpp
    src/input_dispatcher.cpp
    src/factory.cpp
    src/game_object.cpp
    src/sound_engine.cpp
    src/level_update.cpp
    src/player_update.cpp
    src/player_graphics.cpp
    src/camera_update.cpp
    src/camera_graphics.cpp
    src/platform_update.cpp
    src/platform_graphics.cpp
    src/animator.cpp
    src/rain_graphics.cpp
    src/menu_update.cpp
    src/menu_graphics.cpp
    src/fireball_update.cpp
    src/fireball_graphics.cpp
)
target_compile_features(main PRIVATE cxx_std_23)
target_link_libraries(main PRIVATE sfml-graphics sfml-audio)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)
