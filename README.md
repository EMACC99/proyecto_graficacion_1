# Proyecto 1 de graficacion

Librerias Necesarias:

* OpenGL
* glu
* glew
* glm
* glut
* Qt
* qmake
* make

Para clonar el proyecto, hagalo con `git clone --recursive` para que los submodulos se inicialicen correctamente.

## Compliacion

```sh
qmake
make
./Proyecto
```

## Instrucciones de uso

Para cambiar la iluminacion, presione la tecla `L`.
![luz](Images/Luz.gif)
Mueva la rueda del mouse para hacer zoom en la escena.
![zoom](Images/zoom.gif)

## Ventajas y otras notas

Se penso en la disminucion de dependencias fuertes como lo es `QT` para que se pueda usar independientemente de la libreria que maneje el vewport.

Uso de header only libraries para minimizar instalaciones.
