#pragma once
#include "common.h"

class Buffers
{
public:
	Buffers(VkDevice device);
	~Buffers();

	static Buffers* Create(VkDevice device) {
		return new Buffers(device);
	}

	void CreateBuffer();
private:
	VkDevice _device;
	VkBuffer _buffer;
};
