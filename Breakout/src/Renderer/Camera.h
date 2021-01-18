#pragma once

namespace Breakout {

	class Camera
	{
	public:
		Camera() = default;
		Camera(const glm::mat4& projectionMatrix);
		~Camera();

		void SetProjectionMatrix(const glm::mat4& projectionMatrix) { m_ProjectionMatrix = projectionMatrix; }
		void SetViewportSize(uint32_t width, uint32_t height) { m_ViewportWidth = width; m_ViewportHeight = height; }

		inline const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; }

		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		inline glm::mat4 GetViewProjection() const { return m_ProjectionMatrix * m_ViewMatrix; }

		void UpdateCameraView();

	private:
		void RecalculateViewMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };

		uint32_t m_ViewportWidth = 1280, m_ViewportHeight = 720;
	};

}