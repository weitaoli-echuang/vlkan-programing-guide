#include "Image.h"
Image::Image(VkDevice device)
{
	_device = device;
}

Image::~Image()
{
}

void Image::CreateImage()
{
	VkImageCreateInfo image_create_info;
	image_create_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	image_create_info.pNext = nullptr;
	image_create_info.flags = VkImageCreateFlagBits::VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT;
	image_create_info.imageType = VkImageType::VK_IMAGE_TYPE_1D;
	image_create_info.format = VkFormat::VK_FORMAT_B8G8R8A8_UINT;
	image_create_info.extent = VkExtent3D{ 1024, 1, 1 };
	image_create_info.arrayLayers = 1;
	image_create_info.mipLevels = 1;
	image_create_info.samples = VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT;
	image_create_info.tiling = VkImageTiling::VK_IMAGE_TILING_LINEAR;
	image_create_info.usage = VkImageUsageFlagBits::VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
	image_create_info.sharingMode = VkSharingMode::VK_SHARING_MODE_EXCLUSIVE;
	image_create_info.queueFamilyIndexCount = 0;
	image_create_info.pQueueFamilyIndices = nullptr;
	image_create_info.initialLayout = VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED;

	SUCCESS(vkCreateImage(_device, &image_create_info, nullptr, &_image));
}