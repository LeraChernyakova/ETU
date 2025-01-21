#include "camera.h"

Camera::Camera(
    const QPointF& screenSize,
    float speed,
    const QVector3D& position
):
    speed_{ speed },
    position_{ position }
{
    /* init sensitivity and window size */
    resize(screenSize);
    /* init direction vectors */
    setDirectionVectors(QVector3D{ 0.f, 0.f, -1.f }, QVector3D{ 0.f, 1.f, 0.f }); 
    /* init view matrix */
    rebuildMatrix();
}


void Camera::setDirectionVectors(const QVector3D& front, const QVector3D& up)
{
    frontVector_ = front;
    upVector_ = up;
    rightVector_ = QVector3D::crossProduct(frontVector_, upVector_);
}


void Camera::rebuildMatrix()
{
    /* calculate view matrix */
    matrix_.setToIdentity();
    matrix_.lookAt(position_, position_ + frontVector_, upVector_);
    /* calculate rotation matrix */
    rotation_.setToIdentity();
    rotation_.rotate(QQuaternion::fromDirection(frontVector_, upVector_));
}


void Camera::move(int forward, int right)
{
    /* move camera */
    position_ += forward * speed_ * frontVector_;
    position_ += right * speed_ * rightVector_;

    rebuildMatrix();
}


void Camera::rotate(float xPos, float yPos)
{
    /* calculate new direction */
    float xOffset = (xPos - lastMousePosition_.x()) * sensitivity_;
    float yOffset = (lastMousePosition_.y() - yPos) * sensitivity_;
    lastMousePosition_ = { xPos, yPos };

    yaw_    += xOffset;
    pitch_  += yOffset;

    if (pitch_ > 89.f)
    {
        pitch_ =  89.f;
    }
    else if (pitch_ < -89.f)
    {
        pitch_ = -89.f;
    }

    /* set new camera direction */
    QVector3D direction = {
        std::cos(d2r(yaw_)) * std::cos(d2r(pitch_)),
        std::sin(d2r(pitch_)),
        std::sin(d2r(yaw_)) * std::cos(d2r(pitch_))
    };
    setDirectionVectors(direction.normalized(), upVector_);

    rebuildMatrix();
}


void Camera::rotate(const QPointF& position)
{
    rotate(position.x(), position.y());
}


void Camera::mousePress(const QPointF& position)
{
    lastMousePosition_ = { position.x(), position.y() };
}


void Camera::resize(const QPointF& size)
{
    /* update screen size and sensitivity */
    screenSize_ = size;
    sensitivity_ = 380.f / size.x();
}
