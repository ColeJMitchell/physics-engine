#include "material.h"
#include "glm/glm.hpp"

class PhysicsObject
{
    public:
        enum PhysicsObjectType
        {
            Cube,
            Sphere,
            Prism
        };

        PhysicsObject(Material material, PhysicsObjectType objectType, 
                      float xScale, float yScale, float zScale,
                      float startingXPos, float startingYPos, float startingZPos,
                      float startingXRotation, float startingYRotation, float startingZRotation, float radians)
                      :m_Material(&material), m_ObjectType(objectType), 
                       m_XScale(xScale), m_YScale(yScale), m_ZScale(zScale),
                       m_StartingXPos(startingXPos), m_StartingYPos(startingYPos), m_StartingZPos(startingZPos),
                       m_StartingXRotation(startingXRotation), m_StartingYRotation(startingYRotation), m_StartingZRotation(startingZRotation), m_Radians(radians){}

        ~PhysicsObject(){ delete m_Material; }

    private:
        Material* m_Material;
        PhysicsObjectType m_ObjectType;
        float m_XScale;
        float m_YScale;
        float m_ZScale;
        float m_StartingXPos;
        float m_StartingYPos;
        float m_StartingZPos;
        float m_StartingXRotation;
        float m_StartingYRotation;
        float m_StartingZRotation;
        float m_Radians;
};