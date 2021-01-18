#include "bkout.h"

#include <glad/glad.h>
#include "VertexArray.h"

namespace Breakout {

	/////////////////////////////////////////////////////
	// Vertex Array Helper Methods
	/////////////////////////////////////////////////////

	static GLenum ShaderDataTypeToGLType(ShaderDataType type)
	{
		switch (type)
		{
		case Breakout::ShaderDataType::Float:		return GL_FLOAT;
		case Breakout::ShaderDataType::Float2:		return GL_FLOAT;
		case Breakout::ShaderDataType::Float3:		return GL_FLOAT;
		case Breakout::ShaderDataType::Float4:		return GL_FLOAT;
		case Breakout::ShaderDataType::Mat3:		return GL_FLOAT;
		case Breakout::ShaderDataType::Mat4:		return GL_FLOAT;
		}

		ASSERT(false, "Unkown Shader Data Type!");
		return 0;
	}

	/////////////////////////////////////////////////////
	// Vertex Array
	/////////////////////////////////////////////////////

	VertexArray::VertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(m_RendererID);
	}

	void VertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer)
	{
		ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!");

		Bind();
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			auto glBaseType = ShaderDataTypeToGLType(element.Type);
			glEnableVertexAttribArray(m_VertexBufferIndex);
			glVertexAttribPointer(m_VertexBufferIndex, element.GetComponentCount(), glBaseType, element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);
			m_VertexBufferIndex++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void VertexArray::SetIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer)
	{
		Bind();
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}