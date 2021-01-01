#pragma once

namespace Breakout {

	/////////////////////////////////////////////////////
	// Shader Types
	/////////////////////////////////////////////////////

	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:		return sizeof(float);
		case ShaderDataType::Float2:	return sizeof(float) * 2;
		case ShaderDataType::Float3:	return sizeof(float) * 3;
		case ShaderDataType::Float4:	return sizeof(float) * 4;
		case ShaderDataType::Mat3:		return sizeof(float) * 3 * 3;
		case ShaderDataType::Mat4:		return sizeof(float) * 4 * 4;
		}

		ASSERT(false, "Invalid Shader Data Type!");
		return 0;
	}

	/////////////////////////////////////////////////////
	// Vertex Buffer Layouts
	/////////////////////////////////////////////////////

	struct BufferElement 
	{
		std::string Name;
		ShaderDataType Type;
		size_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement() = default;
		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized) {}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case ShaderDataType::Float:		return 1;
			case ShaderDataType::Float2:	return 2;
			case ShaderDataType::Float3:	return 3;
			case ShaderDataType::Float4:	return 4;
			case ShaderDataType::Mat3:		return 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4;

			}
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	/////////////////////////////////////////////////////
	// Vertex Buffer
	/////////////////////////////////////////////////////

	class VertexBuffer
	{
	public:
		VertexBuffer(void* data, size_t size);
		~VertexBuffer();

		void Bind();
		
		void SetData(void* data, size_t size, uint32_t offset = 0);

		inline const BufferLayout& GetLayout() const { return m_Layout; }
		void SetLayout(const BufferLayout& layout) { m_Layout = layout; }

	private:
		uint32_t m_RendererID;
		size_t m_Size;
		BufferLayout m_Layout;
	};

	/////////////////////////////////////////////////////
	// Index Buffer
	/////////////////////////////////////////////////////

	class IndexBuffer
	{
	public:
		IndexBuffer(void* data, size_t size);
		~IndexBuffer();

		void Bind();

		void SetData(void* data, size_t size, uint32_t offset = 0);

		inline size_t GetSize() const { return m_Size; }

	private:
		uint32_t m_RendererID;
		size_t m_Size;
	};

}