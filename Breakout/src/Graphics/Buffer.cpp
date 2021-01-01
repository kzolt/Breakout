#include "bkout.h"

#include <glad/glad.h>
#include "Buffer.h"

namespace Breakout {

	/////////////////////////////////////////////////////
	// Vertex Buffer
	/////////////////////////////////////////////////////

	VertexBuffer::VertexBuffer(void* data, size_t size)
		: m_Size(size)
	{
		glCreateBuffers(1, &m_RendererID);
		glNamedBufferData(m_RendererID, m_Size, data, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void VertexBuffer::SetData(void* data, size_t size, uint32_t offset)
	{
		m_Size = size;
		
		glNamedBufferSubData(m_RendererID, offset, (uint32_t)m_Size, data);
	}

	/////////////////////////////////////////////////////
	// Index Buffer
	/////////////////////////////////////////////////////

	IndexBuffer::IndexBuffer(void* data, size_t size)
	{
		glCreateBuffers(1, &m_RendererID);
		glNamedBufferData(m_RendererID, (uint32_t)m_Size, data, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void IndexBuffer::SetData(void* data, size_t size, uint32_t offset )
	{
		m_Size = size;
		glNamedBufferSubData(m_RendererID, offset, (uint32_t)m_Size, data);
	}


}