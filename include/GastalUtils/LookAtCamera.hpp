// LookAtCamera.hpp
#ifndef LOOKATCAMERA_HPP
#define LOOKATCAMERA_HPP

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include "GastalUtils/matricies.h"

glm::mat4 Matrix_Camera_View(glm::vec4 camera_position_c, glm::vec4 camera_view_vector, glm::vec4 camera_up_vector);
glm::mat4 Matrix_Perspective(float field_of_view, float aspect, float near, float far);


class LookAtCamera {
private:
    float cameraTheta;
    float cameraPhi;
    float cameraDistance;

    float radius;
    float coordX;
    float coordY;
    float coordZ;

    glm::vec4 cameraPositionC;
    glm::vec4 cameraLookAtL;
    glm::vec4 cameraViewVector;
    glm::vec4 cameraUpVector;

    void UpdateCamera();

public:
    LookAtCamera(float theta, float phi, float distance);

    void SetCameraTheta(float theta);
    void SetCameraPhi(float phi);
    void SetCameraDistance(float distance);

    glm::mat4 GetMatrixCameraView() const;
    glm::mat4 GetMatrixPerspective(float nearplane, float farplane, float field_of_view, float screenRatio) const;
    float GetCameraTheta() const;
    float GetCameraPhi() const;
    float GetCameraDistance() const;
        
};

#endif // LOOKATCAMERA_HPP