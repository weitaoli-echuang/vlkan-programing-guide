#include <iostream>
#include <vector>
#include <string>
#include <vulkan/vulkan.h>

int main() {
	std::cout << "print here" << std::endl;
	VkApplicationInfo app_info{};
	app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	app_info.pNext = nullptr;
	app_info.apiVersion = VK_API_VERSION;
	app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	app_info.pApplicationName = "Vulkan program guide";
	app_info.pEngineName = "Instance Example";

	std::vector<const char*> layers;
	//layers.push_back("VK_LAYER_LUNARG_standard_validation");
	/*layers.push_back("VK_LAYER_LUNARG_threading");
	layers.push_back("VK_LAYER_GOOGLE_threading");
	layers.push_back("VK_LAYER_LUNARG_draw_state");
	layers.push_back("VK_LAYER_LUNARG_image");
	layers.push_back("VK_LAYER_LUNARG_mem_tracker");
	layers.push_back("VK_LAYER_LUNARG_object_tracker");
	layers.push_back("VK_LAYER_LUNARG_param_checker");*/

	std::vector<const char*> extentions;

	VkInstanceCreateInfo instance_info{};
	instance_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instance_info.pNext = nullptr;
	instance_info.pApplicationInfo = &app_info;
	instance_info.flags = 0;
	instance_info.enabledExtensionCount = extentions.size();
	instance_info.ppEnabledExtensionNames = extentions.data();
	instance_info.enabledLayerCount = layers.size();
	instance_info.ppEnabledLayerNames = layers.data();

	VkResult instance_create_flag;
	VkInstance instance;
	instance_create_flag = vkCreateInstance(&instance_info, nullptr, &instance);
	if (instance_create_flag != VK_SUCCESS)
		std::cout << "instance create error!" << std::endl;
	else
		std::cout << "instance create success!" << std::endl;

	std::cout << "find the physical device that support the instance" << std::endl;
	VkResult physical_device_find_flag;
	uint32_t physical_device_count = 0;
	physical_device_find_flag = vkEnumeratePhysicalDevices(instance, &physical_device_count, nullptr);
	if (physical_device_find_flag != VK_SUCCESS)
		std::cout << "can not find compatible physical device" << std::endl;
	else
		std::cout << "find " << physical_device_count << " physical devices" << std::endl;

	std::vector<VkPhysicalDevice> physical_devices(physical_device_count);
	physical_device_find_flag = vkEnumeratePhysicalDevices(instance, &physical_device_count, physical_devices.data());
	if (physical_device_find_flag != VK_SUCCESS)
		std::cout << "can not find compatible physical device" << std::endl;

	return 0;
}