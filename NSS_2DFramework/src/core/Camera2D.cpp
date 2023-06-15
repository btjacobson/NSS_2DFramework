#include "core/Camera2D.h"

Camera2D::Camera2D(int screenWidth, int screenHeight) : position(0.0f, 0.0f), zoom(1.0f),
    screenWidth(screenWidth), screenHeight(screenHeight)
{
    projection = glm::ortho(0.0f, static_cast<float>(screenWidth), 
        static_cast<float>(screenHeight), 0.0f, -1.0f, 1.0f);
}

void Camera2D::SetPosition(glm::vec2 newPosition)
{
    position = newPosition;
}

void Camera2D::SetZoom(float newZoom)
{
    zoom = newZoom;
}

glm::mat4& Camera2D::GetProjectionMatrix()
{
    return projection;
}

glm::mat4& Camera2D::GetViewMatrix()
{
    view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(-position.x, -position.y, 0.0f));
    view = glm::scale(view, glm::vec3(zoom, zoom, 1.0f));

    return view;
}
