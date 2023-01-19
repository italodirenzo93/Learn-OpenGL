#ifndef VERTEX_ARRAY_LAYOUT_H
#define VERTEX_ARRAY_LAYOUT_H

#include "CommonInclude.h"
#include "Buffer.h"

enum LayoutSemantic
{
	POSITION,
	COLOR,
	TEXCOORD,
	NORMAL
};

struct LayoutBinding
{
	LayoutSemantic semantic;
	unsigned int size;
	unsigned int type;
	bool normalized;

	bool operator== (const LayoutBinding& other) const
	{
		return semantic == other.semantic && size == other.size
			&& type == other.type && normalized == other.normalized;
	}
};

class VertexArrayLayout
{
public:
	VertexArrayLayout();
	VertexArrayLayout(const VertexArrayLayout& other);
	VertexArrayLayout(VertexArrayLayout&& other) noexcept;
	VertexArrayLayout(std::initializer_list<LayoutBinding> initializer);
	~VertexArrayLayout();

	void bind() const { glBindVertexArray(m_vertexArrayID); }
	void unbind() const { glBindVertexArray(0); }

private:
	uint32_t m_vertexArrayID;
	std::vector<LayoutBinding> m_layoutBindings;

public:
	VertexArrayLayout& addBinding(const LayoutBinding& binding);

	template <typename Vertex>
	void mapToBuffer(const VertexBuffer<Vertex>& vertexBuffer) const
	{
		vertexBuffer.bind();
		bind();

		size_t offset = 0;

		for (auto& binding : m_layoutBindings)
		{
			auto iter = Bindings.find(binding.semantic);
			if (iter == Bindings.end()) continue;

			unsigned int bindingPoint = iter->second;

			// TODO: this is a hack. this value has to match the size in bytes of each
			//		 scalar value contained within the vertex struct. For now, only floats are ever used
			//		 but this should be able to accomodate for other datatypes.
			auto componentSize = sizeof(float);

			glVertexAttribPointer(bindingPoint, binding.size, binding.type, binding.normalized, sizeof(Vertex), reinterpret_cast<const void*>(offset * componentSize));
			glEnableVertexAttribArray(bindingPoint);

			offset += binding.size;
		}

		unbind();
		vertexBuffer.unbind();
	}

public:
	VertexArrayLayout& operator= (const VertexArrayLayout& other);
	VertexArrayLayout& operator= (VertexArrayLayout&& other) noexcept;

private:
	static const std::map<LayoutSemantic, unsigned int> Bindings;
};

#endif
