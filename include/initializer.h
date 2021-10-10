#ifndef OPENGLBOILERPLATE_INITIALIZER_H
#define OPENGLBOILERPLATE_INITIALIZER_H

namespace gl {
    struct Version {
        int major;
        int minor;
    };

    class Initializer {
    public:
        Initializer(Version& version);
        Initializer(Version&& version);
        virtual ~Initializer();

        void init();

    protected:
        Version version;

        bool inited;
    };
}

#endif //OPENGLBOILERPLATE_INITIALIZER_H
