project "ProjectNyxSandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "%{wks.location}/ProjectNyxEngine/vendor/spdlog/include",
        "%{wks.location}/ProjectNyxEngine/src",
        "%{wks.location}/ProjectNyxEngine/vendor",
		"%{IncludeDir.VulkanSDK}",
        "%{IncludeDir.GLFW}",
		"%{IncludeDir.glm}"
    }

    links
    {   
        "ProjectNyxEngine"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "NYX_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        runtime "Debug"
        defines
        {
            "DEBUG",
            "NYX_DEBUG"
        }
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        defines
        {
            "NDEBUG",
            "NYX_RELEASE"
        }
        optimize "On"

    filter "configurations:Distribution"
        runtime "Release"
        defines
        {
            "NDEBUG",
            "NYX_DISTRIBUTION"
        }
        optimize "On"