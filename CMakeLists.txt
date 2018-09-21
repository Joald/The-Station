cmake_minimum_required(VERSION 3.8)
project(The_Station)

set(CMAKE_CXX_STANDARD 17)

set(RESOURCE_MANAGERS # helper engine classes
    src/ResourceManagers/ResourcePool.cpp
    src/ResourceManagers/ResourcePool.h
    src/ResourceManagers/ImagePool.cpp
    src/ResourceManagers/ImagePool.h
    src/ResourceManagers/ShaderPool.cpp
    src/ResourceManagers/ShaderPool.h
    src/ResourceManagers/TexturePool.cpp
    src/ResourceManagers/TexturePool.h)

set(EVENTS
    src/Events/EventManager.cpp
    src/Events/EventManager.h
    src/Events/EventContainer.cpp
    src/Events/EventContainer.h
    src/Events/Observable.h
    src/Events/Observer.h)

set(TIME
    src/Time/Time.h
    src/Time/Time.cpp)

set(LOGGING
    src/Logging/Logger.cpp
    src/Logging/Logger.h)

set(RENDERING # classes that do actual graphics displaying
    src/Rendering/Renderer.cpp
    src/Rendering/Renderer.h src/Rendering/Renderable.h src/Rendering/CollisionDetector.cpp src/Rendering/CollisionDetector.h src/Rendering/CollisionGraph.cpp src/Rendering/CollisionGraph.h src/Rendering/CollisionShape.cpp src/Rendering/CollisionShape.h)

set(EXCEPTIONS # custom exceptions
    src/Exceptions/ResourceNotFoundError.cpp
    src/Exceptions/ResourceNotFoundError.h)

set(MODELS # classes that represent objects in the game logic
    src/Models/Menu.cpp
    src/Models/Menu.h
    src/Models/MenuAction.cpp
    src/Models/MenuAction.h
    src/Models/GameOption.cpp
    src/Models/GameOption.h
    src/Models/GameObject.cpp
    src/Models/GameObject.h
    src/Models/Player.cpp
    src/Models/Player.h src/Models/Behaviour/Controllable.cpp src/Models/Behaviour/Controllable.h)

set(GLOBALS
    src/Globals/Globals.cpp
    src/Globals/Globals.h
    src/Globals/Math.h)

set(SOURCE_FILES # all classes
    # old classes
#    src/Character.h
#    src/Explosion.h
#    src/item.h
#    src/Projectile.h
#    src/Section.h
#    src/GameState.h
#    src/FloorTile.h
#    src/TileDrop.h
#    src/Room.h
#    src/Character.cpp
#    src/Explosion.cpp
#    src/item.cpp
#    src/Projectile.cpp
#    src/Room.cpp
#    src/Section.cpp
#    src/GameState.cpp
#    src/FloorTile.cpp
#    src/TileDrop.cpp
#    src/main.cpp

    # reworked classes
    ${RESOURCE_MANAGERS}
    ${EVENTS}
    ${RENDERING}
    ${EXCEPTIONS}
    ${MODELS}
    ${LOGGING}
    ${TIME}
    ${GLOBALS})


set(MAIN_EXEC src/new_main.cpp ) # files used only in game executable

add_executable(The_Station ${SOURCE_FILES} ${MAIN_EXEC})

set(TEST_FILES
    tests/test.cpp tests/DummyWindow.cpp tests/DummyWindow.h)

add_executable(Tester ${SOURCE_FILES} ${TEST_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/")
set(SFML_INCLUDE_DIR SFML/include)
set(SFML_DIR SFML/cmake-build-debug)
set(SFML_LIBRARIES sfml-graphics sfml-network sfml-audio)
find_package(SFML 2.5 REQUIRED system window graphics network audio)
if (SFML_FOUND)
    message("SFML was found!")
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(The_Station ${SFML_LIBRARIES})
    target_link_libraries(Tester ${SFML_LIBRARIES})
endif ()