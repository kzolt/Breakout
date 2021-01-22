#include "bkout.h"

#define FT_FREETYPE_H
#include "ft2build.h"

#include "Label.h"

namespace Breakout {

	Label::Label(const std::string& text, const glm::vec3& position, const glm::vec4& color)
		: Entity("Label", position, { 5.0f, 5.0f }, color), m_Text(text)
	{

	}

	Label::~Label()
	{

	}

}