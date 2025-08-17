#ifndef VERTEX_LAYOUT_H
#define VERTEX_LAYOUT_H

#include <algorithm>
#include <cstdint>
#include <vector>
#include <cstddef>

#include "vertex_attribute.h" 

namespace wgl {

class VertexLayout {
private:
        std::vector<VertexAttribute> attributes_;
        size_t stride_;

        void CalculateOffsetsAndStride();
public:
        inline size_t GetStride() const { return stride_; };

        inline const std::vector<VertexAttribute>& GetAttributes() const
        { return attributes_; }

        bool HasAttribute(AttributeType attr) const;

        VertexLayout& AddAttr(unsigned int idx, AttributeType type, 
                        uint8_t n_components, GLenum data_type,
                        bool normalized);
};

} // namespace wgl

#endif

