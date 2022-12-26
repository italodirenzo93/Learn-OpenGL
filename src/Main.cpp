#include "CommonInclude.h"

#include "Camera.h"
#include "Shader.h"
#include "scenes/Scene.h"
#include "scenes/LightingScene.h"

constexpr int WIDTH = 1024;
constexpr int HEIGHT = 720;

float deltaTime = 0.0f;
float lastFrameTime = 0.0f;

// Camera
float cameraSpeed = 6.0f;
std::shared_ptr<Camera> camera = nullptr;

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	if (camera == nullptr)
		return;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera->position += cameraSpeed * camera->getForwardVector() * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera->position -= cameraSpeed * camera->getForwardVector() * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera->position -= glm::normalize(glm::cross(camera->getForwardVector(), camera->getUpVector())) * cameraSpeed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera->position += glm::normalize(glm::cross(camera->getForwardVector(), camera->getUpVector())) * cameraSpeed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		camera->position -= cameraSpeed * camera->getUpVector() * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		camera->position += cameraSpeed * camera->getUpVector() * deltaTime;
	}
}

void scrollCallback(GLFWwindow *window, double xOffset, double yOffset)
{
	if (camera != nullptr)
	{
		camera->fieldOfView = glm::clamp(camera->fieldOfView - float(yOffset), 1.0f, 45.0f);
	}
}

float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool bIsFirstMouse = true;

void mouseCallback(GLFWwindow *window, double xPos, double yPos)
{
	if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL)
		return;

	if (bIsFirstMouse)
	{
		lastX = float(xPos);
		lastY = float(yPos);
		bIsFirstMouse = false;
	}

	float xOffset = float(xPos) - lastX;
	float yOffset = lastY - float(yPos);
	lastX = float(xPos);
	lastY = float(yPos);

	const float sensitivity = 0.1f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	float pitch = camera->getPitch();
	float yaw = camera->getYaw();

	camera->setYaw(yaw + xOffset);
	camera->setPitch(glm::clamp(pitch + yOffset, -89.0f, 89.0f));
}

int main(void)
{
	GLFWwindow *window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#ifndef NDEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// Hide the mouse cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// GLFW callbacks
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetCursorPosCallback(window, mouseCallback);

	/* Initialize GLAD */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return -1;

	// Print OpenGL context information
	std::cout << "OpenGL Context Version: " << glGetString(GL_VERSION) << std::endl
			  << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl
			  << "GPU Vendor: " << glGetString(GL_VENDOR) << std::endl
			  << "GPU Model: " << glGetString(GL_RENDERER) << std::endl;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	/* Initialize ImGui */
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");

	camera = std::make_shared<Camera>(float(WIDTH / HEIGHT), glm::vec3(0.0f, 0.0f, 3.0f));
	// std::unique_ptr<Scene> scene(new BasicScene(camera));
	std::unique_ptr<Scene> scene(new LightingScene(camera));

	lastFrameTime = float(glfwGetTime());

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		float now = float(glfwGetTime());
		deltaTime = now - lastFrameTime;
		lastFrameTime = now;

		/* ImGui Frame */
		// ImGui_ImplOpenGL3_NewFrame();
		// ImGui_ImplGlfw_NewFrame();
		// ImGui::NewFrame();
		// ImGui::ShowDemoWindow();
		// ImGui::Render();

		/* Render here */
		scene->render(deltaTime);

		/* ImGui Render */
		// ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	scene.reset();

	glfwTerminate();
	return 0;
}
