#pragma once

#include "includes/scene.hpp"
#include <QMainWindow>
#include <QString>
#include <QSurfaceFormat>
#include <QTimer>
#include <QImage>
#include <QOpenGLFunctions>
#include <QOpenGLWindow>
#include <QOpenGLWidget>
#include <QtOpenGL>

#include<array>
#include <filesystem>
#include <algorithm>
#include <chrono>
#include <string>

#ifdef _WIN32
    #include <windows.h>
#endif
#ifdef __APPLE__
    #include <OpenGL/glu.h>
#else
    #include <GL/glu.h>
#endif

class Viewport : public QOpenGLWidget{
    Q_OBJECT

public:
    Viewport(QWidget *parent = 0);
    ~Viewport();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    QTimer timer;
    QOpenGLFunctions *gl;
    Model modelo;
};

