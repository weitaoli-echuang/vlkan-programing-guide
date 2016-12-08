#include <iostream>
#include "../base/Render.h"

int main() {
	Render* render = Render::Create();
	render->Init();

	return 0;
}