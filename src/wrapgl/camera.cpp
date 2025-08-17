#include "camera.h"
#include "shader_program.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>

namespace wgl {

using namespace glm;
using namespace std;

PerspectiveCamera::
PerspectiveCamera(
                ShaderProgram *program,
                string view_name,
                string proj_name,
                float fovd,
                float aspect,
                float near,
                float far
                )
{
        fov_ = radians(fovd);
        near_ = near;
        far_ = far;
        aspect_ = aspect;
        program_ = program;

        position_ = vec3(0.0f);
        rotation_ = vec3(0.0f, radians(-90.0f), 0.0f);

        view_name_ = view_name;
        proj_name_ = proj_name;
}

mat4 PerspectiveCamera::GetProjectionMatrix() const
{
        return perspective(fov_, aspect_, near_, far_); }

mat4 PerspectiveCamera::GetViewMatrix() const
{
        float pitch = rotation_.x;
        float yaw = rotation_.y;

        vec3 front;
        front.x = cos(pitch) * cos(yaw);
        front.y = sin(pitch);
        front.z = cos(pitch) * sin(yaw);
        front = normalize(front);

        vec3 right = normalize(cross(front, kUp));
        vec3 up = normalize(cross(right, front));

        return lookAt(position_, position_ + front, up);
}

void PerspectiveCamera::Update() const
{
        program_->SetMat4(view_name_, GetViewMatrix());
        program_->SetMat4(proj_name_, GetProjectionMatrix());
}

} // namespace wgl

