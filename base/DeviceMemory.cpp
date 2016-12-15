#include "DeviceMemory.h"

DeviceMemory::DeviceMemory(VkDevice device)
{
	_device = device;
}

DeviceMemory::~DeviceMemory()
{
	vkFreeMemory(_device, _device_memory, nullptr);
}

void DeviceMemory::AllocateMemory()
{
	VkMemoryAllocateInfo memory_allocate_info;
	memory_allocate_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	memory_allocate_info.pNext = nullptr;
	memory_allocate_info.allocationSize = 1024 * 1024;
	///<The memory
	///<type, passed in memoryTypeIndex, is an index into the memory type array returned from a call to
	///<vkGetPhysicalDeviceMemoryProperties()
	memory_allocate_info.memoryTypeIndex = 0;

	vkAllocateMemory(_device, &memory_allocate_info, nullptr, &_device_memory);

	VkDeviceSize device_size;
	vkGetDeviceMemoryCommitment(_device, _device_memory, &device_size);

	void** pdata;
	vkMapMemory(_device, _device_memory, 0, VK_WHOLE_SIZE, 0, pdata);
	VkMappedMemoryRange memory_range;
	memory_range.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
	memory_range.pNext = 0;
	memory_range.offset = 0;
	memory_range.size = VK_WHOLE_SIZE;
	///<host write, device see
	vkFlushMappedMemoryRanges(_device, 1, &memory_range);

	///<device write, host see
	vkInvalidateMappedMemoryRanges(_device, 1, &memory_range);

	vkUnmapMemory(_device, _device_memory);
}