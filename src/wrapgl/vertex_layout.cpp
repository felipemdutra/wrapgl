#include "vertex_layout.h"

#include <algorithm>
#include <cstdint>

namespace wgl {

VertexLayout& VertexLayout::AddAttr(unsigned int idx, AttributeType type, uint8_t n_components, 
                      GLenum data_type, bool normalized)
{
        auto existing = std::find_if(attributes_.begin(), attributes_.end(),
                        [type](const VertexAttribute& attr) {
                                return attr.data_type == type;
                        });

        if (existing != attributes_.end()) {
                *existing = VertexAttribute(idx, type, n_components, data_type,
                                normalized);
;
        } else {
                attributes_.emplace_back(idx, type, n_components, data_type,
                                normalized);
        }

        CalculateOffsetsAndStride();
        return *this; // For method chaining.
}

void VertexLayout::CalculateOffsetsAndStride()
{
        stride_ = 0;
        for (auto& attr : attributes_) {
                attr.offset = stride_;
                stride_ += attr.GetSize();
        }
}

bool VertexLayout::HasAttribute(AttributeType attr) const
{
        return std::find_if(
                        attributes_.begin(),
                        attributes_.end(),
                        [attr](const VertexAttribute va) {
                                return va.attr_type == attr; }
                        ) != attributes_.end();
}

} // namespace wgl

