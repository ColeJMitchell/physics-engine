#include "renderer.h"

Renderer::~Renderer()
{
    m_VBO->unbind();
    m_VAO->unbind();
    m_IBO->unbind();
    delete m_VBO;
    delete m_VAO;
    delete m_IBO;
    delete m_Shaders;
    delete m_Cube;
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

glm::mat4 Renderer::calculateMVP(float xScale, float yScale, float zScale, 
                                 float xRotate, float yRotate, float zRotate, float radians)
{
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3)); 
    glm::mat4 model = glm::mat4(1.0f);
    model = Cube::scale(xScale, yScale, zScale, model);
    model = Cube::rotate(xRotate, yRotate, zRotate, glm::radians(radians), model);
    glm::mat4 mvp = projection * view * model;
    return mvp;
}

int Renderer::setupWindow()
{
    if(!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    m_Window = glfwCreateWindow(800, 600, "Physics Engine", nullptr, nullptr);

    if(!m_Window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(m_Window);
    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwDestroyWindow(m_Window);
        glfwTerminate();
        return -1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //check if the shader did not compile properly in constructor
    if (m_ShaderProgram == 0) 
    {
        std::cerr << "Failed to create shader program" << std::endl;
        glfwDestroyWindow(m_Window);
        glfwTerminate();
        return -1;
    }

    Debugging::debug("Window Setup");
    return 0;
}

void Renderer::initRenderObjects()
{
    m_Cube = new Cube();
    m_VBO = new VertexBuffer(m_Cube->getVertices(), m_Cube->getVertexFloatCount());
    m_VAO = new VertexArray();
    m_IBO = new IndexBuffer(m_Cube->getIndices(), m_Cube->getIndexFloatCount());
    m_Shaders = new Shaders("../shaders/vertex.glsl", "../shaders/fragment.glsl");
    m_VAO->addBufferElement(GL_FLOAT, m_Cube->getVertexStrideCount());
    m_VAO->processBufferLayout();
    m_ShaderProgram = m_Shaders->getShaderProgram();
}

void Renderer::startRenderLoop()
{
    float radians = 0;
    bool radiansIncreasing = true;
    while (!glfwWindowShouldClose(m_Window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        int location = glGetUniformLocation(m_ShaderProgram, "u_MVP");
        
        if (radiansIncreasing) 
        {
            radians += 10;
        } 
        else 
        {
            radians -= 10;
        }

        if (radians >= 360)
        {
            radiansIncreasing = false;
        }
        else if (radians <= 0)
        {
            radiansIncreasing = true;
        }

        glm::mat4 mvp = calculateMVP(2, 1, 1, 0, 1, 0, radians);
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mvp));

        m_VAO->bind();
        glUseProgram(m_ShaderProgram);
        glDrawElements(GL_TRIANGLES, m_Cube->getIndexFloatCount(), GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}
