#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "vertexbuffer.h"
#include "vertexarray.h"
#include "indexbuffer.h"
#include "shaders.h"
#include "debugging.h"

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
    
    float vertices[] = 
    {
        -0.5f, -0.5f,
         0.5f,  -0.5f,
         0.5f, 0.5f,
         -0.5f, 0.5f,
    };

    unsigned int indices[] = 
    {
        0, 1, 2, 
        2, 3, 0  
    };
    
    std::string vertexShader = Shaders::readShader("../shaders/vertex.glsl");
    std::string fragmentShader = Shaders::readShader("../shaders/fragment.glsl");
    unsigned int shaderProgram = Shaders::createShaders(vertexShader, fragmentShader);

    if (shaderProgram == 0) 
    {
        std::cerr << "Failed to create shader program" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
    
    VertexArray vertexArray;
    VertexBuffer vertexBuffer(vertices, (sizeof(vertices) / sizeof(vertices[0])));  
    vertexArray.addBufferElement(GL_FLOAT, 2);
    vertexArray.processBufferLayout();
    IndexBuffer indexBuffer(indices, sizeof(indices) * sizeof(indices[0]));
    
    glUseProgram(shaderProgram);

    int location = glGetUniformLocation(shaderProgram, "u_Color");
    glUniform4f(location, 1.0f, 1.0f, 1.0f, 1.0f); 
    
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    //cleanup
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}