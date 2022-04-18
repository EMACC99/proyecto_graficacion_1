#include "includes/openglwindow.hpp"

using namespace std::chrono_literals;

Viewport::Viewport(QWidget *parent): QOpenGLWidget(parent), modelo("bunny.obj"){

    this -> setUpdateBehavior(QOpenGLWidget::NoPartialUpdate);
    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setVersion(2,1);
    this -> setFormat(format);

    this -> create();

    connect(&this -> timer, SIGNAL(timeout()), this , SLOT(update()));
    timer.start(100ms);
    
}

Viewport::~Viewport(){
    makeCurrent();
    //delete
    doneCurrent();

}

void Viewport::initializeGL(){
    resizeGL(this -> width(), this -> height());
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glClearColor(0.0,0.0,0.0,0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
}


void Viewport::resizeGL(int w, int h){
    glViewport(0,0,h,w);
    float aspect = (GLfloat)w / (GLfloat)h;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(43, aspect, 0.01, 100.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5, 0,0,0, 0,1,0);

}

void Viewport::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Scene::draw_teapot();
    modelo.Draw();
}


void Viewport::mouseMoveEvent(QMouseEvent *event){

}

void Viewport::keyPressEvent(QKeyEvent *event){
    
}
