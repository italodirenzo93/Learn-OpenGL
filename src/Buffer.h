#ifndef BUFFER_H
#define BUFFER_H

#include "CommonInclude.h"

template <typename T, uint32_t BufferType>
class Buffer
{
public:
	Buffer()
	{
		glGenBuffers(1, &m_ID);
	}

	Buffer(const Buffer& other)
	{
		copy(other);
	}

	Buffer(Buffer&& other) noexcept : m_ID(other.m_ID), m_size(other.m_size)
	{
		other.m_ID = 0;
		other.m_size = 0;
	}

	~Buffer()
	{
		glDeleteBuffers(1, &m_ID);
	}

	uint32_t getID() const { return m_ID; }
	uint32_t getSize() const { return m_size; }

	void setData(const std::vector<T> &data)
	{
		glBindBuffer(BufferType, m_ID);
		glBufferData(BufferType, static_cast<uint32_t>(data.size() * sizeof(T)), reinterpret_cast<const void *>(data.data()), GL_STATIC_DRAW);
		glBindBuffer(BufferType, 0);

		m_size = static_cast<uint32_t>(data.size());
	}

	void setData(const std::initializer_list<T>& initializer)
	{
		glBindBuffer(BufferType, m_ID);
		glBufferData(BufferType, static_cast<uint32_t>(initializer.size() * sizeof(T)), initializer.begin(), GL_STATIC_DRAW);
		glBindBuffer(BufferType, 0);

		m_size = static_cast<uint32_t>(initializer.size());
	}

	void bind() const { glBindBuffer(BufferType, m_ID); }
	void unbind() const { glBindBuffer(BufferType, 0); }

private:
	uint32_t m_ID = 0;
	uint32_t m_size = 0;

	void copy(const Buffer& other)
	{
		glGenBuffers(1, &m_ID);
		m_size = other.m_size;

		if (m_size == 0)
			return;

		T* data = new T[m_size];

		// Read the other buffer's data into memory
		glBindBuffer(BufferType, m_ID);
		glGetBufferSubData(BufferType, 0, m_size * sizeof(T), data);

		// Write the data into the new buffer
		glBindBuffer(BufferType, m_ID);
		glBufferData(BufferType, m_size * sizeof(T), data, GL_STATIC_DRAW);

		glBindBuffer(BufferType, 0);

		delete[] data;
	}

public:
	Buffer& operator= (const Buffer& other)
	{
		copy(other);
		return *this;
	}

	Buffer& operator= (Buffer&& other) noexcept
	{
		m_ID = other.m_ID;
		m_size = other.m_size;

		other.m_ID = 0;
		other.m_size = 0;

		return *this;
	}
};

template <typename Vertex>
class VertexBuffer : public Buffer<Vertex, GL_ARRAY_BUFFER>
{
};

class IndexBuffer : public Buffer<uint32_t, GL_ELEMENT_ARRAY_BUFFER>
{
};

#endif
