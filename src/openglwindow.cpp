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
    for (auto &[name, textID] : textureID)
        glDeleteTextures(1, &textID);
    doneCurrent();

}

void Viewport::initializeGL(){

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
    initTextures();

    resizeGL(this -> width(), this -> height());
    
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
    
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glBindTexture(GL_TEXTURE_2D, textureID.at("wall"));
    Scene::draw_teapot();
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_GEN_T);

    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glBindTexture(GL_TEXTURE_2D, textureID.at("fur"));
    modelo.Draw();
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_GEN_S);
   
   
    glBindTexture(GL_TEXTURE_2D, textureID.at("grass"));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    Scene::draw_room();

    glDisable(GL_TEXTURE_2D);
}

void Viewport::wheelEvent(QWheelEvent *event){
    this -> eyez -= static_cast<GLfloat>(event -> angleDelta().y() / MOUSE_NORMALIZATION);
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

void Viewport::initTextures(){

    int n = 3;
    std::vector<std::string> files {"fur.png", "texture.bmp", "grass.png"};

    std::string texture_names[] = {"fur", "wall", "grass"};

    std::vector<GLuint> IDS(n);

    glGenTextures(n, IDS.data());
    for (int i = 0; i < n; ++i){
        textureID[texture_names[i]] = IDS[i];
        glBindTexture(GL_TEXTURE_2D, IDS[i]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        auto [textureData, width, height] = Texture::LoadTextureFile(files[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
        glBindTexture(GL_TEXTURE_2D, 0);
        Texture::FreeTextureData(textureData);
        
    }
}
