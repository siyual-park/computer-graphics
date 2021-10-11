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

        glm::vec3 translation;
        glm::vec3 scale;
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
