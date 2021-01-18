#pragma once

#include <glm/glm.hpp>

namespace Breakout {

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const glm::mat4& viewProj, bool depthTest = true);
		static void EndScene();

		static void Clear();

		// Draw
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

	private:
		static void FlushAndReset();

	};

}