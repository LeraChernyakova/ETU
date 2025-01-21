#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4>
#include <QVector3D>

//camera representation
class Camera
{
public:
    Camera(
        const QPointF& screenSize,
        float speed = 0.02f,
        const QVector3D& position = { 0.f, 0.f, 3.f }
    );

    //move camera forward and right
    void move(int forward, int right);
    // rotate camera to look at xPos and yPos
    void rotate(float xPos, float yPos);
    //rotate camera to look at position
    void rotate(const QPointF& position);
    //setup mouse press position
    void mousePress(const QPointF& position);
    //set window size
    void resize(const QPointF& size);

    inline QVector3D getPosition() const { return position_; }
    inline QMatrix4x4 getView() const { return matrix_; }
    inline QMatrix4x4 getRotation() const { return rotation_; }

private:
    //convert degrees to radians
    inline float d2r(float degrees) const
    {
        return 3.1459265 * degrees / 180.f;
    }
    //set front and up vectors and calculate right vector
    void setDirectionVectors(const QVector3D& front, const QVector3D& up);
    //recalculate view and rotation matrices
    void rebuildMatrix();

    //view matrix
    QMatrix4x4 matrix_;
    //camera rotation matrix
    QMatrix4x4 rotation_;
    //camera movement speed
    float speed_;
    //camera position
    QVector3D position_;
    //camera front direction vector
    QVector3D frontVector_;
    //camera up direction vector
    QVector3D upVector_;
    //camera right direction vector
    QVector3D rightVector_;
    //mouse sensitivity for camera rotation
    float sensitivity_ = 0.01f;
    //camera yaw
    float yaw_ = -90.f;
    //camera pitch
    float pitch_    = 0.f;
    //window size
    QPointF screenSize_;
    //mouse last location after press
    QPointF lastMousePosition_;
};

#endif // CAMERA_H
