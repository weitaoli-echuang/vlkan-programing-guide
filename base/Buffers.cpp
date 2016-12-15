#include "Buffers.h"

Buffers::Buffers(VkDevice device)
{
	_device = device;
}

Buffers::~Buffers()
{
	vkDestroyBufferView(_device, _buffer_view, nullptr);
	vkDestroyBuffer(_device, _buffer, nullptr);
}

void Buffers::CreateBuffer()
{
	VkBufferCreateInfo buffer_create_info{};
	buffer_create_info.flags = 0;
	buffer_create_info.pNext = nullptr;
	buffer_create_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	buffer_create_info.size = 1024 * 1024;
	///<When sharingMode is set to
	///<VK_SHARING_MODE_EXCLUSIVE, queueFamilyCount and pQueueFamilies are both
	///<	ignored.
	buffer_create_info.sharingMode = VkSharingMode::VK_SHARING_MODE_EXCLUSIVE;
	buffer_create_info.queueFamilyIndexCount = 0;
	buffer_create_info.pQueueFamilyIndices = nullptr;
	buffer_create_info.usage = VkBufferUsageFlagBits::VK_BUFFER_USAGE_TRANSFER_DST_BIT | VkBufferUsageFlagBits::VK_BUFFER_USAGE_TRANSFER_SRC_BIT;

	SUCCESS(vkCreateBuffer(_device, &buffer_create_info, nullptr, &_buffer));
}

void Buffers::CreateBufferView()
{
	VkBufferViewCreateInfo _buffer_view_create_info;
	_buffer_view_create_info.sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO;
	_buffer_view_create_info.flags = 0;
	_buffer_view_create_info.pNext = nullptr;
	_buffer_view_create_info.buffer = _buffer;
	_buffer_view_create_info.offset = 0;
	_buffer_view_create_info.range = 1024;
	_buffer_view_create_info.format = VkFormat::VK_FORMAT_B8G8R8_UINT;

	SUCCESS(vkCreateBufferView(_device, &_buffer_view_create_info, nullptr, &_buffer_view));
}

void Buffers::BindMemory()
{
	VkMemoryRequirements memory_requirements;
	vkGetBufferMemoryRequirements(_device, _buffer, &memory_requirements);

	VkDeviceMemory memory;
	vkBindBufferMemory(_device, _buffer, memory, 0);
}