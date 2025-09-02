#ifndef MESH_FACTORY_H
#define MESH_FACTORY_H

#include <optional>

#include "mesh.h"
#include "vertex_layout.h"

namespace wgl {

class MeshFactory {
public:
        MeshFactory() = delete;

        // @brief Creates a cube mesh using the specified vertex layout.
        static Mesh* GetCube(const VertexLayout &layout, const glm::vec3 *rgb, bool dynamic);
        static Mesh* GetPyramid(const VertexLayout &layout, const glm::vec3 *rgb, bool dynamic);

        static void DestroyMesh(Mesh *mesh);
};

}

#endif

