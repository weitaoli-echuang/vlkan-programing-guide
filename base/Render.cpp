#include "Render.h"
Render::Render()
{
	_using_physical_device = 0;
}

Render::~Render()
{
	_CleanDevice();
	_CleanInstance();
}

void Render::Init()
{
	_InitInstance();
	_InitPhysicalDevice();
	_InitDevice();
}

void Render::_InitAppInfo()
{
	_app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	_app_info.pNext = nullptr;
	_app_info.apiVersion = VK_API_VERSION;
	_app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	_app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	_app_info.pApplicationName = "Vulkan program guide";
	_app_info.pEngineName = "Instance Example";
}

void Render::_InitInstance()
{
	std::cout << "init instance!" << std::endl;

	_InitAppInfo();

	_InstanceLayerProperties();

	_InstanceExtensionProperties();

	VkInstanceCreateInfo instance_info{};
	instance_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instance_info.pNext = nullptr;
	instance_info.pApplicationInfo = &_app_info;
	instance_info.flags = 0;
	instance_info.enabledExtensionCount = _extentions.size();
	instance_info.ppEnabledExtensionNames = _extentions.data();
	instance_info.enabledLayerCount = _layers.size();
	instance_info.ppEnabledLayerNames = _layers.data();

	VkResult instance_create_flag;
	SUCCESS(vkCreateInstance(&instance_info, nullptr, &_instance));
}

void Render::_InitPhysicalDevice()
{
	std::cout << "find the physical device that support the instance" << std::endl;
	SUCCESS(vkEnumeratePhysicalDevices(_instance, &_physical_devices_counts, nullptr));
	assert(_physical_devices_counts >= 1);
	_physical_devices.resize(_physical_devices_counts);
	SUCCESS(vkEnumeratePhysicalDevices(_instance, &_physical_devices_counts, _physical_devices.data()));
	assert(_physical_devices.size() >= 1);

	///<显卡的固有属性
	vkGetPhysicalDeviceProperties(_physical_devices.at(_using_physical_device), &_physical_device_properties);
	std::cout << "device name " << _physical_device_properties.deviceName << "\n";
	std::cout << "device type " << _physical_device_properties.deviceType << "\n";
	std::cout << "device vendor " << _physical_device_properties.vendorID << "\n";

	///<Vulkan has a number of optional features that may be supported by a physical device.
	///<If a device advertises support for a feature, it must still be enabled (much like an extension),
	///<but once enabled, that feature becomes a first-class citizen of the API just like any core feature
	vkGetPhysicalDeviceFeatures(_physical_devices.at(_using_physical_device), &_physical_device_features);

	///<Device memory in Vulkan refers to memory that is accessible to the device and usable as a backing store for
	///<textures and other data. Memory is classified into types, each of which has a set of properties, such as
	///<caching flags and coherency behavior between host and device
	vkGetPhysicalDeviceMemoryProperties(_physical_devices.at(_using_physical_device), &_physical_device_memory_properties);
	std::cout << "memory type count " << _physical_device_memory_properties.memoryTypeCount << "\n";
	std::cout << "memory heap count " << _physical_device_memory_properties.memoryTypeCount << "\n";

	_PhysicalDeviceLayerProperties();

	_DeviceExtensionProperties();

	_PhysicalDeviceFormatProperties();

	vkGetPhysicalDeviceQueueFamilyProperties(_physical_devices.at(_using_physical_device), &_queue_family_count, nullptr);
	assert(_queue_family_count >= 1);
	_queue_family_properties.resize(_queue_family_count);
	vkGetPhysicalDeviceQueueFamilyProperties(_physical_devices.at(_using_physical_device), &_queue_family_count, _queue_family_properties.data());
	std::cout << "queue family count " << _queue_family_count << "\n";
	for (auto &i : _queue_family_properties)
	{
		std::cout << "queue count " << i.queueCount << " queue flags " << i.queueFlags << "\n";
	}
}

void Render::_InitDevice()
{
	VkDeviceQueueCreateInfo device_queue_create_info{};
	device_queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	device_queue_create_info.flags = 0;
	device_queue_create_info.pNext = nullptr;
	device_queue_create_info.queueFamilyIndex = 0;
	device_queue_create_info.queueCount = 1;
	///<The pQueuePriorities field is an optional pointer to an array of floating point values
	///<representing the relative priority of work submitted to each of the queues. These numbers are
	///<normalized numbers in the range of 0.0 to 1.0. Queues with higher priority may be allocated more
	///<processing resources or scheduled more aggressively than queues with lower priority. Setting
	///<pQueuePriorities to nullptr has the effect of leaving the queues at the same, default
	///<priority.
	device_queue_create_info.pQueuePriorities = nullptr;

	_device_queue_create_info.push_back(device_queue_create_info);

	VkDeviceCreateInfo device_create_info{};
	device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	device_create_info.pNext = nullptr;
	device_create_info.flags = 0;
	device_create_info.queueCreateInfoCount = _device_queue_create_info.size();
	device_create_info.pQueueCreateInfos = _device_queue_create_info.data();
	device_create_info.enabledExtensionCount = _extentions.size();
	device_create_info.ppEnabledExtensionNames = _extentions.data();
	device_create_info.enabledLayerCount = _layers.size();
	device_create_info.ppEnabledLayerNames = _layers.data();
	///<It’s not a good idea to enable features that won’t be used. In an optimized application,
	///<you should query the supported features from the device; then, from the supported features, enable
	///<	the specific features that your application requires.
	device_create_info.pEnabledFeatures = &_physical_device_features;

	SUCCESS(vkCreateDevice(_physical_devices.at(_using_physical_device), &device_create_info, nullptr, &_device));
}

