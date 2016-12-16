#include "CommandBuffer.h"

CommandBuffer::CommandBuffer()
{
}

CommandBuffer::~CommandBuffer()
{
	vkFreeCommandBuffers(_device, _command_pool, _command_buffers.size(), _command_buffers.data());
	vkDestroyCommandPool(_device, _command_pool, nullptr);
}

void CommandBuffer::CommandPool()
{
	VkCommandPoolCreateInfo command_pool_create_info;
	command_pool_create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	command_pool_create_info.pNext = nullptr;

	///<是否临时使用indicates that command
	///<buffers taken from the pool will be short-lived and returned to the pool shortly after use.
	command_pool_create_info.flags = VkCommandPoolCreateFlagBits::VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;

	///<当前commandbuffer自己是否能够被reset or restart
	///<allows
	///<individual command buffers to be reused by resetting them or restarting them. (Don’t worry,
	///<we’ll cover that in a moment.) If this bit is not specified, then only the pool itself can be reset,
	///<which implicitly recycles all of the command buffers allocated from it.
	command_pool_create_info.flags = VkCommandPoolCreateFlagBits::VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
	command_pool_create_info.queueFamilyIndex = _queue_family_index;

	vkCreateCommandPool(_device, &command_pool_create_info, nullptr, &_command_pool);

	VkCommandBufferAllocateInfo command_buffer_allocate_info;
	command_buffer_allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	command_buffer_allocate_info.pNext = nullptr;
	command_buffer_allocate_info.commandPool = _command_pool;
	command_buffer_allocate_info.level = VkCommandBufferLevel::VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	command_buffer_allocate_info.commandBufferCount = _command_count;

	vkAllocateCommandBuffers(_device, &command_buffer_allocate_info, _command_buffers.data());
}

void CommandBuffer::StartRecordCommand()
{
	VkCommandBufferBeginInfo command_buffer_begin_info;
	command_buffer_begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	command_buffer_begin_info.pNext = nullptr;
	command_buffer_begin_info.pInheritanceInfo = nullptr;
	command_buffer_begin_info.flags = VkCommandBufferUsageFlagBits::VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	///<resets it to an initial state
	vkBeginCommandBuffer(_command_buffers.at(0), &command_buffer_begin_info);
}

void CommandBuffer::EndRecordCommand()
{
	vkEndCommandBuffer(_command_buffers.at(0));
}

void CommandBuffer::CopyBuffer()
{
	VkBuffer src_buffer;
	VkBuffer dst_buffer;
	std::vector<VkBufferCopy> buffer_copys;
	buffer_copys.push_back(VkBufferCopy{ 0,0,10 });
	vkCmdCopyBuffer(_command_buffers.at(0), src_buffer, dst_buffer, buffer_copys.size(), buffer_copys.data());
}

void CommandBuffer::ResetCommand()
{
	vkResetCommandBuffer(_command_buffers.at(0), VkCommandBufferResetFlagBits::VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);
}

void CommandBuffer::ResetCommandPool()
{
	vkResetCommandPool(_device, _command_pool, VkCommandPoolResetFlagBits::VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);
}

void CommandBuffer::QueueSubmit()
{
	VkQueue queue;
	uint32_t queue_index = 0;
	vkGetDeviceQueue(_device, _queue_family_index, queue_index, &queue);
	std::vector<VkSubmitInfo> submnit_infos;
	VkSubmitInfo submit_info;
	submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submit_info.pNext = nullptr;
	submit_info.commandBufferCount = _command_buffers.size();
	submit_info.pCommandBuffers = _command_buffers.data();
	submit_info.signalSemaphoreCount = 0;
	submit_info.pSignalSemaphores = nullptr;
	submit_info.waitSemaphoreCount = 0;
	submit_info.pWaitSemaphores = nullptr;
	VkPipelineStageFlags pipeline_stage_flags = VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
	submit_info.pWaitDstStageMask = &pipeline_stage_flags;

	submnit_infos.push_back(submit_info);

	VkFence fence;
	vkQueueSubmit(queue, submnit_infos.size(), submnit_infos.data(), fence);
}