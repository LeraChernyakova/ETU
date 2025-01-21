#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>
#include <QColorDialog>
#include <QPainter>
#include <iostream>

#include "gllighting.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
    setFocusPolicy(Qt::StrongFocus);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::init()
{
    ui->lightSettingsLayout->setAlignment(Qt::AlignTop);
    ui->materialSettingsLayout->setAlignment(Qt::AlignTop);
    ui->position->setAlignment(Qt::AlignTop);
    ui->direction->setAlignment(Qt::AlignTop);
    ui->lightColors->setAlignment(Qt::AlignTop);
    ui->materialColors->setAlignment(Qt::AlignTop);
    ui->materialSpecialSettingLayout->setAlignment(Qt::AlignTop);

    GLLighting& lighting = ui->glWindow->getLighting();
    QVector3D lightingPos = lighting.getPosition();
    QVector3D lightingDir = lighting.getDirection();

    ui->lightTypeSelector->addItems({
        "Point Light",
        "Directional Light",
        "Spot Light"
    });

    ui->positionX->setValue(lightingPos.x());
    ui->positionY->setValue(lightingPos.y());
    ui->positionZ->setValue(lightingPos.z());

    ui->directionX->setValue(lightingDir.x());
    ui->directionY->setValue(lightingDir.y());
    ui->directionZ->setValue(lightingDir.z());

    ui->cutoffSelector->setValue(lighting.getCutOff());
    ui->outerCutoffSelector->setValue(lighting.getOuterCutOff());

    QPixmap pixmap(32, 32);

    pixmap.fill(lighting.getAmbientColor());
    ui->lightAmbientSelector->setIcon(QIcon(pixmap));

    pixmap.fill(lighting.getDiffuseColor());
    ui->lightDiffuseSelector->setIcon(QIcon(pixmap));

    pixmap.fill(lighting.getSpecularColor());
    ui->lightSpecularSelector->setIcon(QIcon(pixmap));

    ui->figureSelector->setMaximum(ui->glWindow->getFigures().size());
    loadFigureMaterial();

    ui->projectionSelector->addItems({
        "Perspective",
        "Orthographic"
    });
}


void MainWindow::keyPressEvent(QKeyEvent* event)
{
    this->ui->glWindow->keyPressEvent(event);
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() & Qt::LeftButton)
    {
        drag_ = true;
        this->ui->glWindow->mousePressEvent(event);
    }
}


void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
    drag_ = false;
}


void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (drag_)
    {
        this->ui->glWindow->mouseMoveEvent(event);
    }
}


void MainWindow::on_lightTypeSelector_currentTextChanged(const QString &arg1)
{
    if (arg1 == "Point Light")
    {
        ui->glWindow->getLighting().setType(GLLightingType::Point);
    } else if (arg1 == "Directional Light")
    {
        ui->glWindow->getLighting().setType(GLLightingType::Directional);
    } else if (arg1 == "Spot Light")
    {
        ui->glWindow->getLighting().setType(GLLightingType::Spot);
    }
    ui->glWindow->update();
}


void MainWindow::on_positionX_valueChanged(double)
{
    ui->glWindow->getLighting().setPosition({
        static_cast<float>(ui->positionX->value()),
        static_cast<float>(ui->positionY->value()),
        static_cast<float>(ui->positionZ->value())
    });
    ui->glWindow->update();
}


void MainWindow::on_positionY_valueChanged(double)
{
    ui->glWindow->getLighting().setPosition({
        static_cast<float>(ui->positionX->value()),
        static_cast<float>(ui->positionY->value()),
        static_cast<float>(ui->positionZ->value())
    });
    ui->glWindow->update();
}


void MainWindow::on_positionZ_valueChanged(double)
{
    ui->glWindow->getLighting().setPosition({
        static_cast<float>(ui->positionX->value()),
        static_cast<float>(ui->positionY->value()),
        static_cast<float>(ui->positionZ->value())
    });
    ui->glWindow->update();
}


void MainWindow::on_directionX_valueChanged(double)
{
    ui->glWindow->getLighting().setDirection({
        static_cast<float>(ui->directionX->value()),
        static_cast<float>(ui->directionY->value()),
        static_cast<float>(ui->directionZ->value())
    });
    ui->glWindow->update();
}


void MainWindow::on_directionY_valueChanged(double)
{
    ui->glWindow->getLighting().setDirection({
        static_cast<float>(ui->directionX->value()),
        static_cast<float>(ui->directionY->value()),
        static_cast<float>(ui->directionZ->value())
    });
    ui->glWindow->update();
}


void MainWindow::on_directionZ_valueChanged(double)
{
    ui->glWindow->getLighting().setDirection({
        static_cast<float>(ui->directionX->value()),
        static_cast<float>(ui->directionY->value()),
        static_cast<float>(ui->directionZ->value())
    });
    ui->glWindow->update();
}


void MainWindow::on_cutoffSelector_valueChanged(double)
{
    ui->glWindow->getLighting().setCutOff(static_cast<float>(ui->cutoffSelector->value()));
    ui->glWindow->update();
}


