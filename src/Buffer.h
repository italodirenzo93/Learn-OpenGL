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

	unsigned int getID() const { return ID; }

	void setData(size_t size, const T *data) const
	{
		if (size == 0 || data == nullptr)
			return;

		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(T), data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void bind() const { glBindBuffer(GL_ARRAY_BUFFER, ID); }
	void unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

private:
	unsigned int ID;
};

#endif
