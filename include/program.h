//
// Created by Kakao_Ent on 2021/10/10.
//

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
    };
}


#endif //OPENGLBOILERPLATE_PROGRAM_H
