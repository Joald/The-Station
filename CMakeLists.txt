cmake_minimum_required(VERSION 3.8)
project(The_Station)

set(CMAKE_CXX_STANDARD 20)

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
        src/Rendering/Renderer.h src/Rendering/Renderable.h src/Rendering/CollisionDetector.cpp src/Rendering/CollisionDetector.h src/Rendering/CollisionGraph.cpp src/Rendering/CollisionGraph.h src/Rendering/CollisionShape.cpp src/Rendering/CollisionShape.h src/Rendering/Collidable.cpp src/Rendering/Collidable.h src/Rendering/CollisionRectangle.cpp src/Rendering/CollisionRectangle.h src/Rendering/CollisionCircle.cpp src/Rendering/CollisionCircle.h src/Rendering/CollisionNegativeRectangle.cpp src/Rendering/CollisionNegativeRectangle.h)

set(EXCEPTIONS # custom exceptions
        src/Exceptions/ResourceNotFoundError.cpp
        src/Exceptions/ResourceNotFoundError.h)

set(MODELS # classes that represent objects in the game logic
        src/Models/GameOption.cpp
        src/Models/GameOption.h
        src/Models/GameObject.cpp
        src/Models/GameObject.h
        src/Models/Player.cpp
        src/Models/Player.h src/Models/Behaviour/Controllable.cpp src/Models/Behaviour/Controllable.h src/Models/ScreenEdge.cpp src/Models/ScreenEdge.h src/Models/Menus/MenuManager.cpp src/Models/Menus/MenuManager.h)

set(GLOBALS
        src/Globals/Globals.cpp
        src/Globals/Globals.h
        src/Globals/Math.h
        src/Globals/Math.cpp
        src/Filesystem/Filesystem.h
        src/Filesystem/Filesystem.cpp)

set(DEPRECATED
        src/Deprecated/Menu.cpp
        src/Deprecated/Menu.h
        src/Deprecated/MenuAction.cpp
        src/Deprecated/MenuAction.h
        # pre-rework files
        src/Character.h
        src/Explosion.h
        src/item.h
        src/Projectile.h
        src/Section.h
        src/GameState.h
        src/FloorTile.h
        src/TileDrop.h
        src/Room.h
        src/Character.cpp
        src/Explosion.cpp
        src/item.cpp
        src/Projectile.cpp
        src/Room.cpp
        src/Section.cpp
        src/GameState.cpp
        src/FloorTile.cpp
        src/TileDrop.cpp
        src/main.cpp
        )
set(SOURCE_FILES # all classes


        # reworked classes
        ${RESOURCE_MANAGERS}
        ${EVENTS}
        ${RENDERING}
        ${EXCEPTIONS}
        ${MODELS}
        ${LOGGING}
        ${TIME}
        ${GLOBALS})

set(BASE_PATH "${CMAKE_SOURCE_DIR}")
include_directories("${BASE_PATH}/src")


set(MAIN_EXEC src/main.cpp) # files used only in game executable

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

    target_compile_options(The_Station PUBLIC "-fsanitize=undefined" "-fsanitize=leak" "-fsanitize=address")
    target_link_options(The_Station PUBLIC "-fsanitize=undefined" "-fsanitize=leak" "-fsanitize=address")
endif ()