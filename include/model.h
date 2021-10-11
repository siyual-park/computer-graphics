#ifndef OPENGLBOILERPLATE_MODEL_H
#define OPENGLBOILERPLATE_MODEL_H

#include <string>
#include <vector>
#include <assimp/scene.h>

#include "drawable.h"
#include "mesh.h"

namespace gl {
    class Model: Drawable {
    public:
        explicit Model(std::string &path);

        void draw(Program &program) override;

    protected:
        std::vector<Texture> textures_loaded;
        std::vector<Mesh> meshes;
        std::string directory;

        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string &&type_name);
    };
}

#endif //OPENGLBOILERPLATE_MODEL_H
