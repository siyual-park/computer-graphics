#ifndef OPENGLBOILERPLATE_SHADER_H
#define OPENGLBOILERPLATE_SHADER_H

#include <string>
#include "base-object.h"

namespace gl {
    template <unsigned int T>
    class Shader : public BaseObject {
    public:
        enum {
            Type = T
        };

        explicit Shader(std::string& path);
        explicit Shader(std::string&& path);
        virtual ~Shader();

        virtual void compile();
        bool isCompiled();

        std::string path;
    protected:
        bool is_compiled{};
    };
}

#include "shader-inc.h"

#endif //OPENGLBOILERPLATE_SHADER_H
