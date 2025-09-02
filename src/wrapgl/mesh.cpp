#include "mesh.h"

#include <GL/glew.h>

#include "util.h"
#include "vertex_layout.h"

namespace wgl {

Mesh::Mesh() : vao_(0), vbo_(0), ebo_(0) { }

Mesh::Mesh(
                VertexLayout layout,
                const std::vector<float> &vertices,
                const std::vector<unsigned int> &indices,
                bool dynamic
                ) 
        : vertex_count_(vertices.size()), index_count_(indices.size()),
        layout_(layout), dynamic_(dynamic)
{
        glGenVertexArrays(1, &vao_);
        
        glGenBuffers(1, &vbo_);
        glGenBuffers(1, &ebo_);

        glBindVertexArray(vao_);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);

        glBufferData(GL_ARRAY_BUFFER,
                     vertex_count_ * sizeof(float),
                     vertices.data(),
                     dynamic_ ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     index_count_ * sizeof(unsigned int),
                     indices.data(),
                     GL_STATIC_DRAW);

        // We need to tell the GPU how to render the vertices using the
        // provided layout.
        const auto attributes = layout.GetAttributes();
        for (const auto attr : attributes) {
                glVertexAttribPointer(
                        attr.idx,
                        attr.n_components,
                        attr.data_type,
                        attr.normalized,
                        layout.GetStride(),
                        (void*) attr.offset
                );

                glEnableVertexAttribArray(attr.idx);
        }

        // Unbind VAO
        glBindVertexArray(0);

        assert(glGetError() == GL_NO_ERROR);
}

Mesh::~Mesh()
{
        glDeleteVertexArrays(1, &vao_);
        glDeleteBuffers(1, &vbo_);
        glDeleteBuffers(1, &ebo_);

        assert(glGetError() == GL_NO_ERROR);
}

void Mesh::Draw(const Renderer &renderer) const
{
        renderer.Draw(vao_, index_count_); 
}

void Mesh::UpdateVertexBuffer(const std::vector<float> &new_vertices) const
{
        glBindVertexArray(vao_);

        glBufferData(GL_ARRAY_BUFFER,
                     vertex_count_ * sizeof(float),
                     new_vertices.data(),
                     dynamic_ ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

        glBindVertexArray(0);
}

} // namespace wgl

