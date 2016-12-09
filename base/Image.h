#pragma once
#include "common.h"

class Image
{
public:
	Image(VkDevice);
	~Image();

	static Image* Create(VkDevice *device)
	{
		return new Image(device);
	}

	void CreateImage();
private:
	VkDevice _device;
	VkImage _image;
};
