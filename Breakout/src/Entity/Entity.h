#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Breakout {

	class Entity
	{
	public:
		Entity(const std::string& debugName, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
			: m_DebugName(debugName), m_Position(position), m_Size(size), m_Color(color) {}

		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline glm::vec3& GetPosition() { return m_Position; }

		inline const glm::vec2& GetSize() const { return m_Size; }
		inline glm::vec2& GetSize() { return m_Size; }
		
		inline const glm::vec4& GetColor() const { return m_Color; }
		inline glm::vec4& GetColor() { return m_Color; }

	private:
		std::string m_DebugName;

		glm::vec3 m_Position;
		glm::vec2 m_Size;
		glm::vec4 m_Color;
	};

}