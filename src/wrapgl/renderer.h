#ifndef RENDERER_H
#define RENDERER_H

#include <unordered_map>
#include <string_view>
#include <string>

#include <glm/ext/matrix_float4x4.hpp>
#include <GL/glew.h>

#include "shader_program.h"

namespace wgl {

class Renderer {
private:
        std::unordered_map<std::string, ShaderProgram*> shader_programs_;

        std::string active_program_name_; // Stores the name of the current active shader program.

public:
        // Binds the program to the Renderer, making it available for use
        //
        // Note: the newly added program IS NOT set as the currently active 
        // one. You need to call UseProgram for that.
        void BindProgram(const std::string &name, ShaderProgram *program);

        // Sets the shader program with given name as the active program to
        // draw with.
        //
        // @param name The name of the program you set in BindProgram
        // @returns true if the program was activated, false otherwise.
        bool UseProgram(const std::string &name);

        // @brief Sets a uniform 4x4 matrix in the currently active shader 
        //        program.
        //
        // This function updates the specified uniform variable in the active
        // shader program with a 4x4 matrix. The uniform variable must be of
        // type `mat4` in the shader code.
        //
        // @param name The name of the uniform variable in the shader program.
        //        It should match the name used in the shader code.
        // @param mat The 4x4 matrix to be set as the value of the uniform 
        //        value.
        // @note This function assumes that a shader program is currently
        //       active. If no program is active, behaviour is undefined, and 
        //       bad things will happen.
        void SetUniformMatrix4f(const std::string &name, const glm::mat4 &mat);

        // @brief Sets a uniform 3D vector in the currently active shader 
        //      program.
        //
        // This function updates the specified uniform variable in the active
        // shader program with a 3D vector. The uniform variable must be of
        //      type `vec3` in the shader code.
        // 
        // @param name The name of the uniform variable in the shader program.
        //      It should match the name used in the shader code.
        // @param vec The 3D vector to be set as the value of the uniform 
        //       variable
        // @note This function assumes that a shader program is currently
        //      active. If no program is active, the behaviour is undefined.
        void SetUniformVec3f(const std::string &name, const glm::vec3 &vec);

        // @brief Returns a pointer to a bound shader program.
        //
        // This function searches for a bound shader program using the 
        // specified name. If the shader program is found, a pointer to it is
        // returned. Otherwise, a nullptr is returned.
        //
        // @param name The name of the shade program to retrieve. This should
        //             match the name used when the program was bound with
        //             the renderer.
        // @returns A pointer to the shader program if found, nullptr 
        //          otherwise.
        ShaderProgram* GetProgram(const std::string &name);

        void Draw(unsigned int vao, unsigned int index_count) const;

        void DrawInstanced(unsigned int vao, unsigned int index_count,
                        GLsizei instance_count) const;

        void Clear(float r, float g, float b, float a, bool clear_depht) const;
};

} // namespace wlg

#endif

