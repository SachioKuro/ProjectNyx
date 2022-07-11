include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "ProjectNyx"
    architecture "x86_64"
    startproject "ProjectNyxSandbox"
    
    configurations
    {
        "Debug",
        "Release",
        "Distribution"
    }

    platforms
    {
        "Win64"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
    include "vendor/premake"
    include "ProjectNyxEngine/vendor/GLFW"
group ""
include "ProjectNyxSandbox"
include "ProjectNyxEngine"
