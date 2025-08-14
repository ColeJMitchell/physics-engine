#include <GL/glew.h>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

class Shaders
{
    public:
        static unsigned int createShaders(const std::string& vertexShader, const std::string& fragmentShader);
        static std::string readShader(const std::string& filepath);

    private:
        static unsigned int compileShader(unsigned int type, const std::string& source);
};