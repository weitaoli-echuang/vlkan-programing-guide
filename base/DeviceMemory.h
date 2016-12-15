#pragma once
#include "../base/common.h"

class DeviceMemory
{
public:
	DeviceMemory(VkDevice device);
	~DeviceMemory();

	DeviceMemory* Create(VkDevice device)
	{
		return new DeviceMemory(device);
	}

	void AllocateMemory();

	VkDevice _device;
	VkDeviceMemory _device_memory;
};
