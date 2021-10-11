#include "mesh.h"

#include <GL/gl3w.h>
#include "cast.h"

gl::Mesh::Mesh(std::string &name, std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, std::vector<Texture> &textures): name{name}, vertices{vertices}, indices{indices}, textures{textures} {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, getGLsizeiptr(vertices.size() * sizeof(Vertex)), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, getGLsizeiptr(indices.size() * sizeof(unsigned int)), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, tex_coords)));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, tangent)));

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, bitangent)));

    glEnableVertexAttribArray(5);
    glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, bone_ids)));


    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, weights)));
    glBindVertexArray(0);
}

gl::Mesh::Mesh(gl::Mesh &&other) noexcept {
    VAO = other.VAO;
    VBO = other.VBO;
    EBO = other.EBO;

    name = std::move(other.name);

    vertices = std::move(other.vertices);
    indices = std::move(other.indices);
    textures = std::move(other.textures);

    other.EBO = 0;
    other.VBO = 0;
    other.VAO = 0;
}

gl::Mesh::~Mesh() {
    if (EBO != 0) {
        glDeleteBuffers(1, &EBO);
    }
    if (VBO != 0) {
        glDeleteBuffers(1, &VBO);
    }
    if (VAO != 0) {
        glDeleteBuffers(1, &VAO);
    }
}

void gl::Mesh::draw(gl::Program &program) {
    unsigned int diffuse_nr = 1;
    unsigned int specular_nr = 1;
    unsigned int normal_nr = 1;
    unsigned int height_nr = 1;

    for (unsigned int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);

        std::string number;
        std::string name = this->name + "_" + textures[i].type;
        if (textures[i].type == "texture_diffuse")
            number = std::to_string(diffuse_nr++);
        else if (textures[i].type == "texture_specular")
            number = std::to_string(specular_nr++);
        else if (textures[i].type == "texture_normal")
            number = std::to_string(normal_nr++);
        else if (textures[i].type == "texture_height")
            number = std::to_string(height_nr++);

        program.setInt(name + number, getGLint(i));

        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, getGLsizei(indices.size()), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}
