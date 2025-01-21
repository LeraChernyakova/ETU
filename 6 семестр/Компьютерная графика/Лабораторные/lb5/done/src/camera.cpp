#include "camera.h"

Camera::Camera()
{
    cameraPos = { 0.0f, 0.0f, 3.0f };
    cameraFront = { 0.0f, 0.0f, -1.0f };
    cameraUp = { 0.0f, 1.0f, 0.0f };

    height = 640;
    width = 480;

    fov = 45.0f;
    pitch = 0.0f;
    yaw = -90.0f;
}

QMatrix4x4 Camera::getView()
{
    QMatrix4x4 view;
    view.lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    return view;
}

QMatrix4x4 Camera::getProjection()
{
    QMatrix4x4 projection;
    float aspect = width / (height ? (float)height : 1.0f);
    projection.perspective(fov, aspect, 0.1f, 50.0f);
    return projection;
}

QVector3D Camera::getPos()
{
    return cameraPos;
}

void Camera::setViewport(int w, int h)
{
    width = w;
    height = h;
}

void Camera::move(MoveDirection direction)
{
    float cameraSpeed = 0.5f;

    QVector3D cameraRight = QVector3D::crossProduct(cameraFront, cameraUp).normalized();

    if (direction == MoveDirection::Forward) {
        cameraPos += cameraSpeed * cameraFront;
    }
    if (direction == MoveDirection::Back) {
        cameraPos -= cameraSpeed * cameraFront;
    }
    if (direction == MoveDirection::Left) {
        cameraPos -= cameraSpeed * cameraRight;
    }
    if (direction == MoveDirection::Right) {
        cameraPos += cameraSpeed * cameraRight;
    }
    if (direction == MoveDirection::Up) {
        cameraPos += cameraSpeed * cameraUp;
    }
    if (direction == MoveDirection::Down) {
        cameraPos -= cameraSpeed * cameraUp;
    }
}

void Camera::rotate(float deltaYaw, float deltaPitch)
{
    yaw += deltaYaw;
    pitch += deltaPitch;

    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    QVector3D front;
    front.setX(qCos(qDegreesToRadians(yaw)) * qCos(qDegreesToRadians(pitch)));
    front.setY(qSin(qDegreesToRadians(pitch)));
    front.setZ(qSin(qDegreesToRadians(yaw)) * qCos(qDegreesToRadians(pitch)));

    cameraFront = front.normalized();
}
