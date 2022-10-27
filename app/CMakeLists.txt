# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
            native-lib

            # Sets the library as a shared library.
            SHARED

            # General.
            src/main/cpp/JNICalls.cpp
            src/main/cpp/Game.cpp
            # My Scenes.
            src/main/cpp/scenes/FlappyBirds/SceneFlappyBirds.cpp
            src/main/cpp/scenes/FlappyBirds/Player.cpp
            src/main/cpp/scenes/FlappyBirds/Scenary.cpp
            src/main/cpp/scenes/SceneTest5.cpp
            src/main/cpp/scenes/SceneTest4.cpp
            src/main/cpp/scenes/SceneTest3.cpp
            src/main/cpp/scenes/SceneTest2.cpp
            src/main/cpp/scenes/SceneTest1.cpp
            #ENGINE
            # Graphics.
            src/main/cpp/engine/graphics/shaders/ShaderController.cpp
            src/main/cpp/engine/graphics/shaders/ShadersSource.cpp
            src/main/cpp/engine/graphics/shaders/Shader.cpp
            src/main/cpp/engine/graphics/camera/CameraController.cpp
            src/main/cpp/engine/graphics/camera/Camera.cpp
            src/main/cpp/engine/graphics/drawable/Shape.cpp
            src/main/cpp/engine/graphics/drawable/ShapeRectangle.cpp
            src/main/cpp/engine/graphics/drawable/ShapeCircle.cpp
            # Scene.
            src/main/cpp/engine/scene/SceneNode.cpp
            src/main/cpp/engine/scene/Scene.cpp
            src/main/cpp/engine/scene/FactoryComponent.cpp
            src/main/cpp/engine/scene/components/Component.cpp
            src/main/cpp/engine/scene/components/Renderer.cpp
            src/main/cpp/engine/scene/components/ShapeRenderer.cpp
            src/main/cpp/engine/scene/components/RendererRectangle.cpp
            src/main/cpp/engine/scene/components/RendererCircle.cpp
            src/main/cpp/engine/scene/components/PhysicsBody.cpp
            src/main/cpp/engine/scene/components/ColliderBox.cpp
            src/main/cpp/engine/scene/components/ColliderCircle.cpp
            src/main/cpp/engine/scene/Transform.h
            # Physics.
            src/main/cpp/engine/physics/WorldPhysics.cpp
            # Common and utils.
            src/main/cpp/engine/common/Utils.h
            src/main/cpp/engine/common/Timer.cpp
            src/main/cpp/engine/common/events/EventDispatcher.cpp
            src/main/cpp/engine/common/events/EventPool.cpp)


# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib
                       GLESv2

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )