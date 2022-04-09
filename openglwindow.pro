QT+= core gui opengl widgets

SOURCES += \
    src/main.cpp\
    src/openglwindow.cpp\
    src/loadtexture.cpp \
    src/scene.cpp

HEADERS+=\
         includes/openglwindow.hpp\
         includes/gl_debug.hpp\
         includes/loadtexture.hpp\
         includes/scene.hpp

QMAKE_CXXFLAGS+= -std=c++17 -g -Wno-deprecated-declarations -Wall -Wpedantic -Wextra -Wno-sign-compare


RC_ICONS = assets/monachina.ico

CONFIG += debug

# make a mac debug build instead of an .app
CONFIG -= app_bundle
#CONFIG += release
#QMAKE_CXXFLAGS_RELEASE -= -O2
#QMAKE_CXXFLAGS_RELEASE += -Os
MOC_DIR = tmp/moc/
OBJECTS_DIR = tmp/obj/

macx {
	LIBS += -framework OpenGL

}
else{
	LIBS += -lGL -lglut -lGLU
}

win32:QMAKE_CXXFLAGS -=  -Wno-deprecated-declarations

TARGET = Proyecto
