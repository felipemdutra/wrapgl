#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>

#include <glm/ext/vector_float3.hpp>
#include <vector>

#include "renderer.h"
#include "vertex_layout.h"

namespace wgl {

class Mesh {
private:
        GLuint vao_, vbo_, ebo_;
        unsigned int vertex_count_, index_count_;

        VertexLayout layout_;

        bool dynamic_;

public:
        Mesh();
        Mesh(VertexLayout layout, const std::vector<float> &vertices,
                        const std::vector<unsigned int> &indices, bool dynamic);
        ~Mesh();

        // @brief Draws the mesh with the active shader in the renderer.
        //
        // @param renderer The renderer to draw the mesh with.
        void Draw(const Renderer &renderer) const;

        void UpdateVertexBuffer(const std::vector<float> &new_vertices) const;
};

} // namespace wgl

#endif

