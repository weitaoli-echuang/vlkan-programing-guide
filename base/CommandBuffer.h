#pragma once
#include "common.h"

class CommandBuffer
{
public:
	CommandBuffer();
	~CommandBuffer();

	static CommandBuffer* Create()
	{
		return new CommandBuffer;
	}

	void CommandPool();

	void StartRecordCommand();
	void EndRecordCommand();
	void CopyBuffer();
	void ResetCommand();
	void ResetCommandPool();
	void QueueSubmit();

	VkDevice _device;
	uint32_t _queue_family_index;
	uint32_t _command_count;
	VkCommandPool _command_pool;
	std::vector<VkCommandBuffer> _command_buffers;

private:
};
