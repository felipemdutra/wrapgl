#include "renderer.h"

#include <cassert>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <utility>

#include "shader_program.h"

namespace wgl {

using std::string, glm::mat4, glm::vec3;

ShaderProgram* Renderer::GetProgram(const string &name)
{
        auto it = shader_programs_.find(name);
        if (it == shader_programs_.end()) {
                return nullptr;
        }

        return it->second;
}

void Renderer::BindProgram(const string &name, ShaderProgram* program)
{
        shader_programs_.insert(std::make_pair(name, program));
}

bool Renderer::UseProgram(const string &name)
{
        ShaderProgram *program = GetProgram(name);
        if (!program) {
                return false;
        }

        active_program_name_ = name;
        program->Use();

        return true;
}

void Renderer::SetUniformMatrix4f(const string &name, const mat4 &mat)
{
        ShaderProgram *active_program = GetProgram(active_program_name_);
        if (!active_program) {
                return;
        }

        active_program->SetMat4(name, mat);
}

void Renderer::SetUniformVec3f(const string &name, const vec3 &vec)
{
        ShaderProgram *active_program = GetProgram(active_program_name_);
        if (!active_program) {
                return;
        }

        active_program->SetVec3(name, vec);
}

void Renderer::Draw(unsigned int vao, unsigned int index_count) const
{
        assert(glGetError() == GL_NO_ERROR);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
        assert(glGetError() == GL_NO_ERROR);
}

void Renderer::DrawArrays(unsigned int vao, GLenum mode, GLsizei vertex_count) const
{
    assert(glGetError() == GL_NO_ERROR);
    glBindVertexArray(vao);
    glDrawArrays(mode, 0, vertex_count);
    glBindVertexArray(0);
    assert(glGetError() == GL_NO_ERROR);
}

void Renderer::DrawInstanced(unsigned int vao, unsigned int index_count,
                GLsizei instance_count) const
{
        glBindVertexArray(vao);
        glDrawElementsInstanced(
                        GL_TRIANGLES,
                        index_count,
                        GL_UNSIGNED_INT,
                        nullptr,
                        instance_count
                        );
        glBindVertexArray(0);
}

void Renderer::Clear(float r, float g, float b, float a, bool clear_depth) const
{
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | (clear_depth ? GL_DEPTH_BUFFER_BIT : 0));
}

} // namespace wgl

