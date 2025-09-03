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
                    // #EAEAEA
                    return glm::vec3(234.0f/255.0f, 234.0f/255.0f, 234.0f/255.0f); 

                case PETG: 
                    // #000000
                    return glm::vec3(192.0f/255.0f, 224.0f/255.0f, 255.0f/255.0f); 

                default:
                    return glm::vec3(1.0f, 1.0f, 1.0f); // fallback = white
    }
}


        private:
            MaterialType m_Material;
};