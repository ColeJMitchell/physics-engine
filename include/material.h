#include <glm/glm.hpp>

class Material
{
    public:
        enum MaterialType
        {
            STEEL,
            ALUMINIUM,
            COPPER,
            PLA,
            PETG
        };

        Material(MaterialType material)
        {
            m_Material = material;
        }

        glm::vec3 getMaterialColor()
        {
            switch (m_Material)
            {
                case STEEL:
                    // #7C7C7C
                    return glm::vec3(124.0f/255.0f, 124.0f/255.0f, 124.0f/255.0f); 

                case ALUMINIUM:
                    // #D9D9D9
                    return glm::vec3(217.0f/255.0f, 217.0f/255.0f, 217.0f/255.0f); 

                case COPPER:
                    // #B87333
                    return glm::vec3(184.0f/255.0f, 115.0f/255.0f, 51.0f/255.0f);  

                case PLA:
                    // #FF0000
                    return glm::vec3(255.0f, 0.0f, 0.0f); 

                case PETG: 
                    // #000000
                    return glm::vec3(0.0f, 0.0f, 0.0f); 

                default:
                    // #FFFFFF
                    return glm::vec3(1.0f, 1.0f, 1.0f); 
            }
        }

        //units are in kg/m^3
        float getMaterialDensity()
        {
            switch (m_Material)
            {
                case STEEL:
                    return 7850.0f;

                case ALUMINIUM:
                    return 2700.0f;

                case COPPER:
                    return 8960.0f;

                case PLA:
                    return 1240.0f;

                case PETG:
                    return 1270.0f;
            }
        }

        private:
            MaterialType m_Material;
};