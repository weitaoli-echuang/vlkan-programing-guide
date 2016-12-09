#pragma once
#include "common.h"

class Render
{
public:
	Render();
	~Render();

	void Init();

	static Render* Create() {
		return new Render;
	}

	VkApplicationInfo _app_info{};
	VkInstanceCreateInfo _instance_create_info{};
	std::vector<VkLayerProperties> _instance_layer_properties;
	std::vector<VkLayerProperties> _device_layer_properties;
	std::vector<VkExtensionProperties> _instance_extension_properties;
	std::vector<VkExtensionProperties> _device_extension_properties;
	std::vector<const char*> _layers;
	std::vector<const char*> _extentions;

	VkInstance _instance{};
	std::vector<VkPhysicalDevice> _physical_devices;
	uint32_t	_physical_devices_counts;
	VkPhysicalDeviceProperties _physical_device_properties{};
	VkPhysicalDeviceFeatures _physical_device_features{};
	VkPhysicalDeviceMemoryProperties _physical_device_memory_properties{};
	std::vector<VkFormat> _physical_device_format;
	std::vector<VkFormatProperties> _physical_device_format_properties;
	std::vector<VkImageFormatProperties> _physical_device_image_format_properties;
	std::vector<VkQueueFamilyProperties> _queue_family_properties;
	uint32_t _queue_family_count;

	uint32_t _using_physical_device;
	VkDevice _device;
	std::vector<VkDeviceQueueCreateInfo> _device_queue_create_info;

private:
	void _InitAppInfo();
	void _InitInstance();
	void _InitPhysicalDevice();
	void _InitDevice();
	void _InstanceLayerProperties();
	void _InstanceExtensionProperties();
	void _PhysicalDeviceLayerProperties();
	void _DeviceExtensionProperties();
	void _PhysicalDeviceFormatProperties();
	void _PhysicalDeviceImageFormatProperties();

	void _CleanDevice();
	void _CleanInstance();
};
