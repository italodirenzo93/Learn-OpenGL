#ifndef BUFFER_H
#define BUFFER_H

#include "CommonInclude.h"

template <typename T>
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
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, static_cast<uint32_t>(sizeof(T) * data.size()), reinterpret_cast<const void *>(data.data()), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void bind() const { glBindBuffer(GL_ARRAY_BUFFER, ID); }
	void unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

private:
	uint32_t ID;
};

#endif
