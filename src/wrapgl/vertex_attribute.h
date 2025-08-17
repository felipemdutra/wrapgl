#ifndef VERTEX_ATTRIBUTE_H
#define VERTEX_ATTRIBUTE_H

#include <GL/glew.h>
#include <cstdint>

namespace wgl {

enum AttributeType {
        kPosition = 0,
        kNormal,
        kColor,
};

struct VertexAttribute {
        unsigned int idx;             // Attribute's layout index in the shader.
        AttributeType attr_type; /* Type of the attribute, such as position,
                                    color, etc. */
        uint8_t n_components;    /* Number of components of the attribute, 
                                    like position can have 3 elements, for x, y
                                    and z. */
        GLenum data_type;        // GL_FLOAT, GL_INT, etc.
        size_t offset;           // Attribute's offset in the vertex layout.
        bool normalized;         // Whether the components are normalized.

        VertexAttribute(unsigned int idx, AttributeType attr_type, uint8_t n_comp,
                        GLenum data_type, bool norm);

        size_t GetSize() const;
};

} // namespace wgl

#endif

