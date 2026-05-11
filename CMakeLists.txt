cmake_minimum_required(VERSION 3.23)

project(
        MinaVillage
        VERSION 1.0
        DESCRIPTION "Mina Village farm country game"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(
        CMAKE_RUNTIME_OUTPUT_DIRECTORY
        "${CMAKE_BINARY_DIR}/$<CONFIGURATION>"
)

set(
        CMAKE_LIBRARY_OUTPUT_DIRECTORY
        "${CMAKE_BINARY_DIR}/$<CONFIGURATION>"
)

file(GLOB SOURCES   src/defs.h src/structs.h src/*.c src/*.h src/*/*.c src/*/*.h)

add_executable(MinaVillage
        src/Main.cpp 
        # ${SOURCES}
        src/Actor.cpp
        src/BGSpriteComponent.cpp
        src/Component.cpp
        src/Game.cpp
        src/GameMath.cpp
        src/SpriteComponent.cpp
        src/AnimSpriteComponent.cpp
        src/MultiAnimSpriteComponent.cpp
        src/TileMapGame.cpp
        src/SpriteSheetActor.cpp
        src/TileMapComponent.cpp
        src/MapActor.cpp
        src/ISORenderer.cpp
        src/IsoMapGame.cpp
        src/AtlasManager.cpp
)

target_include_directories(MinaVillage
        PRIVATE ${PROJECT_SOURCE_DIR}/src
)

if(APPLE)
  set_target_properties(MinaVillage PROPERTIES
          INSTALL_RPATH "@executable_path;@loader_path"
          BUILD_WITH_INSTALL_RPATH TRUE
          MACOSX_RPATH TRUE
  )
elseif(UNIX)
  set_target_properties(MinaVillage PROPERTIES
          INSTALL_RPATH "$ORIGIN"
          BUILD_WITH_INSTALL_RPATH TRUE
  )
endif()

set(SDLTTF_VENDORED ON)
set(VENDOR_DIR "${PROJECT_SOURCE_DIR}/vendor")
add_subdirectory(${VENDOR_DIR}/SDL)
add_subdirectory(${VENDOR_DIR}/SDL_image)
add_subdirectory(${VENDOR_DIR}/SDL_ttf)
add_subdirectory(${VENDOR_DIR}/SDL_mixer)

target_link_libraries(MinaVillage
        SDL3::SDL3
        SDL3_image::SDL3_image
        SDL3_ttf::SDL3_ttf
        SDL3_mixer::SDL3_mixer
)