cmake_minimum_required(VERSION 3.6)
project(MyTowerDefence)

set(SOURCE_FILES src/main.c src/main.c src/graphic.c src/graphic.h src/util.c src/util.h src/game.c src/game.h src/map.c src/map.h src/creep.c src/creep.h src/tile.c src/tile.h src/gamestate.c src/gamestate.h src/tower.c src/tower.h src/mapRenderer.c src/mapRenderer.h src/menu.c src/menu.h src/menuRenderer.c src/menuRenderer.h src/vector.c src/vector.h)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIR})

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

find_package(SDL2GFX REQUIRED)
include_directories(${SDL2GFX_INCLUDE_DIR})

#INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2TTF_LIBRARY} ${SDL2GFX_LIBRARY})