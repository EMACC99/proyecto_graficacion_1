#include "includes/openglwindow.hpp"

using namespace std::chrono_literals;

Viewport::Viewport(QWidget *parent): QOpenGLWidget(parent){

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

}


void Viewport::resizeGL(int w, int h){
    glViewport(0,0,h,w);
    float aspect = (GLfloat)w / (GLfloat)h;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(42.f, aspect, .1f, 100.f);
}

void Viewport::paintGL(){

}


void Viewport::mouseMoveEvent(QMouseEvent *event){

}

void Viewport::keyPressEvent(QKeyEvent *event){
    
}