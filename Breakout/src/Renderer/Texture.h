#pragma once

namespace Breakout {

	class Texture
	{
	public:
		Texture(const std::string& path);
		~Texture();

		inline uint32_t GetWidth() const { return m_Width; }
		inline uint32_t GetHeight() const { return m_Height; }

		void Bind(uint32_t slot = 0) const;

		bool operator==(const Texture& other)
		{
			return m_RendererID == other.m_RendererID;
		}

	private:
		uint32_t m_RendererID;
		uint32_t m_Width, m_Height;

		std::string m_Path;
	};

}