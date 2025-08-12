#include <GL/glew.h>
#include <string>
#include <iostream>

namespace Debugging 
{
    void debug(std::string &codeBlock)
    {
        GLenum err;
        while ( (err = glGetError()) != GL_NO_ERROR )
        {
            std::cout << "OpenGL error at " << codeBlock << ": " << err << std::endl;
        }
    }
};