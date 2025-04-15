#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h> // (or others, depending on the system in use)
#include <iostream>

static void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFlush();
}

void init(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1100, 700);
    glutInitWindowPosition(100, 0);
    glutCreateWindow("Team Project");

    glClearColor(0.0, 0.0, 0.0, 1.0);

    glutDisplayFunc(display);
}

void run() {
     glutMainLoop();
}

int main(int argc, char** argv) {
    init(argc, argv);
    run();
    return 0;
}


