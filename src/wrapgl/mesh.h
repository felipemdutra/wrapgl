#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>

#include <vector>

#include "renderer.h"
#include "vertex_layout.h"

namespace wgl {

class Mesh {
private:
        GLuint vao_, vbo_, ebo_;
        unsigned int vertex_count_, index_count_;

        VertexLayout layout;

public:
        Mesh();
        Mesh(VertexLayout layout, const std::vector<float>& vertices,
                        const std::vector<unsigned int> &indices);

        ~Mesh();

        // @brief Draws the mesh with the active shader in the renderer.
        //
        // @param renderer The renderer to draw the mesh with.
        void Draw(const Renderer &renderer) const;
};

} // namespace wgl

#endif

