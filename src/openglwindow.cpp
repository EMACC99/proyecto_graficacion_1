#include "includes/gl_debug.hpp"
#include "includes/openglwindow.hpp"
#include "includes/utils.hpp"
using namespace std::chrono_literals;

Viewport::Viewport(QWidget *parent): QOpenGLWidget(parent), modelo("bunny.obj"){
    this -> setUpdateBehavior(QOpenGLWidget::NoPartialUpdate);
    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setVersion(2,1);
    this -> setFormat(format);

    this -> create();

    LightOn = true;
    connect(&this -> timer, SIGNAL(timeout()), this , SLOT(update()));
    timer.start(100ms);
    
}

Viewport::~Viewport(){
    makeCurrent();
    //delete
    doneCurrent();

}

void Viewport::initializeGL(){
    texture = Texture::LoadTexture("texture.bmp");

    GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat LightPosition[]= { 2.0f, 0.0f, 2.0f, 1.0f };
    /*Setting light values*/
    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);

    glClearColor(0.0,0.0,0.0,0.0);
    glClearDepth(1.f);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LEQUAL);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    resizeGL(this -> width(), this -> height());
    
    glGenTextures(1, &texture);
    glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


void Viewport::resizeGL(int w, int h){
    glViewport(0,0,h,w);
    float aspect = (GLfloat)w / (GLfloat)h;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(43, aspect, 0.01, 100.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,eyez, 0,0,0, 0,1,0);

}

void Viewport::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0,0,eyez, 0,0,0,  0,1,0);
    
    if (LightOn && !glIsEnabled(GL_LIGHT0))
        glEnable(GL_LIGHT0);
    else if(!LightOn)
        glDisable(GL_LIGHT0);
    
    Scene::draw_teapot();
    modelo.Draw();
    Scene::draw_room(&texture);
}

void Viewport::wheelEvent(QWheelEvent *event){
    this -> eyez += event -> angleDelta().y() / 8;
    // this -> resizeGL(this -> width(), this -> height());
    update();
}

void Viewport::mouseMoveEvent(QMouseEvent *event){
    
}

void Viewport::keyPressEvent(QKeyEvent *event){
    switch (event -> key()){
    case Qt::Key_L:
        LightOn = !LightOn;
        break;
    
    default:
        break;
    }
}
