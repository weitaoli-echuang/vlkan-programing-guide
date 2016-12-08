#include "Buffers.h"

Buffers::Buffers(VkDevice device)
{
	_device = device;
}

Buffers::~Buffers()
{
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