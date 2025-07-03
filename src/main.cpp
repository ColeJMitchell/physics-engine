#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
int main() 
{
    if(!glfwInit()) 
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //check that glfw window works
    GLFWwindow* window = glfwCreateWindow(800, 600, "Physics Engine", nullptr, nullptr);
    if(!window) 
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) 
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    float vertices[] = {
        -0.5f, -0.5f, 
         0.5f, -0.5f,
         0.0f,  0.5f,
    }; 
    unsigned int triangle;
    glGenBuffers(1, &triangle);
    glBindBuffer(GL_ARRAY_BUFFER, triangle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    
    while(!glfwWindowShouldClose(window)) 
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Destroy the window once the simulation is done
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
    
}
