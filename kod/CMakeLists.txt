cmake_minimum_required(VERSION 3.13)
project(STA)

set(CMAKE_CXX_STANDARD 17)

set(GCC_COVERAGE_COMPILE_FLAGS "-pedentic-errors")
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall")

include_directories("C:/Program Files (x86)/mingw-w64/i686-8.1.0-posix-dwarf-rt_v6-rev0/mingw32/include")
include_directories(".")

add_executable(STA
        Macros.hpp
        Control.hpp
        Actor.hpp Actor.cpp
        Caller.hpp
        Config.hpp Config.cpp
        Config.inl
        WindowEvents.hpp WindowEvents.cpp
        FixtureData.hpp FixtureData.cpp
        Game.hpp Game.cpp
        main.cpp
        Casts.hpp WorldCallbacks.cpp
        WorldCallbacks.hpp
        Body.hpp Body.cpp
        VisibleBody.hpp VisibleBody.cpp
        Ship.hpp Ship.cpp
        GameConfig.hpp GameConfig.cpp
        Scene.hpp Scene.cpp
        Window.hpp Window.cpp
        Drawable.hpp
        World.hpp World.cpp
        Base.hpp Base.cpp
        CreatorInitializer.hpp
        GlobalScene.hpp GlobalScene.cpp
        TextureBank.hpp TextureBank.cpp
        FontBank.hpp FontBank.cpp
        OnEveryXCalls.hpp
        Animation.hpp Animation.cpp
        AnimatedSprite.hpp AnimatedSprite.cpp
        ActorPtr.hpp
        GlobalWindowEvents.hpp
        AnimationBank.hpp AnimationBank.cpp
        imgui.cpp
        imgui_draw.cpp
        imgui_widgets.cpp
        imgui_stdlib.cpp
        imgui-SFML.cpp ListenerDraw.hpp Building.cpp Building.hpp Room.cpp Room.hpp MainGame.hpp Layers.hpp Human.cpp Human.hpp AConfig.hpp FireFighter.cpp FireFighter.hpp PointsCounter.cpp PointsCounter.hpp Cursor.cpp Cursor.hpp)

target_link_libraries(STA sfml-graphics sfml-window sfml-system)
target_link_libraries(STA Box2D)


if (UNIX)
    target_link_libraries(STA GL)
elseif ()
    target_link_libraries(STA opengl32)
endif ()
