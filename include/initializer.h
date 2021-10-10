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
        void load();

    protected:
        Version version;

        bool inited;
        bool loaded;
    };
}

#endif //OPENGLBOILERPLATE_INITIALIZER_H
