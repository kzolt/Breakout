#pragma once

#include "Renderer/Renderer.h"

namespace Breakout {

	class Scene
	{
	public:
		Scene();
		~Scene();

		void OnUpdate();
		void OnRender();

	private:
		Renderer m_Renderer;
	};

}