void MainWindow::on_outerCutoffSelector_valueChanged(double)
{
    ui->glWindow->getLighting().setOuterCutOff(static_cast<float>(ui->outerCutoffSelector->value()));
    ui->glWindow->update();
}


void MainWindow::on_lightAmbientSelector_clicked()
{
    GLLighting& lighting = ui->glWindow->getLighting();
    QColor peek = QColorDialog::getColor(lighting.getAmbientColor(), nullptr, "Choose Light Ambient Color", QColorDialog::ShowAlphaChannel);

    if (peek.isValid())
    {
        lighting.setAmbientColor(peek);

        QPixmap pixmap(32, 32);
        pixmap.fill(peek);

        ui->lightAmbientSelector->setIcon(QIcon(pixmap));
    }
    ui->glWindow->update();
}

void MainWindow::on_lightDiffuseSelector_clicked()
{
    GLLighting& lighting = ui->glWindow->getLighting();
    QColor peek = QColorDialog::getColor(lighting.getDiffuseColor(), nullptr, "Choose Light Diffuse Color", QColorDialog::ShowAlphaChannel);

    if (peek.isValid())
    {
        lighting.setDiffuseColor(peek);

        QPixmap pixmap(32, 32);
        pixmap.fill(peek);

        ui->lightDiffuseSelector->setIcon(QIcon(pixmap));
    }
    ui->glWindow->update();
}


void MainWindow::on_lightSpecularSelector_clicked()
{
    GLLighting& lighting = ui->glWindow->getLighting();
    QColor peek = QColorDialog::getColor(lighting.getSpecularColor(), nullptr, "Choose Light Specular Color", QColorDialog::ShowAlphaChannel);

    if (peek.isValid())
    {
        lighting.setSpecularColor(peek);

        QPixmap pixmap(32, 32);
        pixmap.fill(peek);

        ui->lightSpecularSelector->setIcon(QIcon(pixmap));
    }
    ui->glWindow->update();
}


void MainWindow::on_shininessSelector_valueChanged(double arg1)
{
    std::shared_ptr<GLFigure> figure = ui->glWindow->getFigure(ui->figureSelector->value() - 1);
    figure->getMaterial().setShininess(static_cast<float>(arg1));
    ui->glWindow->update();
}


void MainWindow::on_ambientStrengthSelector_valueChanged(double arg1)
{
    std::shared_ptr<GLFigure> figure = ui->glWindow->getFigure(ui->figureSelector->value() - 1);
    figure->getMaterial().setAmbientStrength(static_cast<float>(arg1));
    ui->glWindow->update();
}


void MainWindow::on_figureSelector_valueChanged(int)
{
    loadFigureMaterial();
    ui->glWindow->update();
}


void MainWindow::on_materialDiffuseSelector_clicked()
{
    std::shared_ptr<GLFigure> figure = ui->glWindow->getFigure(ui->figureSelector->value() - 1);
    QColor peek = QColorDialog::getColor(figure->getMaterial().getDiffuseColor(), nullptr, "Choose Material Diffuse Color", QColorDialog::ShowAlphaChannel);

    if (peek.isValid())
    {
        figure->getMaterial().setDiffuseColor(peek);

        QPixmap pixmap(32, 32);
        pixmap.fill(peek);

        ui->materialDiffuseSelector->setIcon(QIcon(pixmap));
    }
    ui->glWindow->update();
}


void MainWindow::on_materialSpecularSelector_clicked()
{
    std::shared_ptr<GLFigure> figure = ui->glWindow->getFigure(ui->figureSelector->value() - 1);
    QColor peek = QColorDialog::getColor(figure->getMaterial().getSpecularColor(), nullptr, "Choose Material Specular Color", QColorDialog::ShowAlphaChannel);

    if (peek.isValid())
    {
        figure->getMaterial().setSpecularColor(peek);

        QPixmap pixmap(32, 32);
        pixmap.fill(peek);

        ui->materialSpecularSelector->setIcon(QIcon(pixmap));
    }
    ui->glWindow->update();
}


void MainWindow::on_projectionSelector_currentTextChanged(const QString &arg1)
{
    if (arg1 == "Perspective")
    {
        ui->glWindow->setProjectionType(GLProjectionType::Perspective);
    } else if (arg1 == "Orthographic")
    {
        ui->glWindow->setProjectionType(GLProjectionType::Orthographic);
    }
    ui->glWindow->update();
}


void MainWindow::loadFigureMaterial()
{
    std::shared_ptr<GLFigure> figure = ui->glWindow->getFigure(ui->figureSelector->value() - 1);
    // colors
    QPixmap pixmap(32, 32);
    // diffuse
    pixmap.fill(figure->getMaterial().getDiffuseColor());
    ui->materialDiffuseSelector->setIcon(QIcon(pixmap));
    // specular
    pixmap.fill(figure->getMaterial().getSpecularColor());
    ui->materialSpecularSelector->setIcon(QIcon(pixmap));
    // shininess
    ui->shininessSelector->setValue(figure->getMaterial().getShininess());
    // ambient strength
    ui->ambientStrengthSelector->setValue(figure->getMaterial().getAmbientStrength());
}
