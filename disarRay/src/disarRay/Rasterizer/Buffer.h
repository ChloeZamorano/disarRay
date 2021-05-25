#pragma once

#include "DrayIntern.h"

namespace Dray
{
	enum class ShaderDataType : u8
	{
		None = 0,
		Int, Int2, Int3, Int4,
		Uint, Uint2, Uint3, Uint4,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
	};

	static u32 ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Int:
		case ShaderDataType::Uint:
		case ShaderDataType::Float:
			return  4;

		case ShaderDataType::Int2:
		case ShaderDataType::Uint2:
		case ShaderDataType::Float2:
			return  8;

		case ShaderDataType::Int3:
		case ShaderDataType::Uint3:
		case ShaderDataType::Float3:
			return 12;

		case ShaderDataType::Int4:
		case ShaderDataType::Uint4:
		case ShaderDataType::Float4:
			return 16;

		case ShaderDataType::Mat3:
			return 36;

		case ShaderDataType::Mat4:
			return 64;

		default:
			DRAY_ENGINE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	}

	struct DRAY_API VertexElement
	{
		str8 Name;
		ShaderDataType Type;
		u32 Size;
		u32 Offset;
		bool Normalized;

		VertexElement() {}
		VertexElement(ShaderDataType type, const str8& name, bool normalized = false) :
			Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized) {}

		u32 GetComponentCount() const
		{
			switch (Type)
			{
			case ShaderDataType::Int:
			case ShaderDataType::Uint:
			case ShaderDataType::Float:
				return 1;

			case ShaderDataType::Int2:
			case ShaderDataType::Uint2:
			case ShaderDataType::Float2:
				return 2;

			case ShaderDataType::Int3:
			case ShaderDataType::Uint3:
			case ShaderDataType::Float3:
				return 3;

			case ShaderDataType::Int4:
			case ShaderDataType::Uint4:
			case ShaderDataType::Float4:
				return 4;

			case ShaderDataType::Mat3:
				return 9;

			case ShaderDataType::Mat4:
				return 16;

			default:
				DRAY_ENGINE_ASSERT(false, "Unknown ShaderDataType!");
				return 0;
			}
		}
	};

	class DRAY_API VertexLayout
	{
	public:
		VertexLayout() {}
		VertexLayout(const std::initializer_list<VertexElement>& elements) :
			m_Elements(elements)
		{
			ComputeOffsetsAndStride();
		}

		inline u32 GetStride() const { return m_Stride; }
		inline const std::vector<VertexElement>& GetElements() { return m_Elements; }

		std::vector<VertexElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<VertexElement>::iterator end() { return m_Elements.end(); }

	private:
		void ComputeOffsetsAndStride()
		{
			u32 offset = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
			}
			m_Stride = offset;
		}

		std::vector<VertexElement> m_Elements;
		u32 m_Stride = 0;
	};

	class DRAY_API VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual VertexLayout& GetLayout() = 0;
		virtual void SetLayout(VertexLayout& layout) = 0;

		static VertexBuffer* Create(f32* verts, u32 size);
	};

	class DRAY_API IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual u32 GetCount() const = 0;

		static IndexBuffer* Create(u32* indices, u32 count);
	};
}
