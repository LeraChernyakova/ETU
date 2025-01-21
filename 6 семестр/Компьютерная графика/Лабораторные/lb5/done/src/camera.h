#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include <QMatrix4x4>

class Camera
{
public:
    enum class MoveDirection {
        Forward,
        Back,
        Left,
        Right,
        Up,
        Down
    };

    Camera();
    QMatrix4x4 getView();
    QMatrix4x4 getProjection();
    QVector3D getPos();
    void setViewport(int w, int h);
    void move(MoveDirection direction);
    void rotate(float deltaYaw, float deltaPitch);

private:
    QVector3D cameraPos;
    QVector3D cameraFront;
    QVector3D cameraUp;

    int height;
    int width;

    float fov;
    float yaw;
    float pitch;
};

#endif // CAMERA_H
