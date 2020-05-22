#include <iostream>

#include "pch.h"

#include "GameObject.h"
#include "GraphicDevice.h"
#include "CubeObject.h"
#include "Camera.h"


using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void update(GLFWwindow* window);
void render();
void init();

// Screen dimansion
unsigned int width = 1920, height = 1080;

// App globals
GraphicDevice device;
vector<GameObject*> objects;
Camera* camera;


int main(int argc, char** argv)
{

    // Initializing window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    init();

    while (!glfwWindowShouldClose(window))
    {
        update(window);

        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void init()
{

    device.SetupDevice();
    camera = new Camera(width, height);

    auto cube = new CubeObject(&device);
    cube->SetPosition(glm::vec3(5, 5, 5));
    objects.push_back(cube);
    cube = new CubeObject(&device);
    cube->SetPosition(glm::vec3(0, 0, -6));
    objects.push_back(cube);



    camera->Setup();

    for (auto object = objects.begin(); object != objects.end(); object++)
    {
        (*object)->Render();
    }
}

void update(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    camera->Update(window);
    for (auto object = objects.begin(); object != objects.end(); object++)
    {
        (*object)->Update(window);
    }
}

void render()
{
    unsigned int projLoc = glGetUniformLocation(device.GetShader()->ID, "projection");
    unsigned int viewLoc = glGetUniformLocation(device.GetShader()->ID, "view");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera->GetProjectionMatrix()));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    device.Render(&objects);
    
}

void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{   
    glViewport(0, 0, w, h);
    camera->SetViewPortSize(w, h, true);
    width = w;
    height = h;
}