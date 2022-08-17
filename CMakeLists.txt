cmake_minimum_required(VERSION 3.19)

# set the project name
project(SfmlTests)

include(FetchContent)

set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(
 SFML
 GIT_REPOSITORY https://github.com/SFML/SFML.git
 GIT_TAG 2.5.1
)

FetchContent_MakeAvailable(SFML)
add_subdirectory(random)


set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(app main.cpp utils/utils.hpp utils/utils.cpp objects/TexturedSprite.hpp objects/TexturedSprite.cpp packets/GetProfile.hpp packets/GetProfile.cpp)

target_include_directories(app PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           utils
                           objects
                           assets
                           )

target_link_libraries(app sfml-graphics sfml-audio sfml-network sfml-main effolkronium_random)
