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

// C++ STL headers
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

// C headers
#include <cstdint>

#define NON_COPYABLE_CLASS(className)      \
	className(const className&) = delete; \
	className& operator=(const className&) = delete;

#define NON_MOVABLE_CLASS(className)    \
	className(className&&) = delete;      \
    className& operator=(className&&) = delete;

#define NON_COPYABLE_OR_MOVABLE_CLASS(className)    \
	NON_COPYABLE_CLASS(className)   \
	NON_MOVABLE_CLASS(className)

#endif
