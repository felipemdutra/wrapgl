#ifndef PERSPECTIVE_CAMERA_H
#define PERSPECTIVE_CAMERA_H

#include "shader_program.h"
#include <glm/glm.hpp>

namespace wgl {

class PerspectiveCamera {
private:
        ShaderProgram *program_;
        std::string view_name_, proj_name_;

        glm::vec3 position_;
        glm::vec3 rotation_; // { pitch, yaw, roll } in radians
        float fov_, aspect_, near_, far_;

        static constexpr glm::vec3 kUp = glm::vec3(0.0f, 1.0f, 0.0f);

public:
        // @brief Sets perspective camera with given configuration.
        //
        // @param program The program where your view and projection matrices
        //        are setup.
        // @param view The uniform variable name for the view matrix in your
        //        shader.
        // @param proj The uniform variable name for the projection matrix in
        //        your shader.
        // @param fovd The desired FOV in degrees.
        // @param aspect A window's width divided by it's height.
        // @param near The closest distance from the camera at which objects
        //        are rendered. Anything closer is completely cut off.
        // @param far The farthest distance from the camera at which objects
        //        are rendered. Anything beyond is also cut off. 
        PerspectiveCamera(
                        ShaderProgram *program,
                        std::string view_name,
                        std::string proj_name,
                        float fovd,
                        float aspect,
                        float near,
                        float far
                        );

        inline void SetPosition(const glm::vec3 &pos) { position_ = pos; }

        inline void SetRotation(const glm::vec3 &rotDegrees)
        { rotation_ = glm::radians(rotDegrees); }

        inline void SetAspect(float aspect) { aspect_ = aspect; }

        inline void SetX(float x) { position_.x = x; }
        inline void SetY(float y) { position_.y = y; }
        inline void SetZ(float z) { position_.z = z; }

        inline void Translate(const glm::vec3 &delta) { position_ += delta; }
        inline void Rotate(const glm::vec3 &delta) { rotation_ += delta; }

        glm::mat4 GetProjectionMatrix() const;
        glm::mat4 GetViewMatrix() const;
        
        void Update() const;
};

}

#endif

