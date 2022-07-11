#pragma once

#include <utility>
#include <vector>
#include <optional>
#include <string>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Core.h"

namespace Nyx {
	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities{};
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	class Application {
	public:
		const uint32_t WINDOW_WIDTH = 800;
		const uint32_t WINDOW_HEIGHT = 600;

		const uint32_t MAX_FRAMES_IN_FLIGHT = 2;

		Application();
		virtual ~Application();

		void Run();
	private:
		GLFWwindow* m_window;
		VkInstance m_instance;
		VkDebugUtilsMessengerEXT m_debugMessenger;
		VkSurfaceKHR m_surface;
		VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
		VkDevice m_device;
		VkQueue m_graphicsQueue;
		VkQueue m_presentQueue;
		VkSwapchainKHR m_swapChain;
		std::vector<VkImage> m_swapChainImages;
		VkFormat m_swapChainImageFormat;
		VkExtent2D m_swapChainExtent;
		std::vector<VkImageView> m_swapChainImageViews;
		VkRenderPass m_renderPass;
		VkPipelineLayout m_pipelineLayout;
		VkPipeline m_graphicsPipeline;
		std::vector<VkFramebuffer> m_swapChainFramebuffers;
		VkCommandPool m_commandPool;
		VkCommandBuffer m_commandBuffer;
		VkSemaphore imageAvailableSemaphore;
		VkSemaphore renderFinishedSemaphore;
		VkFence inFlightFence;

		const std::vector<const char*> m_validationLayers = {
			"VK_LAYER_KHRONOS_validation"
		};

		const std::vector<const char*> m_deviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

#ifdef  NDEBUG
		const bool enableValidationLayers = false;
#else
		const bool enableValidationLayers = true;
#endif //  NDEBUG

		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT,
			VkDebugUtilsMessageTypeFlagsEXT,
			const VkDebugUtilsMessengerCallbackDataEXT*,
			void*
		);

		static std::vector<char> readFile(const std::string& filename);

		void initWindow();

		void initVulkan();
		std::vector<const char*> getRequiredExtensions();
		bool checkValidationLayerSupport();
		void createInstance();
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		void setupDebugMessenger();
		void pickPhysicalDevice();
		bool isDeviceSuitable(VkPhysicalDevice device);
		bool checkDeviceExtensionSupport(VkPhysicalDevice device);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
		void createLogicalDevice();
		void createSurface();
		VkSurfaceFormatKHR chooseSwapSurfaceFormate(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
		void createSwapChain();
		void createImageViews();
		VkShaderModule createShaderModule(const std::vector<char>& code);
		void createRenderPass();
		void createGraphicsPipeline();
		void createFramebuffers();
		void createCommandPool();
		void createCommandBuffer();

		void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
		void createSyncObjects();
		void drawFrame();

		void mainLoop();
	};

	Application* CreateApplication();
}
