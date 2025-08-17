#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/glew.h>
#include <string>

#include <glm/glm.hpp>

namespace wgl {

class ShaderProgram {
private:
        GLuint kProgramId;

        // Reads the contents of the file in the path to a string.
        // Used in the constructor to open and read the shader files.
        static std::string ReadFileToString(const std::string &path);

        // Compiles given shader and checks for errors.
        //
        // This method should be used in the constructor for ShaderProgram.
        // If it fails, the constructor is responsible for handling the error
        // and throwing.
        //
        // @param shader The shader to compile.
        //
        // @param out_info_log If compilation fails, this is the error that
        // happened. Should be used by the constructor for error handling.
        // If compilation is successful, this'll be a nullptr.
        //
        // @return false on failure, true otherwise.
        static bool CompileShader(unsigned int shader, 
                        std::string &out_info_log);

        // Links the shader program (kProgramId) and checks for error.
        //
        // This method should be used after attaching both vertex and fragment
        // shaders inside the constructor, whose responsible for error 
        // handling.
        //
        // @param out_info_log If linkage fails, it contains the error message
        // that should be used for error handling, else it contains an empty
        // string.
        //
        // @return false on failure, true otherwise.
        bool LinkProgram(std::string &out_info_log) const;

public:
        // Creates a shader program using the vertex and fragment shaders given
        // in the paths.
        ShaderProgram(const std::string &vertex_path,
                      const std::string &fragment_path);

        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;

        ShaderProgram(ShaderProgram&& other) noexcept;
        ShaderProgram& operator=(ShaderProgram &&other) noexcept;
        ~ShaderProgram();

        void Use() const;

        void SetVec3(const std::string &name, const glm::vec3 &vec) const;
        void SetMat4(const std::string &name, const glm::mat4 &mat) const;
};

} // wgl

#endif //SHADERPROGRAM_H
