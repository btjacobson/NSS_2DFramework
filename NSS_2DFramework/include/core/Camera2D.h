#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include "glm.hpp"
#include "gtc/type_ptr.hpp"
#include "gtc/matrix_transform.hpp"

class Camera2D
{
public:
    Camera2D(int screenWidth, int screenHeight);

    void SetPosition(glm::vec2 newPosition);
    void SetZoom(float newZoom);

    glm::mat4& GetProjectionMatrix();
    glm::mat4& GetViewMatrix();

private:
    glm::vec2 position;
    glm::mat4 projection;
    glm::mat4 view;

    float zoom;
    int screenWidth;
    int screenHeight;
};

#endif
