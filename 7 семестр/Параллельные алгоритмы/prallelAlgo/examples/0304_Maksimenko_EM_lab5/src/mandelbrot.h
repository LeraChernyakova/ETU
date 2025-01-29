#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <QImage>
#include <memory>
#include <iostream>

class Mandelbrot
{
public:
    Mandelbrot( size_t w, size_t h, size_t iterations = 100 );
    virtual ~Mandelbrot() = default;

    const QImage& Image() const;

    virtual void Generate();
    void FillImage();

    size_t width_;
    size_t height_;
    size_t iterations_;

    std::unique_ptr< uint8_t[] > points_;
    QImage image_;

};

#endif // MANDELBROT_H
