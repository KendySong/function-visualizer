workspace "function-visualizer"
    architecture "x64"
    location "build"
    configurations { "Release", "Debug" }

project "function-visualizer"
    kind "ConsoleApp"
    language "C++"
    location "build"

    files { "src/**.cpp", "src/**.hpp", "src/**.h", "libraries/include/ImGui/**.cpp", "shaders/**", "libraries/lib/glad.c" }

    includedirs "libraries/*"
    libdirs "libraries/lib"
    links { "opengl32", "glfw3" }

    filter "configurations:Release"
        optimize "Full"
        defines "RELEASE"

    filter "configurations:Debug"
        defines "DEBUG"