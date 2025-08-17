#include "vertex_attribute.h"

namespace wgl {

VertexAttribute::VertexAttribute(
                unsigned int idx,
                AttributeType attr_type,
                uint8_t n_comp,
                GLenum data_type,
                bool norm) 
        : idx(idx), attr_type(attr_type), n_components(n_comp), 
        data_type(data_type), normalized(norm)
{ }

size_t VertexAttribute::GetSize() const
{
        size_t type_size;
        switch (data_type) {
                case GL_INT:
                        type_size = sizeof(int); break;
                case GL_UNSIGNED_INT:
                        type_size = sizeof(unsigned int); break;
                case GL_SHORT:
                        type_size = sizeof(short int); break;
                case GL_UNSIGNED_SHORT:
                        type_size = sizeof(unsigned short); break;
                case GL_BYTE:
                        type_size = sizeof(char); break;
                case GL_UNSIGNED_BYTE:
                        type_size = sizeof(unsigned char); break;
                case GL_DOUBLE:
                        type_size = sizeof(double); break;
                case GL_FLOAT:
                default:
                        type_size = sizeof(float); break;
        }
        
        return n_components * type_size;
}

} // namespace wgl

