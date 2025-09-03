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

        static void updateCameraXPosition(float xSpeed) 
        { 
            glm::vec3 zDirection = glm::normalize(m_Center - m_Eye);
            glm::vec3 xDirection = glm::normalize(glm::cross(m_Up, zDirection));
            m_Eye += xDirection * xSpeed;
            m_Center += xDirection * xSpeed;
        }

        static void updateCameraYPosition(float ySpeed) 
        { 
            glm::vec3 zDirection = glm::normalize(m_Center - m_Eye);
            glm::vec3 xDirection = glm::normalize(glm::cross(zDirection, m_Up));
            glm::vec3 yDirection = glm::normalize(glm::cross(xDirection, zDirection));

            m_Eye += yDirection * ySpeed;
            m_Center += yDirection * ySpeed;
        }

        static void updateCameraZPosition(float zSpeed) 
        { 
            glm::vec3 zDirection = glm::normalize(m_Center - m_Eye);
            m_Eye += zDirection * zSpeed;
            m_Center += zDirection * zSpeed;
        }

        static void mouseCallback(GLFWwindow* window, double mouseXPos, double mouseYPos)
        {
            if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) 
            { 
                m_PreviousMouseXPos = mouseXPos;
                m_PreviousMouseYPos = mouseYPos;
                return; 
            }

            if (m_FirstMouseCallback)
            {
                m_PreviousMouseXPos = mouseXPos;
                m_PreviousMouseYPos = mouseYPos;
                m_FirstMouseCallback = false;
            }

            float mouseXPosOffset = (mouseXPos - m_PreviousMouseXPos) * m_Sensitivity;
            float mouseYPosOffset = (m_PreviousMouseYPos - mouseYPos) * m_Sensitivity;
            m_PreviousMouseXPos = mouseXPos;
            m_PreviousMouseYPos = mouseYPos;
            
            m_Pitch += mouseYPosOffset;
            m_Yaw += mouseXPosOffset;

            if (m_Pitch > 89.0f) { m_Pitch = 89.0f; }
            if (m_Pitch < -89.0f) { m_Pitch = -89.0f; }

            glm::vec3 mouseDirection;
            mouseDirection.x = cos(glm::radians(m_Pitch)) * cos(glm::radians(m_Yaw));
            mouseDirection.y = sin(glm::radians(m_Pitch));
            mouseDirection.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

            m_Center = m_Eye + glm::normalize(mouseDirection);
        }
        
    private:
        inline static glm::vec3 m_Eye = glm::vec3(0.0f, 0.0f, 5.0f);
        inline static glm::vec3 m_Center = glm::vec3(0.0f, 0.0f, 0.0f);
        inline static glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
        inline static bool m_FirstMouseCallback = true;
        inline static float m_PreviousMouseXPos = 0.0f;
        inline static float m_PreviousMouseYPos = 0.0f;
        inline static float m_Pitch = 0.0f;
        inline static float m_Yaw = -90.0f;
        inline static float m_Sensitivity = .3f;
};