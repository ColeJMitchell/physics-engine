#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
    public:
        static glm::mat4 calculateMVP(float xTranslate, float yTranslate, float zTranslate,
                                      float xScale, float yScale, float zScale, 
                                      float xRotate, float yRotate, float zRotate, float radians
                                     )
        {
            glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1200.0f / 900.0f, 0.1f, 100.0f);
            glm::mat4 view = glm::lookAt(m_Eye, m_Center, m_Up);
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(xTranslate, yTranslate, zTranslate)); 
            model = glm::rotate(model, glm::radians(radians), glm::vec3(xRotate, yRotate, zRotate));
            model = glm::scale(model, glm::vec3(xScale, yScale, zScale));
            glm::mat4 mvp = projection * view * model;
            return mvp;
        }

    private:
        inline static glm::vec3 m_Eye = glm::vec3(0.0f, 0.0f, 5.0f);
        inline static glm::vec3 m_Center = glm::vec3(0.0f, 0.0f, 0.0f);
        inline static glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
};