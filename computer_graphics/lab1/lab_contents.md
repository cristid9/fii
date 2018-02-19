Lab 1
======

* mailul are labelul `[gpc]`
* formatul arhivei la teme `[gpc]_nume_prenume_3A7_nume_prenume_3A7_T1`
* se aplica penalizari
* 40% din total lab == trecut
* folosim `OpenGL`
* `glut` =  `gl utility token`
  - biblioteca rigida
  - nu mai trebuie sa faci initializari mari in `OpenGL`
  - `glew` e un succesor al lui `glut`
* include-uri pe linux: ` #include <GL/glut.h>`
* `single buffering` si `double buffering` la placa video
* de ce `RGB`, de ce `verde` in loc de `galbe`
* regula mainii drepte

Tema
====
* display3, cu coordonate exacte
* display6, vrea un singur apel de `GL_TRIANGLES`
* display8, vrea sa fie ca un contur bordura aia rosie

Misc
=====
* build din `clion`
  - `apt-get install freeglut3-dev`
  - `target_link_libraries(<source name> -lGL -lGLU -lglut)`, adaugi asta in `CMakeList.txt`
* build din terminal
  - `g++ main.cpp -o main -lGL -lGLU -lglut`
  
