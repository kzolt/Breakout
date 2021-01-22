#pragma once

#include <glm/glm.hpp>

namespace Breakout {

	class Label;
	class Texture;

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
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, std::shared_ptr<Texture> texture, const glm::vec4& tintColor = glm::vec4(1.0f), float tilingFactor = 1.0f);
		static void DrawLabel(const Label& label);

	private:
		static void FlushAndReset();

	};

}