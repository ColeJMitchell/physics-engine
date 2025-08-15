#include <GL/glew.h>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

class Shaders
{
    public:
        Shaders(std::string vertexShader, std::string fragmentShader);
        ~Shaders();
        std::string readShader(const std::string& filepath);
        unsigned int createShaders(const std::string& vertexShader, const std::string& fragmentShader);

    private:
        unsigned int m_ShaderProgram = 0;
        unsigned int compileShader(unsigned int type, const std::string& source);
};