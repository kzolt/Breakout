#pragma once

#include "Buffer.h"

namespace Breakout {

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind();

		void AddVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer);
		void AddIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer);

		inline std::shared_ptr<IndexBuffer> GetIndexBuffer() { return m_IndexBuffer; }
		inline const std::vector<std::shared_ptr<VertexBuffer>> &GetVertexBuffers() { return m_VertexBuffers; }

	private:
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;

		uint32_t m_RendererID;
		uint32_t m_VertexBufferIndex = 0;
	};

}