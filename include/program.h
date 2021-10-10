#ifndef OPENGLBOILERPLATE_PROGRAM_H
#define OPENGLBOILERPLATE_PROGRAM_H

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
        void unuse();
    };
}

#include "program-inc.h"

#endif //OPENGLBOILERPLATE_PROGRAM_H
