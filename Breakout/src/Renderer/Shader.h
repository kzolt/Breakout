#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Breakout {

	class Shader
	{
	public:
		Shader(const std::string& filepath);
		~Shader();

		void Bind();

		void SetInt(const std::string& name, int value);
		void SetIntArray(const std::string& name, int* values, uint32_t count);

		void SetFloat(const std::string& name, float value);
		void SetFloat2(const std::string& name, const glm::vec2& value);
		void SetFloat3(const std::string& name, const glm::vec3& value);
		void SetFloat4(const std::string& name, const glm::vec4& value);

		void SetMat3(const std::string& name, const glm::mat3& matrix);
		void SetMat4(const std::string& name, const glm::mat4& matrix);

	private:
		std::optional<std::string> ReadFile(const std::string& filepath);
		std::unordered_map<uint32_t, std::string> PreProcess(const std::string& source);

		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

		GLint GetUniformLocation(const std::string& name) const;

	private:
		uint32_t m_RendererID;
		std::string m_Name;

		mutable std::unordered_map<std::string, GLint> m_UniformLocations;
	};

}