void Render::_InstanceLayerProperties()
{
	uint32_t instance_layer_properties_count;
	SUCCESS(vkEnumerateInstanceLayerProperties(&instance_layer_properties_count, nullptr));
	assert(instance_layer_properties_count >= 1);
	_instance_layer_properties.resize(instance_layer_properties_count);
	SUCCESS(vkEnumerateInstanceLayerProperties(&instance_layer_properties_count, _instance_layer_properties.data()));
	std::cout << "instance layer properties" << std::endl;
	for (auto &i : _instance_layer_properties)
	{
		std::cout << i.layerName << "\t" << i.specVersion << "\t" << i.implementationVersion << "\t" << i.description << std::endl;
	}

	///< temp use
	_layers.push_back("VK_LAYER_LUNARG_standard_validation");
}

void Render::_PhysicalDeviceLayerProperties()
{
	uint32_t device_layer_properties_count;
	SUCCESS(vkEnumerateDeviceLayerProperties(_physical_devices.at(_using_physical_device), &device_layer_properties_count, nullptr));
	assert(device_layer_properties_count >= 1);
	_device_layer_properties.resize(device_layer_properties_count);
	SUCCESS(vkEnumerateDeviceLayerProperties(_physical_devices.at(_using_physical_device), &device_layer_properties_count, _device_layer_properties.data()));
	std::cout << "physical device layer properties" << std::endl;
	for (auto &i : _device_layer_properties)
	{
		std::cout << i.layerName << "\t" << i.specVersion << "\t" << i.implementationVersion << "\t" << i.description << std::endl;
	}
}

void Render::_InstanceExtensionProperties()
{
	uint32_t instance_extension_properties;
	SUCCESS(vkEnumerateInstanceExtensionProperties(nullptr, &instance_extension_properties, nullptr));
	assert(instance_extension_properties >= 1);
	_instance_extension_properties.resize(instance_extension_properties);
	SUCCESS(vkEnumerateInstanceExtensionProperties(nullptr, &instance_extension_properties, _instance_extension_properties.data()));
	for (auto &i : _instance_extension_properties)
	{
		std::cout << i.extensionName << "\t" << i.specVersion << std::endl;
	}
}

void Render::_DeviceExtensionProperties()
{
	uint32_t device_extension_properties;
	SUCCESS(vkEnumerateDeviceExtensionProperties(_physical_devices.at(_using_physical_device), nullptr, &device_extension_properties, nullptr));
	assert(device_extension_properties >= 1);
	_device_extension_properties.resize(device_extension_properties);
	SUCCESS(vkEnumerateDeviceExtensionProperties(_physical_devices.at(_using_physical_device), nullptr, &device_extension_properties, _device_extension_properties.data()));
	for (auto &i : _device_extension_properties)
	{
		std::cout << i.extensionName << "\t" << i.specVersion << std::endl;
	}
}

void Render::_PhysicalDeviceFormatProperties()
{
	///<184个vkFormat
	_physical_device_format_properties.resize(184);
	for (uint32_t i = 0; i < 184; i++)
	{
		_physical_device_format.push_back(VkFormat(i));
		vkGetPhysicalDeviceFormatProperties(_physical_devices.at(_using_physical_device), VkFormat(i), &_physical_device_format_properties.at(i));
		std::cout << _physical_device_format_properties.at(i).linearTilingFeatures
			<< "\t" << _physical_device_format_properties.at(i).optimalTilingFeatures
			<< "\t" << _physical_device_format_properties.at(i).bufferFeatures << std::endl;
	}
}

void Render::_PhysicalDeviceImageFormatProperties()
{
	_physical_device_format_properties.clear();
	_physical_device_format_properties.resize(184);
	for (uint32_t i = 0; i < 184; i++)
	{
		_physical_device_format.push_back(VkFormat(i));
		vkGetPhysicalDeviceImageFormatProperties(
			_physical_devices.at(_using_physical_device),
			VkFormat(i),
			VkImageType::VK_IMAGE_TYPE_1D,
			VkImageTiling::VK_IMAGE_TILING_LINEAR,
			VkImageUsageFlagBits::VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
			VkImageCreateFlagBits::VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT,
			&_physical_device_image_format_properties.at(i));
		std::cout << _physical_device_format_properties.at(i).linearTilingFeatures
			<< "\t" << _physical_device_format_properties.at(i).optimalTilingFeatures
			<< "\t" << _physical_device_format_properties.at(i).bufferFeatures << std::endl;
	}
	)
}

void Render::_CleanDevice()
{
	///<before clean up the resource, should wait until all works submitted to device have been down and return back to host
	vkDeviceWaitIdle(_device);
	vkDestroyDevice(_device, nullptr);
}

void Render::_CleanInstance()
{
	vkDestroyInstance(_instance, nullptr);
}