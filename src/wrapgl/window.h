#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <string>

namespace wgl {

// A blank window.
// A Window object should be the first thing you initialize in your project.
//
// Example:
//      Window win(800, 600, "This is a Window");
//      while (!win.ShouldClose()) {
//          win.SwapBuffers();
//      }
class Window {
private:
        GLFWwindow *handle_ = nullptr; 
        
        int width_, height_;
        std::string title_;

        static void FrameBufferSizeCallback(GLFWwindow *handle, int w, int h);
         
public:
        Window(int width, int height, const std::string &title);

        ~Window();

        int GetWidth() const { return width_; }
        int GetHeight() const { return height_; }

        void SetWidth(int width) { width_ = width; }
        void SetHeight(int height) { height_ = height; }

        bool ShouldClose() const { return glfwWindowShouldClose(handle_); }

        void SwapBuffers() const { glfwSwapBuffers(handle_); }
};

}

#endif

