#include "renderer.h"

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

    VertexBuffer vertexBuffer(vertices, (sizeof(vertices) / sizeof(vertices[0])));  
    VertexArray vertexArray;
    vertexArray.addBufferElement(GL_FLOAT, 2);
    vertexArray.processBufferLayout();
    IndexBuffer indexBuffer(indices, sizeof(indices) / sizeof(indices[0]));


    Shaders shaders("../shaders/vertex.glsl", "../shaders/fragment.glsl");
    unsigned int shaderProgram = shaders.getShaderProgram();

    if (shaderProgram == 0) 
    {
        std::cerr << "Failed to create shader program" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    glUseProgram(shaderProgram);
    int location = glGetUniformLocation(shaderProgram, "u_Color");
    glUniform4f(location, 1.0f, 1.0f, 1.0f, 1.0f); 
    
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, nullptr);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    //cleanup
    vertexArray.unbind();
    vertexBuffer.unbind();
    indexBuffer.unbind();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}