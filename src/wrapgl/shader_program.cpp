#include <GL/glew.h>

#include "shader_program.h"

#include <exception>
#include <fstream>
#include <glm/matrix.hpp>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <string>

constexpr int kLogSize = 512;

using namespace std;

namespace wgl {

ShaderProgram::ShaderProgram(const string &vertex_path, const string &fragment_path)
        : kProgramId(glCreateProgram())
{
        // Only delete if they are 0.
        unsigned int vertex = 0, fragment = 0;

        // We put everything on a try-catch statement because if anything
        // fails, we must delete the shaders and the shader program. We do this
        // so that we don't need to delete them in every branch that fails.
        try {

                string vertex_code_str = ReadFileToString(vertex_path);
                string fragment_code_str = ReadFileToString(fragment_path);

                const char *vertex_code = vertex_code_str.c_str();
                const char *fragment_code = fragment_code_str.c_str();

                vertex = glCreateShader(GL_VERTEX_SHADER);
                fragment = glCreateShader(GL_FRAGMENT_SHADER);

                glShaderSource(vertex, 1, &vertex_code, nullptr);
                glShaderSource(fragment, 1, &fragment_code, nullptr);

                string info_log;

                if (!CompileShader(vertex, info_log)) {
                        throw std::runtime_error("ERROR: FAILED TO COMPILE VERTEX "
                                        "SHADER: " + info_log);
                }

                if (!CompileShader(fragment, info_log)) {
                        throw std::runtime_error("ERROR: FAILED TO COMPILE FRAGMENT "
                                        "SHADER: " + info_log);
                }

                glAttachShader(kProgramId, vertex); 
                glAttachShader(kProgramId, fragment);

                glDeleteShader(vertex);
                glDeleteShader(fragment);

                if (!LinkProgram(info_log)) {
                        throw std::runtime_error("ERROR: FAILED TO LINK SHADER "
                                        "PROGRAM: " + info_log);
                }

        } catch (exception &e) {
                if (vertex != 0) {
                        glDeleteShader(vertex);
                }

                if (fragment != 0) {
                        glDeleteShader(fragment);
                }

                glDeleteProgram(kProgramId);

                // Throw again. This catch statement was only used for cleanup
                // before the program stopped completely.
                throw;
        }
}

ShaderProgram::~ShaderProgram()
{
        glDeleteProgram(kProgramId);
}

string ShaderProgram::ReadFileToString(const string &path)
{
        ifstream shader_file;
        string shader_code;

        // Before opening the file, we need to allow it to throw exceptions if
        // these errors occur.
        shader_file.exceptions(ifstream::badbit | ifstream::failbit);

        try {
                shader_file.open(path);
                
                stringstream shader_stream;

                shader_stream << shader_file.rdbuf();
                shader_code = shader_stream.str();

        } catch (exception &e) {
                throw runtime_error("ERROR: FAILED TO READ SHADER FILE: " 
                                + string(e.what()));
        }

        return shader_code;
}

bool ShaderProgram::CompileShader(unsigned int shader, string &out_info_log)
{
        glCompileShader(shader);

        int success;
        char info_log[kLogSize];

        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        
        if (!success) {
                glGetShaderInfoLog(shader, kLogSize, nullptr, info_log);
                out_info_log = info_log;

                return false;
        }
        
        out_info_log = "";
        return true;
}

bool ShaderProgram::LinkProgram(std::string &out_info_log) const
{
        glLinkProgram(kProgramId);

        int success;
        char info_log[kLogSize];

        glGetProgramiv(kProgramId, GL_LINK_STATUS, &success);

        if (!success) {
                glGetProgramInfoLog(kProgramId, kLogSize, nullptr, info_log);
                out_info_log = info_log; 

                return false;
        }

        return true;
}


void ShaderProgram::SetVec3(const std::string &name, const glm::vec3 &vec) const
{
        glUniform3fv(glGetUniformLocation(kProgramId, name.c_str()), 1, &vec[0]);
}

void ShaderProgram::SetMat4(const std::string &name, const glm::mat4 &mat) const
{
        glUniformMatrix4fv(
                        glGetUniformLocation(kProgramId, name.c_str()),
                        GL_FALSE,
                        1,
                        &mat[0][0]
                        );
}

} // wgl

