#ifndef COMMONINCLUDE_H
#define COMMONINCLUDE_H

#define NON_COPYABLE_CLASS(className)      \
	className(const className &) = delete; \
	void operator=(const className &) = delete;

#define NON_MOVABLE_CLASS(className) \
	className(className &&) = delete;

#include <glm/glm.hpp>

#endif
