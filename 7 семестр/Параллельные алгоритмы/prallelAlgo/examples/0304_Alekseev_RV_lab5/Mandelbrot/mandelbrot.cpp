#include "mandelbrot.h"

size_t MakeIteration(double zx, double zy, size_t maxIter) {
    size_t iter = 0;
    double zxCur = zx;
    double zyCur = zy;

    while((zxCur * zxCur + zyCur * zyCur <= 4.0) && (iter < maxIter)) {
        double zxPerv = zxCur;
        zxCur = zxCur * zxCur - zyCur * zyCur +zx;
        zyCur = 2 * zxPerv * zyCur + zy;
        iter++;
    }

    return iter;
}

Mandelbrot::Mandelbrot(size_t w, size_t h, size_t iter) :
    width_{w},
    height_{h},
    iterations_{iter},
    points_{std::make_unique< uint8_t[] >(w * h)},
    image_{static_cast<int>(w), static_cast<int>(h), QImage::Format_RGB888}
{}

const QImage &Mandelbrot::Image() const
{
    return image_;
}

void Mandelbrot::Generate()
{
    constexpr double zxMin = -2.0;
    constexpr double zyMin = -1.2;
    constexpr double zxMax =  1.0;
    constexpr double zyMax =  1.2;
    const double stepX = (zxMax - zxMin) / width_;
    const double stepY = (zyMax - zyMin) / height_;

    double zx = zxMin;
    for (size_t x = 0; x < width_; x++, zx += stepX) {
        double zy = zyMin;
        for (size_t y = 0; y < height_; y++, zy += stepY) {
            size_t iter = MakeIteration(zx, zy, iterations_);
            points_[x + y * width_] = static_cast< uint8_t >(
                        0xff - 0xff * (iter / static_cast< double >(iterations_)));
        }
    }
}

void Mandelbrot::FillImage()
{
    QPainter painter;
    painter.begin(&image_);

    for (size_t x = 0; x < width_; x++) {
        for (size_t y = 0; y < height_; y++) {
            QPen pen(static_cast< uint8_t >( 0xff * (points_[x + y * width_] / static_cast< double >(iterations_)) ) << 5);
            painter.setPen(pen);
            painter.drawPoint(x, y);
        }
    }

    painter.end();
}
