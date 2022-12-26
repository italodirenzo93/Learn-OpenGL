#ifndef COMMONINCLUDE_H
#define COMMONINCLUDE_H

// Library headers
#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>

// STL headers
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#define NON_COPYABLE_CLASS(className)      \
	className(const className &) = delete; \
	void operator=(const className &) = delete;

#define NON_MOVABLE_CLASS(className) \
	className(className &&) = delete;

#endif
