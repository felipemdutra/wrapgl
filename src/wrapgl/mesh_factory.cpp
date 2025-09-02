#include "mesh_factory.h"
#include "mesh.h"
#include "vertex_attribute.h"
#include <glm/ext/vector_float3.hpp>
#include <utility>
#include <vector>

using std::vector, std::pair;

namespace wgl {

static std::pair<std::vector<float>, std::vector<unsigned int>>
CreateCubeVerticesAndIndices(const VertexLayout& layout, const glm::vec3* rgb)
{
    bool hasColor = layout.HasAttribute(AttributeType::kColor);

    // 8 unique cube corners
    static const glm::vec3 positions[8] = {
        {-0.5f, -0.5f,  0.5f}, // 0 front-bottom-left
        { 0.5f, -0.5f,  0.5f}, // 1 front-bottom-right
        { 0.5f,  0.5f,  0.5f}, // 2 front-top-right
        {-0.5f,  0.5f,  0.5f}, // 3 front-top-left
        {-0.5f, -0.5f, -0.5f}, // 4 back-bottom-left
        { 0.5f, -0.5f, -0.5f}, // 5 back-bottom-right
        { 0.5f,  0.5f, -0.5f}, // 6 back-top-right
        {-0.5f,  0.5f, -0.5f}  // 7 back-top-left
    };

    std::vector<float> verts;
    verts.reserve(8 * (3 + (hasColor ? 3 : 0)));

    for (const auto& pos : positions) {
        verts.push_back(pos.x);
        verts.push_back(pos.y);
        verts.push_back(pos.z);

        if (hasColor) {
            if (rgb) {
                verts.push_back(rgb->r);
                verts.push_back(rgb->g);
                verts.push_back(rgb->b);
            } else {
                verts.push_back(1.0f);
                verts.push_back(1.0f);
                verts.push_back(1.0f);
            }
        }
    }

    // 12 triangles (36 indices), CCW front-facing
    const std::vector<unsigned int> indices = {
        // Front face
        0, 1, 2, 2, 3, 0,
        // Back face
        5, 4, 7, 7, 6, 5,
        // Left face
        4, 0, 3, 3, 7, 4,
        // Right face
        1, 5, 6, 6, 2, 1,
        // Top face
        3, 2, 6, 6, 7, 3,
        // Bottom face
        4, 5, 1, 1, 0, 4
    };

    return {verts, indices};
}

static std::pair<std::vector<float>, std::vector<unsigned int>>
CreatePyramidVerticesAndIndices(const VertexLayout& layout, const glm::vec3* rgb)
{
    bool hasColor = layout.HasAttribute(AttributeType::kColor);

    // 5 unique vertices (square base + apex)
    static const glm::vec3 positions[5] = {
        {-0.5f, -0.5f,  0.5f}, // 0 front-left base
        { 0.5f, -0.5f,  0.5f}, // 1 front-right base
        { 0.5f, -0.5f, -0.5f}, // 2 back-right base
        {-0.5f, -0.5f, -0.5f}, // 3 back-left base
        { 0.0f,  0.5f,  0.0f}  // 4 apex
    };

    std::vector<float> verts;
    verts.reserve(5 * (3 + (hasColor ? 3 : 0)));

    for (const auto& pos : positions) {
        verts.push_back(pos.x);
        verts.push_back(pos.y);
        verts.push_back(pos.z);

        if (hasColor) {
            if (rgb) {
                verts.push_back(rgb->r);
                verts.push_back(rgb->g);
                verts.push_back(rgb->b);
            } else {
                verts.push_back(1.0f);
                verts.push_back(1.0f);
                verts.push_back(1.0f);
            }
        }
    }

    // Indices (CCW order)
    const std::vector<unsigned int> indices = {
        // Base (two triangles)
        0, 1, 2,
        2, 3, 0,

        // Sides (four triangles)
        0, 1, 4, // front
        1, 2, 4, // right
        2, 3, 4, // back
        3, 0, 4  // left
    };

    return {verts, indices};
}

Mesh* MeshFactory::GetCube(const VertexLayout &layout, const glm::vec3 *rgb, bool dynamic)
{
        if (!layout.HasAttribute(AttributeType::kPosition)) {
                return nullptr;
        }

        auto [vertices, indices] = CreateCubeVerticesAndIndices(layout, rgb);

        return new Mesh(layout, vertices, indices, dynamic);
}

Mesh* MeshFactory::GetPyramid(const VertexLayout &layout, const glm::vec3 *rgb, bool dynamic)
{
    if (!layout.HasAttribute(AttributeType::kPosition)) {
        return nullptr;
    }

    auto [vertices, indices] = CreatePyramidVerticesAndIndices(layout, rgb);

    return new Mesh(layout, vertices, indices, dynamic);
}

void MeshFactory::DestroyMesh(Mesh *mesh)
{
        delete mesh;
}

} // namespace wgl

