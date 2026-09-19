workspace "VGAVis"
    configurations{
        "Debug", 
        "Release"
    }
    architecture "x64"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "VGAVis"
    location "VGAVis"
    language "C++"
    kind "ConsoleApp"

    targetdir ("bin/"..outputdir.."/%{prj.name}")
    objdir ("bin-int/"..outputdir.."/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.c",
        "%{prj.name}/obj_dir/**.cpp", -- verilator compiled files
        "%{prj.name}/include/**.h",
        "%{prj.name}/dependencies/src/**.cpp",
        "%{prj.name}/dependencies/src/**.c"
    }

    includedirs
    {
        "%{wks.location}/%{prj.name}/dependencies/include",
        "%{wks.location}/%{prj.name}/dependencies/include/imgui",
        "%{wks.location}/%{prj.name}/dependencies/include/verilator",
        "%{wks.location}/%{prj.name}/dependencies/include/verilator/vltstd",
        "%{wks.location}/%{prj.name}/dependencies/include/verilator/fstcpp",
        "%{prj.name}/src",
        "%{prj.name}/include",
        "%{prj.name}/obj_dir" -- verilator compiled files
    }

    libdirs
    {
        "%{wks.location}/%{prj.name}/dependencies/libs"
    }

    links 
    {
        "glfw3",
        "opengl32"
    }

    cppdialect "C++17"
    staticruntime "Off"
    systemversion "latest"

    filter "system:windows"
        linkoptions { "/ignore:4099" }

    filter "configurations:Debug"
        defines "DEBUG"
        symbols "on"

    filter "configurations:Release"
        defines "RELEASE"
        symbols "off"
        optimize "on"
