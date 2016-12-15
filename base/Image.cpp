#include "Image.h"
Image::Image(VkDevice device)
{
	_device = device;
}

Image::~Image()
{
	vkDestroyImageView(_device, _image_view, nullptr);
	vkDestroyImage(_device, _image, nullptr);
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

	_subresource.aspectMask = VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT;
	_subresource.arrayLayer = 0;
	_subresource.mipLevel = 0;

	vkGetImageSubresourceLayout(_device, _image, &_subresource, &_layout);
}

void Image::CreateImageView()
{
	VkImageSubresourceRange subresouce_range;
	subresouce_range.aspectMask = VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT;
	subresouce_range.baseArrayLayer = 0;
	subresouce_range.layerCount = 1;
	subresouce_range.baseMipLevel = 0;
	subresouce_range.levelCount = 1;

	VkImageViewCreateInfo image_view_create_info;
	image_view_create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	image_view_create_info.flags = 0;
	image_view_create_info.pNext = nullptr;
	image_view_create_info.image = _image;
	image_view_create_info.viewType = VkImageViewType::VK_IMAGE_VIEW_TYPE_1D;
	image_view_create_info.format = VkFormat::VK_FORMAT_B8G8R8A8_UINT;
	image_view_create_info.components = VkComponentMapping{
		VkComponentSwizzle::VK_COMPONENT_SWIZZLE_A,
		VkComponentSwizzle::VK_COMPONENT_SWIZZLE_R,
		VkComponentSwizzle::VK_COMPONENT_SWIZZLE_G,
		VkComponentSwizzle::VK_COMPONENT_SWIZZLE_B
	};
	image_view_create_info.subresourceRange = subresouce_range;

	SUCCESS(vkCreateImageView(_device, &image_view_create_info, nullptr, &_image_view));
}

void Image::BindMemory()
{
	VkMemoryRequirements memory_requirements;
	vkGetImageMemoryRequirements(_device, _image, &memory_requirements);

	VkDeviceMemory memory;
	vkBindImageMemory(_device, _image, memory, 0);
}