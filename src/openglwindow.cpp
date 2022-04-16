#include "includes/openglwindow.hpp"
// #include "includes/scene.hpp"
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
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glClearColor(0.0,0.0,0.0,0.0);
    std::unique_ptr<Model> modelo (new Model("assets/bunny.obj"));
}


void Viewport::resizeGL(int w, int h){
    glViewport(0,0,h,w);
    float aspect = (GLfloat)w / (GLfloat)h;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void Viewport::paintGL(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    Scene::draw_teapot();
    modelo -> Draw();
}


void Viewport::mouseMoveEvent(QMouseEvent *event){

}

void Viewport::keyPressEvent(QKeyEvent *event){
    
}