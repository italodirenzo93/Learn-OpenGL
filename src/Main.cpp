#include "CommonInclude.h"

#include "Camera.h"
#include "scenes/Scene.h"
//#include "scenes/LightingScene.h"
//#include "scenes/MeshLoadingScene.h"
//#include "scenes/MultiCubeScene.h"
//#include "scenes/FramebufferEffectScene.h"
#include "scenes/ModelViewerScene.h"

using namespace std;
namespace fs = std::filesystem;

static constexpr int WIDTH = 1024;
static constexpr int HEIGHT = 720;

float deltaTime = 0.0f;
float lastFrameTime = 0.0f;

// Camera
float cameraSpeed = 6.0f;
std::shared_ptr<Camera> camera = nullptr;
bool bIsFirstMouse = true;
bool bUseCameraControls = true;

void processInput(GLFWwindow *window)
{
    if (bUseCameraControls)
    {
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            bIsFirstMouse = true;
        }

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }

	if (camera == nullptr)
		return;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera->position += cameraSpeed * camera->front * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera->position -= cameraSpeed * camera->front * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera->position -= glm::normalize(glm::cross(camera->front, camera->up)) * cameraSpeed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera->position += glm::normalize(glm::cross(camera->front, camera->up)) * cameraSpeed * deltaTime;
	}

	camera->update();
}

void scrollCallback(GLFWwindow *window, double xOffset, double yOffset)
{
	if (camera != nullptr)
	{
		camera->fieldOfView = glm::clamp(camera->fieldOfView - float(yOffset), 1.0f, 45.0f);
	}

	camera->update();
}

float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;

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

	float pitch = camera->pitch;
	float yaw = camera->yaw;

	camera->yaw = yaw + xOffset;
	camera->pitch = glm::clamp(pitch + yOffset, -89.0f, 89.0f);

	camera->update();
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS && camera != nullptr && key == GLFW_KEY_C)
	{
		std::cout << "Camera position: (" << camera->position.x << "f, " << camera->position.y << "f, " << camera->position.z << "f)" << std::endl;
	}
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);

	camera->aspectRatio = float(width) / float(height);
	camera->update();
}

#ifdef __DEBUG__

void APIENTRY glDebugOutput(GLenum source,
                            GLenum type,
                            unsigned int id,
                            GLenum severity,
                            GLsizei length,
                            const char *message,
                            const void *userParam)
{
    // ignore non-significant error/warning codes
    if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " <<  message << std::endl;

    switch (source)
    {
        case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
    } std::cout << std::endl;

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
        case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
    } std::cout << std::endl;

    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
    } std::cout << std::endl;
    std::cout << std::endl;
}

#endif

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("No model file specified. Exiting...\n");
		return 0;
	}

	const char* pathToModel = argv[1];

	if (!fs::exists(pathToModel))
	{
		printf("Model file at %s does not exist. Exiting...\n", pathToModel);
		return 0;
	}

	GLFWwindow *window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

#ifdef __APPLE__
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#endif
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#ifdef __DEBUG__
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

    if (bUseCameraControls)
    {
        // Hide the mouse cursor
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

	// GLFW callbacks
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	/* Initialize GLAD */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return -1;

	// Print OpenGL context information
	cout << "OpenGL Context Version: " << glGetString(GL_VERSION) << endl
			  << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl
			  << "GPU Vendor: " << glGetString(GL_VENDOR) << endl
			  << "GPU Model: " << glGetString(GL_RENDERER) << endl << endl;

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model)
    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

#ifdef __DEBUG__
    // Configure debug callback if we got a debug context
    int glContextFlags; glGetIntegerv(GL_CONTEXT_FLAGS, &glContextFlags);
    if (glContextFlags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }
#endif

	/* Initialize ImGui */
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");

	camera = make_shared<Camera>(float(WIDTH) / float(HEIGHT), glm::vec3(-0.5f, 0.5f, 9.0), glm::vec3(0.0f, 1.0f, 0.0f));

    std::unique_ptr<Scene> scene;
//    scene = std::make_unique<BasicScene>(camera);
//    scene = std::make_unique<LightingScene>(camera);
    //scene = std::make_unique<MeshLoadingScene>(camera);
    //scene = std::make_unique<MultiCubeScene>(*camera);
	//scene = make_unique<FramebufferEffectScene>(*camera);
	scene = make_unique<ModelViewerScene>(*camera, pathToModel);

	lastFrameTime = float(glfwGetTime());

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		auto now = float(glfwGetTime());
		deltaTime = now - lastFrameTime;
		lastFrameTime = now;

		/* ImGui Frame */
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		// ImGui::ShowDemoWindow();
        scene->renderUi();
		ImGui::Render();

		/* Render here */
		scene->render(deltaTime);

		/* ImGui Render */
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	scene.reset();

	glfwTerminate();
	return 0;
}
