#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "vertexbuffer.h"
#include "debugging.h"

std::string readShader(const std::string& filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open())
    {
        std::cerr << "Could not open file: " << filepath << std::endl;
        return "";
    }
    else
    {
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
}


static unsigned int compileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = new char[length];
        glGetShaderInfoLog(id, length, &length, message);
        std::cerr << "Shader compilation error: " << std::endl;
        std::cerr << message << std::endl;
        delete[] message;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

static unsigned int createShaders(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
    
    //check if shaders compiled successfully
    if (vs == 0 || fs == 0) 
    {
        glDeleteProgram(program);
        return 0;
    }
    
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    int linkStatus;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    if (linkStatus == GL_FALSE) 
    {
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char* message = new char[length];
        glGetProgramInfoLog(program, length, &length, message);
        std::cerr << "Shader linking error: " << std::endl;
        std::cerr << message << std::endl;
        delete[] message;
        glDeleteProgram(program);
        return 0;
    }
    
    glValidateProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

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
    
    std::string vertexShader = readShader("../shaders/vertex.glsl");
    std::string fragmentShader = readShader("../shaders/fragment.glsl");
    
    unsigned int shaderProgram = createShaders(vertexShader, fragmentShader);
    if (shaderProgram == 0) 
    {
        std::cerr << "Failed to create shader program" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
    
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    VertexBuffer vertexBuffer;
    vertexBuffer.createBuffer(vertices, (sizeof(vertices) / sizeof(vertices[0])) );
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
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
    glDeleteVertexArrays(1, &VAO);
    vertexBuffer.deleteBuffer();
    glDeleteBuffers(1, &IBO);
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}