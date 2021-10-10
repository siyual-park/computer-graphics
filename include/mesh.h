#ifndef OPENGLBOILERPLATE_MESH_H
#define OPENGLBOILERPLATE_MESH_H

#include <string>
#include <vector>

#include "drawable.h"

namespace gl {

#define MAX_BONE_INFLUENCE 4

    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 tex_coords;
        glm::vec3 tangent;
        glm::vec3 bitangent;

        int bone_ids[MAX_BONE_INFLUENCE];
        float weights[MAX_BONE_INFLUENCE];
    };

    struct Texture {
        unsigned int id;
        std::string type;
        std::string path;
    };

    class Mesh: public Drawable {
    public:
        Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, std::vector<Texture> &textures);
        virtual ~Mesh();

        void draw(Program &program) override;

        std::vector<Vertex>       vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture>      textures;
        unsigned int VAO{};

    protected:
        unsigned int VBO{}, EBO{};
    };
}

#endif //OPENGLBOILERPLATE_MESH_H
