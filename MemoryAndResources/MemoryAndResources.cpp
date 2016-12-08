#include "../base/Render.h"
#include "../base/Buffers.h"

int main() {
	Render* render = Render::Create();
	render->Init();

	Buffers* buffer = Buffers::Create(render->_device);
	buffer->CreateBuffer();

	std::cout << "here" << std::endl;
	return 0;
}