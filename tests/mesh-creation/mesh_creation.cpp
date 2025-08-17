#include "../../src/wrapgl/wrapgl.h"
#include <GLFW/glfw3.h>
#include <memory>

#include <glm/gtc/matrix_transform.hpp>

using namespace wgl;

int main(void)
{
        Window window(800, 600, "WrapGL demo");

        Renderer renderer = Renderer();

        // Create shader program.
        auto program = std::make_shared<ShaderProgram>("tests/mesh-creation/vertex.glsl",
                        "tests/mesh-creation/fragment.glsl");

        renderer.BindProgram("default", program.get());
        renderer.UseProgram("default");

        VertexLayout mesh_layout;
        mesh_layout.AddAttr(
                        /*idx=*/0,
                        kPosition,
                        /*n_components=*/3,
                        /*data_type=*/GL_FLOAT,
                        /*normalized=*/false
                        );

        mesh_layout.AddAttr(1, kColor, 3, GL_FLOAT, true);

        const glm::vec3 rgb(1.0f, 0.0f, 0.0f);
        Mesh *mesh = MeshFactory::GetCube(mesh_layout, &rgb);
        if (!mesh) {
                return 1;
        }

        PerspectiveCamera camera = PerspectiveCamera(
                        program.get(),
                        "view",
                        "proj",
                        45.0f,
                        (float)window.GetWidth()/window.GetHeight(),
                        0.1f,
                        1000.0f
                        );

        camera.SetPosition(glm::vec3(-2.0f, 2.0f, 5.0f));
        camera.SetRotation(glm::vec3(-30.0f, -90.0f, 0.0f));

        while (!window.ShouldClose()) {
                renderer.Clear(0.63f, 0.23f, 0.86f, 1.0f, true);
                camera.Update();

                renderer.SetUniformMatrix4f("model", glm::mat4(1.0f));
                mesh->Draw(renderer);

                window.SwapBuffers();
                glfwPollEvents();
        }

        return 0;
}

