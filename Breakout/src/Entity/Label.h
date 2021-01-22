#pragma once

#include "Entity.h"

namespace Breakout {

	class Label : public Entity
	{
	public:
		Label(const std::string& text, const glm::vec3& position, const glm::vec4& color);
		~Label();

		inline const std::string& GetText() const { return m_Text; }
		inline std::string& GetText() { return m_Text; }

		inline void SetText(const std::string& text) { m_Text = text; }

	private:
		std::string m_Text;
	};

}