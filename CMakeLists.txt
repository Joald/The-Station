cmake_minimum_required(VERSION 3.8)
project(The_Station)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        src/Character.h
        src/Explosion.h
        src/item.h
        src/Projectile.h
        src/Section.h
        src/Station.h
        src/The_Station.h
        src/FloorTile.h
        src/TileDrop.h
        src/Room.h
        src/Character.cpp
        src/Explosion.cpp
        src/item.cpp
        src/main.cpp
        src/Projectile.cpp
        src/Room.cpp
        src/Section.cpp
        src/Station.cpp
        src/The_Station.cpp
        src/FloorTile.cpp
        src/TileDrop.cpp src/ResourcePool.cpp src/ResourcePool.h src/ImagePool.cpp src/ImagePool.h src/ResourceNotFoundError.cpp src/ResourceNotFoundError.h src/Menu.cpp src/Menu.h src/MenuAction.cpp src/MenuAction.h src/GameOption.cpp src/GameOption.h)

add_executable(The_Station ${SOURCE_FILES})


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(The_Station ${SFML_LIBRARIES})
endif()