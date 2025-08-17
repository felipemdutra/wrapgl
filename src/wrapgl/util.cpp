#include "util.h"

#include <iostream>

int ThrowIfGlError(GLenum error)
{
        switch (error) {
                case GL_INVALID_ENUM:
                        //throw std::runtime_error("GL_INVALID_ENUM: An unacceptable value was specified for an enumerated argument");
                        std::cerr << "GL_INVALID_ENUM: An unacceptable value was specified for an enumerated argument";
                        break;
                case GL_INVALID_VALUE:
                        //throw std::runtime_error("GL_INVALID_VALUE: A numeric argument is out of range.");
                        std::cerr << "GL_INVALID_VALUE: A numeric argument is out of range.";
                        break;
                case GL_INVALID_OPERATION:
                        //throw std::runtime_error("GL_INVALID_OPERATION: The specified operation is not allowed in the current state.");
                        std::cerr << "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
                        break;
                case GL_INVALID_FRAMEBUFFER_OPERATION:
                        //throw std::runtime_error("GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.");
                        std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
                        break;
                case GL_OUT_OF_MEMORY:
                        //throw std::runtime_error("GL_OUT_OF_MEMORY: There is not enough memory left to execute the command");
                        std::cerr << "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command";
                        break;
                case GL_STACK_UNDERFLOW:
                        //throw std::runtime_error("GL_STACK_UNDERFLOW: An attempt has been made to perform an operation that would cause an internal stack to underflow. ");
                        std::cerr << "GL_STACK_UNDERFLOW: An attempt has been made to perform an operation that would cause an internal stack to underflow. ";
                        break;
                case GL_STACK_OVERFLOW:
                        //throw std::runtime_error("GL_STACK_OVERFLOW: An attempt has been made to perform an operation that would cause an internal stack to overflow. ");
                        std::cerr << "GL_STACK_OVERFLOW: An attempt has been made to perform an operation that would cause an internal stack to overflow. ";
                        break;
                default:
                        // No error.
                        return 0;
        }

        return -1;
}

