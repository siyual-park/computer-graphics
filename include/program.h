#ifndef OPENGLBOILERPLATE_PROGRAM_H
#define OPENGLBOILERPLATE_PROGRAM_H

#include <glm/glm.hpp>

#include "base-object.h"
#include "shader.h"

namespace gl {

    class Program : public BaseObject {
    public:
        Program();
        ~Program();

        template <unsigned int T>
        Program& attach(Shader<T>& shader);

        void link();
        void use();

        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;

        void setVec2(const std::string &name, const glm::vec2 &value) const;
        void setVec3(const std::string &name, const glm::vec3 &value) const;
        void setVec4(const std::string &name, const glm::vec4 &value) const;
        void setMat2(const std::string &name, const glm::mat2 &mat) const;
        void setMat3(const std::string &name, const glm::mat3 &mat) const;
        void setMat4(const std::string &name, const glm::mat4 &mat) const;
    };
}

#include "program-inc.h"

#endif //OPENGLBOILERPLATE_PROGRAM_H
