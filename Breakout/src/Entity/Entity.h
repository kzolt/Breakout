#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Breakout {

	class Entity
	{
	public:
		Entity(const std::string& debugName, const glm::vec2& position, const glm::vec2& size)
			: m_DebugName(debugName), m_Position(position), m_Size(size) {}

	private:
		std::string m_DebugName;

		glm::vec2 m_Position;
		glm::vec2 m_Size;
	};

}