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

        Shader(std::string& path);
        Shader(std::string&& path);
        virtual ~Shader();

        virtual void compile();
        bool isCompiled();

        std::string path;
    protected:
        bool is_compiled{};
    };

    using VertexShader = Shader<GL_VERTEX_SHADER>;
    using FragmentShader = Shader<GL_FRAGMENT_SHADER>;
    using TessellationControlShader = Shader<GL_TESS_CONTROL_SHADER>;
    using TessellationEvaluationShader = Shader<GL_TESS_EVALUATION_SHADER>;
}

#include "shader-inc.h"

#endif //OPENGLBOILERPLATE_SHADER_H
