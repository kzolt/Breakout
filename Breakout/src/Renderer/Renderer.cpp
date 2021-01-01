#include "bkout.h"

#include <glad/glad.h>
#include "Renderer.h"

namespace Breakout {

	Renderer::Renderer()
	{

	}

	Renderer::~Renderer()
	{

	}

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}

}