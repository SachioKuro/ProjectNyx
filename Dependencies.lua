VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/ProjectNyxEngine/vendor/GLFW/include"
IncludeDir["glm"] = "%{wks.location}/ProjectNyxEngine/vendor/glm"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

LibraryDir = {}

LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"
LibraryDir["GLFW"] = "%{wks.location}/ProjectNyxEngine/vendor/GLFW/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/GLFW"

Library = {}
Library["GLFW"] = "%{LibraryDir.GLFW}/GLFW.lib"
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"
