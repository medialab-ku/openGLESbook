# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

include_directories( src/main/cpp/ )
add_library( # Sets the name of the library.
             opengles

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/main.cpp
             src/main/cpp/utility/asset.cpp
             src/main/cpp/utility/picopng.cpp
             src/main/cpp/utility/input.cpp
             src/main/cpp/utility/scene.cpp
             src/main/cpp/render/target.cpp
             src/main/cpp/render/shader.cpp
             src/main/cpp/render/program.cpp
             src/main/cpp/render/uniform.cpp
             src/main/cpp/render/texture.cpp
             src/main/cpp/render/material.cpp
             src/main/cpp/render/object.cpp
             src/main/cpp/render/camera.cpp
             src/main/cpp/render/light.cpp
             src/main/cpp/example/hello_teapot.cpp
             src/main/cpp/example/image_texturing.cpp
             src/main/cpp/example/phong_lighting.cpp
             src/main/cpp/example/arcball_rotation.cpp
             src/main/cpp/example/normal_mapping.cpp
             src/main/cpp/example/tangent_mapping.cpp
             src/main/cpp/example/shadow_mapping.cpp
             src/main/cpp/example/cube_mapping.cpp
             src/main/cpp/example/pn_triangles.cpp
             src/main/cpp/example/disp_mapping.cpp )

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
                       opengles

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} android GLESv3 )