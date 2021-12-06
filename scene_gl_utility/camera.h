#ifndef _CAMERA_H_
#define _CAMERA_H_

struct Camera {
    GLfloat verticalAngle, horizontalAngle;
    glm::vec3 eye, up;
    [[nodiscard]] glm::vec3 viewVec() const {
        return {cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle),
                -cos(verticalAngle) * cos(horizontalAngle)};
    }
};

#endif // _CAMERA_H_
