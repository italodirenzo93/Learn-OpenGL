#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <stb_image.h>

#include <iostream>
#include <fstream>
#include <string>

#include "Shader.h"

std::string ReadShaderSourceFromFile(const char* fileName)
{
    std::ifstream ifs(fileName);
    if (!ifs.is_open())
    {
        std::cout << "Could not open " << fileName << " for reading." << std::endl;
        return "Error";
    }

    std::string code((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

    return code;
}

int main(void)
{
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Initialize GLAD */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return -1;

    /* Vector Math */
    glm::vec3 v1(1.0, 2.0, 3.0);
    glm::vec3 v2(10.0, 11.0, 2.0);
    glm::vec3 v = v1 + v2;
    std::cout << "Vector Result: " << v.x << " " << v.y << " " << v.z << std::endl;

    /* Load an Image */
    int w, h, nrChannels;
    unsigned char *image = stbi_load("./resources/test_image.png", &w, &h, &nrChannels, STBI_default);
    if (!image)
        return -1;
    std::cout << "Width: " << w << " | Height: " << h << " | Channels: " << nrChannels << std::endl;

    /* Initialize ImGui */
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    // VBO
    static const float vertices[] = {
        // positions // colors
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f // top
    };

    unsigned int vboID;
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // VAO
    unsigned int vaoID;
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Shader program("./resources/shaders/basic.vert", "./resources/shaders/basic.frag");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* ImGui Frame */
        //ImGui_ImplOpenGL3_NewFrame();
        //ImGui_ImplGlfw_NewFrame();
        //ImGui::NewFrame();
        //ImGui::ShowDemoWindow();
        //ImGui::Render();

        /* Render here */
        program.use();

        glClearColor(0.0f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vaoID);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);
        glUseProgram(0);

        /* ImGui Render */
        //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}