#ifndef OPENGLBOILERPLATE_MODEL_H
#define OPENGLBOILERPLATE_MODEL_H

#include <string>
#include <vector>
#include <assimp/scene.h>

#include "drawable.h"
#include "mesh.h"

namespace gl {
    class Model: public Drawable {
    public:
        explicit Model(std::string &name, std::string &path);
        explicit Model(std::string &name, std::string &&path);

        explicit Model(std::string &&name, std::string &path);
        explicit Model(std::string &&name, std::string &&path);

        ~Model();

        void draw(Program &program) override;

        std::string name;

        glm::vec3 translation = glm::vec3(0.0, 0.0, 0.0);
        glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);

        float angle = glm::radians(0.0f);
        glm::vec3 rotate_axis = glm::vec3(1.0f, 1.0f, 1.0f);
    protected:
        std::vector<Texture> textures_loaded;
        std::vector<Mesh> meshes;
        std::string directory;

        void init(std::string &path);

        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string &&type_name);
    };
}

#endif //OPENGLBOILERPLATE_MODEL_H
