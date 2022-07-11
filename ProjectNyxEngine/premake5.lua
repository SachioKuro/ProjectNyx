project "ProjectNyxEngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.cpp",
        "vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl"
    }

    defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

    includedirs
    {
        "src",
		"vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.VulkanSDK}"
    }

    links
    {
        "GLFW",
        "%{Library.Vulkan}"
    }

    filter { "system:windows", "configurations:Debug"}
        buildoptions "/MDd"
    filter { "system:windows", "configurations:Release"}
        buildoptions "/MD"

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "NYX_PLATFORM_WINDOWS",
            "NYX_BUILD_DLL"
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
