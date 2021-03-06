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

	///<The buffer is not yet fully usable because
	///<it first needs to be backed with memory
	void CreateBuffer();

	void CreateBufferView();

	void BindMemory();
private:
	VkDevice _device;
	VkBuffer _buffer;
	VkBufferView _buffer_view;
};
