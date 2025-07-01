#include <GL/glew.h>

#include "window.h"

#include <GLFW/glfw3.h>
#include <stdexcept>

namespace wgl {

Window::Window(int width, int height, const std::string &title)
        : width_(width), height_(height), title_(title)
{
        if (glfwInit() == GLFW_FALSE) {
                throw std::runtime_error("ERROR: FAILED TO INITIALIZE GLFW");
        }

        // Configure context
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        handle_ = glfwCreateWindow(width_, height_, title_.c_str(), nullptr,
                        nullptr);

        glfwMakeContextCurrent(handle_);

        // This function sets this Window object as a pointer to our handle
        // window.
        //
        // We use this to our advantage inside FrameBufferSizeCallback, to keep
        // the handle's width and height in sync with our Window object after
        // resizing the frame buffer.
        glfwSetWindowUserPointer(handle_, this);

        glfwMakeContextCurrent(handle_); // Set OpenGL context to our window

        // Initialize glew after setting up context.
        if (glewInit() != GLEW_OK) {
                glfwDestroyWindow(handle_);
                glfwTerminate();

                throw std::runtime_error("ERROR: FAILED TO INITIALIZE GLEW");
        }

        // Callback if window gets resized
        glfwSetFramebufferSizeCallback(handle_, FrameBufferSizeCallback);
}

Window::~Window()
{
        glfwDestroyWindow(handle_);
        glfwTerminate();
        handle_ = nullptr;
}

void Window::FrameBufferSizeCallback(GLFWwindow *handle, int w, int h)
{
        // We must sync the handle's width and height with the Window object
        // that the handle points to, which we set inside Window::Window()
        auto *window = static_cast<Window*>(glfwGetWindowUserPointer(handle));
        if (window) {
                window->SetWidth(w);
                window->SetHeight(h);

                glViewport(0, 0, w, h);
        }
}

} // namespace wgl

