#ifndef BUFFER_H
#define BUFFER_H

#include "CommonInclude.h"

template <typename T, uint32_t BufferType>
class Buffer
{
public:
	Buffer()
	{
		glGenBuffers(1, &ID);
	}

	~Buffer()
	{
		glDeleteBuffers(1, &ID);
	}

	uint32_t getID() const { return ID; }

	void setData(const std::vector<T> &data) const
	{
		glBindBuffer(BufferType, ID);
		glBufferData(BufferType, static_cast<uint32_t>(sizeof(T) * data.size()), reinterpret_cast<const void *>(data.data()), GL_STATIC_DRAW);
		glBindBuffer(BufferType, 0);
	}

	void setData(const std::initializer_list<T>& initializer) const
	{
		glBindBuffer(BufferType, ID);
		glBufferData(BufferType, static_cast<uint32_t>(sizeof(T) * initializer.size()), initializer.begin(), GL_STATIC_DRAW);
		glBindBuffer(BufferType, 0);
	}

	void bind() const { glBindBuffer(BufferType, ID); }
	void unbind() const { glBindBuffer(BufferType, 0); }

private:
	uint32_t ID;
};

template <typename T>
class ArrayBuffer : public Buffer<T, GL_ARRAY_BUFFER>
{
};

template <typename T>
class ElementBuffer : public Buffer<T, GL_ELEMENT_ARRAY_BUFFER>
{
};

#endif
