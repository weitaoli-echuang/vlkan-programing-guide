#pragma once
#include "common.h"

class Image
{
public:
	Image(VkDevice);
	~Image();

	static Image* Create(VkDevice *device)
	{
		return new Image(*device);
	}

	void CreateImage();

	void CreateImageView();

	void BindMemory();
private:
	VkDevice _device;
	VkImage _image;
	VkImageSubresource _subresource;
	VkSubresourceLayout _layout;
	VkImageView _image_view;
};
